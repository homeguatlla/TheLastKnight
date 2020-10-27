#include <TheLastKnight/Character/fsm/states/debug/Normal.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/EventDispatcher.h>

namespace TLN
{
	void Normal::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void Normal::OnEnter(float deltaTime)
	{
		mEventDispatcher->OnEnableDebugMode.Broadcast(false);
	}
};