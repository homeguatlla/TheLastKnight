#pragma once

namespace TLN
{
	class ICharacter
	{
		public:
			virtual void PerformMovement() = 0;
			virtual bool IsWalking() const = 0;
			virtual bool IsIdle() const = 0;
			void Empty() {}
	};
};