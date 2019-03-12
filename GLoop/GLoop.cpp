#include <iostream>
#include "GLoop.hpp"

namespace gloop {
	
	void	GLoop::run(ecm::Register &reg) {
		auto ret = run_hooks(_stageM.get_stage(gloop::StageType::INIT), reg);
		if (ret != gloop::HookStatus::OK)
			return;
		while ((ret = run_loop_hooks(_stageM.get_stage(gloop::StageType::LOOP), reg)) == gloop::HookStatus::OK);
		if (ret != gloop::HookStatus::STOP_LOOP)
			return;
		run_hooks(_stageM.get_stage(gloop::StageType::FINAL), reg);
	}

	gloop::HookStatus		GLoop::run_hooks(gloop::Stage &stage, ecm::Register &reg) {
		std::cout << "0" << std::endl;
		auto ret = run_one_hook(stage.get_hookMap(gloop::HookType::EARLY), reg);
		std::cout << "1" << std::endl;
		if (ret != gloop::HookStatus::OK)
			return ret;
		std::cout << "2" << std::endl;
		ret = run_one_hook(stage.get_hookMap(gloop::HookType::MIDDLE), reg);
		if (ret != gloop::HookStatus::OK)
			return ret;
		std::cout << "3" << std::endl;
		return run_one_hook(stage.get_hookMap(gloop::HookType::LAST), reg);
	}
	
	gloop::HookStatus		GLoop::run_one_hook(gloop::Stage::hookMap &hook, ecm::Register &reg) {
		
		for (auto &&elem : hook) {
			std::cout << "in hook" << std::endl;
			auto ret = gloop::HookStatus::OK;
			// if (elem.second.hook.threadable == true) {
			// } else
			ret = elem.second.hook.callback(reg, *this);
			if (ret != gloop::HookStatus::OK)
				return ret;
		}
		
		return gloop::HookStatus::OK;
	}

	gloop::HookStatus		GLoop::run_loop_hooks(gloop::Stage &stage, ecm::Register &reg) {
		auto ret = run_one_loop_hook(stage.get_hookMap(gloop::HookType::EARLY), reg);
		if (ret != gloop::HookStatus::OK)
			return ret;
		ret = run_one_loop_hook(stage.get_hookMap(gloop::HookType::MIDDLE), reg);
		if (ret != gloop::HookStatus::OK)
			return ret;
		return run_one_loop_hook(stage.get_hookMap(gloop::HookType::LAST), reg);
	}

	gloop::HookStatus		GLoop::run_one_loop_hook(gloop::Stage::hookMap &hook, ecm::Register &reg) {
		for (auto &&elem : hook) {
			gtimer	now = std::chrono::system_clock::now();
			long		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - elem.second.last_call).count();
			if (elapsed >= elem.second.hook.callrate) {
				auto		ret = gloop::HookStatus::OK;
				elem.second.last_call = now;
				// if (elem.second.hook.threadable == true) {
				// } else
				ret = elem.second.hook.callback(reg, *this);
				if (ret != gloop::HookStatus::OK)
					return ret;
			}
		}
		return gloop::HookStatus::OK;
	}

} // gloop