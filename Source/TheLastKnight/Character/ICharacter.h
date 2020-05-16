#pragma once
#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
	class IAbility;

	class ICharacter
	{
		public:
			virtual void PerformMovement() = 0;
			virtual bool IsWalking() const = 0;
			virtual bool IsIdle() const = 0;
			virtual bool IsCasting() const = 0;

			virtual bool CanCast(InputAction action) const = 0;
			virtual bool IsReadyToCast() const = 0;
			virtual std::shared_ptr<TLN::IAbility> Cast() = 0;

			virtual void PlayCastingAnimation() = 0;
			virtual void StopCastingAnimation() = 0;

			void Empty() {}
	};
};