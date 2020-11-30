#include <TheLastKnight/Character/fsm/states/debug/NextNPC.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/EventDispatcher.h>
#include <TheLastKnight/Debug/DebugData.h>
#include <TheLastKnight/utils/UtilsLibrary.h>
#include <algorithm>

namespace TLN
{
	void NextNPC::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void NextNPC::OnEnter(float deltaTime)
	{
		auto controllers = GetContext()->GetAllNPCAgentControllers();
		auto debugData = GetContext()->GetDebugData();

		auto it = std::find(controllers.begin(), controllers.end(), debugData->GetCurrentNPCController());
		if (it != controllers.end())
		{
			it++;
			if (it == controllers.end())
			{
				it = controllers.begin();
			}
			debugData->SetCurrentNPCController(*it);
			mEventDispatcher->OnNextNPC.Broadcast(*it);
		}
	}
};