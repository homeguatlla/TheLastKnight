#pragma once
#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
	class ICharacter
	{
		public:
			virtual void PerformMovement() = 0;
			virtual bool IsWalking() const = 0;
			virtual bool IsIdle() const = 0;
			virtual bool IsCasting() const = 0;

			virtual bool CanCast(InputAction action) const = 0;
			virtual void Cast() = 0;

			void Empty() {}
	};
};