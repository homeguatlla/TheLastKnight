#pragma once

namespace TLN
{
	enum class CharacterState
	{
		STATE_IDLE = 0,
		STATE_WALKING = 1,
		STATE_RUNNING = 2,
		STATE_JUMPING = 3,
		STATE_ON_AIR = 4,		

		STATE_IDLE_ABILITY = 10,
		STATE_CASTING = 11,
		STATE_COOLDOWN = 12,

		STATE_NORMAL = 100,
		STATE_DEBUG = 101
	};
};
