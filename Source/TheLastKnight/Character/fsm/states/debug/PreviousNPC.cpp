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
		auto names = GetContext()->GetAllNPCAgentNames();
		auto debugData = GetContext()->GetDebugData();

		auto it = std::find(names.begin(), names.end(), debugData->GetCurrentNPCName());
		if (it != names.end())
		{
			if (it == names.begin())
			{
				it = names.end() - 1;
			}
			else
			{
				it--;
			}
			debugData->SetCurrentNPCName(*it);
			mEventDispatcher->OnPreviousNPC.Broadcast(utils::UtilsLibrary::ConvertToFString(*it));
		}		
	}
};