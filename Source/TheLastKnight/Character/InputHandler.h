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
		USE,

		ENTER_LEAVE_DEBUG,
		NEXT_NPC,
		PREVIOUS_NPC
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

			bool IsActionPressed(InputAction action) const;
			const Action GetAction(InputAction action) const;
			void InsertInput(InputAction action, bool pressed);
	};
};