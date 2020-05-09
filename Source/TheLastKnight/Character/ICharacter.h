#pragma once

namespace TLN
{
	class ICharacter
	{
		public:
			virtual void PerformMovement() = 0;
			void Empty() {}
	};
};