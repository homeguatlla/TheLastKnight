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
		auto names = GetContext()->GetAllNPCAgentNames();
		auto debugData = GetContext()->GetDebugData();

		auto it = std::find(names.begin(), names.end(), debugData->GetCurrentNPCName());
		if (it != names.end())
		{
			it++;
			if (it == names.end())
			{
				it = names.begin();
			}
			debugData->SetCurrentNPCName(*it);
			mEventDispatcher->OnNextNPC.Broadcast(utils::UtilsLibrary::ConvertToFString(*it));
		}
	}
};