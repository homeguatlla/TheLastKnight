#include <TheLastKnight/Character/fsm/states/debug/PreviousNPC.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/EventDispatcher.h>
#include <TheLastKnight/Debug/DebugData.h>
#include <TheLastKnight/utils/UtilsLibrary.h>
#include <algorithm>

namespace TLN
{
	void PreviousNPC::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void PreviousNPC::OnEnter(float deltaTime)
	{
		auto controllers = GetContext()->GetAllNPCAgentControllers();
		auto debugData = GetContext()->GetDebugData();

		auto it = std::find(controllers.begin(), controllers.end(), debugData->GetCurrentNPCController());
		if (it != controllers.end())
		{
			if (it == controllers.begin())
			{
				it = controllers.end() - 1;
			}
			else
			{
				it--;
			}
			debugData->SetCurrentNPCController(*it);
			mEventDispatcher->OnPreviousNPC.Broadcast(*it);
		}		
	}
};