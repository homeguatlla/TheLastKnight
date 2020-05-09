#pragma once
#include "CoreMinimal.h"

namespace TLN
{
	class InputHandler
	{
		public:
			InputHandler() = default;
			~InputHandler() = default;

			void ForwardBackward(const FVector& direction, float value);
			void LeftRight(const FVector& direction, float value);
			void Ability1(bool pressed);
			void Ability2(bool pressed);
	};
};