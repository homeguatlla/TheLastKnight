#include <TheLastKnight/Character/fsm/states/debug/Debug.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Debug/DebugData.h>
#include <TheLastKnight/EventDispatcher.h>

namespace TLN 
{
	void Debug::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void Debug::OnEnter(float deltaTime)
	{
		auto debugData = GetContext()->GetDebugData();
		mEventDispatcher->OnNextNPC.Broadcast(debugData->GetCurrentNPCController());
		mEventDispatcher->OnEnableDebugMode.Broadcast(true);
	}
};