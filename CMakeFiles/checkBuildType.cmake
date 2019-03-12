if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("CMAKE_BUILD_TYPE set on Debug")
	if (UNIX)
		set(CMAKE_CXX_FLAGS "-g3 ${CMAKE_CXX_FLAGS}")
	elseif (WIN32)
		set(CMAKE_CXX_FLAGS " $/D_DEBUG {CMAKE_CXX_FLAGS}")
  	endif()
else()
	set(CMAKE_BUILD_TYPE "Release")
	message("Unknown CMAKE_BUILD_TYPE. CMAKE_BUILD_TYPE set on Release by default")
endif()