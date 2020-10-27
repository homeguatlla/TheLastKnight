#include <TheLastKnight/Character/fsm/states/debug/Debug.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/EventDispatcher.h>

namespace TLN
{
	void Debug::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void Debug::OnEnter(float deltaTime)
	{
		mEventDispatcher->OnEnableDebugMode.Broadcast(true);
	}
};