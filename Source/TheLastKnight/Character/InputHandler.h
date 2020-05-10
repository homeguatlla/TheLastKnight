#pragma once
#include "CoreMinimal.h"
#include<map>

namespace TLN
{
	enum class InputAction
	{
		JUMP,
		ABILITY1,
		ABILITY2,
		USE
	};

	struct Action
	{
		bool isPressed;
		
		Action() = default;
		~Action() = default;

		Action(bool pressed) :
			isPressed{pressed}
		{}
	};

	class InputHandler
	{
		std::map<InputAction, Action> mInputs;

		public:
			InputHandler() = default;
			~InputHandler() = default;

			void Use(bool pressed);
			void Ability1(bool pressed);
			void Ability2(bool pressed);

			bool IsActionPressed(InputAction action) const;
			const Action GetAction(InputAction action) const;
	};
};