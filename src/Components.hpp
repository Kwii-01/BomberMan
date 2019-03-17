#pragma once

#include <vector>
#include <queue>
#include "Register.hpp"

struct vec3df {
	double	x;
	double	y;
	double	z;
};

namespace Bomber {

	constexpr char	GROUND_T[] = "./sprites/BrickGround.jpg";
	constexpr char	BACKGROUND_T[] = "./sprites/backgroundBrick.jpg";
	constexpr char	WALL_T[] = "./sprites/BrickWall.jpg";
	constexpr char	BOX_T[] = "./sprites/wood_box.png";
	constexpr char	PLAYER_ONE_T[] = "./sprites/p1.jpg";
	constexpr char	PLAYER_TWO_T[] = "./sprites/p2.jpg";

	constexpr char	GAME_SONG[] = "./assets/CANDY.ogg";

	constexpr int	MAX_X = 17;
	constexpr int	MAX_Y = 19;
	constexpr int	POURCENT_MAP_REMPL = 10;

	template<typename T>
	struct Vec3 {
		T	x;
		T	y;
		T	z;
	};

	template<typename T>
	struct Vec2 {
		T	x;
		T	y;
	};

	enum Bomber_types {
		PATH,
		WALL,
		BOX,
	};

	enum Bomber_bonus {
		BIG_EXPLOSION,
		LIFE,
		MORE_BOMB,
	};

	enum Collision {
		KILL,
		BLOCK_ALL,
		BLOCK_PLAYER,
		PASS,
		GET,
	};

	enum ItemType {
		CUBE,
		SPHERE,
		MESH,
		TEXT,
		BUTTON,
	};

	enum State {
		NOTHING,
		NEW,
		UPDATE,
		DELETE,
	};

	enum Keys {
		K_Z,
		K_S,
		K_Q,
		K_D,
		ARROW_U,
		ARROW_D,
		ARROW_L,
		ARROW_R,
		K_SPACE,
		K_ENTER,
		ESCAPE,
	};

	struct Pos : public Vec3<int> {};

	struct Stat {
		int	max_bomb;
		int	explosion_radius;
		int	life;
	};

	struct Bomb {
		GEcm::entity_type	parent;
		int			explosion_radius;
	};

	struct Graphics {
		bool			isVisible;
		std::string		texture;
		Bomber::ItemType	type;
		Bomber::State	state;
		double		size;
	};

	struct Inputs {
		std::queue<Bomber::Keys>	keys;
	};

} // Bomber
