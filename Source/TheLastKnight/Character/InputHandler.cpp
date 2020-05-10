#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
	void InputHandler::Use(bool pressed)
	{
		mInputs.insert(std::make_pair(InputAction::USE, Action(pressed)));
	}

	void InputHandler::Ability1(bool pressed)
	{
		mInputs.insert(std::make_pair(InputAction::ABILITY1, Action(pressed)));
	}

	void InputHandler::Ability2(bool pressed)
	{
		mInputs.insert(std::make_pair(InputAction::ABILITY2, Action(pressed)));
	}

	bool InputHandler::IsActionPressed(InputAction action) const
	{
		auto it = mInputs.find(action);

		if (it != std::end(mInputs))
		{
			return it->second.isPressed;
		}
		else
		{
			return false;
		}
	}
	
	const Action InputHandler::GetAction(InputAction action) const
	{
		auto it = mInputs.find(action);

		if (it != std::end(mInputs))
		{
			return it->second;
		}

		return Action();
	}
}