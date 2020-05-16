#include <TheLastKnight/Character/InputHandler.h>

namespace TLN
{
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

	void InputHandler::InsertInput(InputAction action, bool pressed)
	{
		auto it = mInputs.insert(std::make_pair(action, Action(pressed)));

		if (!it.second) //already existed
		{
			it.first->second = pressed;
		}
	}
}