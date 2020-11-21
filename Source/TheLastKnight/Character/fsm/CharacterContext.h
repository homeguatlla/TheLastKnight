#pragma once
#include <memory>
#include <string>
#include <vector>
#include <TheLastKnight/Character/InputHandler.h>

class AEventDispatcher;
class UWorld;
class DebugData;

namespace TLN
{
	class ICharacter;
	class IAbility;

	class CharacterContext
	{
	public:
		CharacterContext(
			UWorld* world, 
			ICharacter* character, 
			std::shared_ptr<InputHandler> input,
			std::shared_ptr<DebugData> debugData);

		~CharacterContext() = default;

		ICharacter* GetCharacter();
		std::shared_ptr<InputHandler> GetInputHandler();
		AEventDispatcher* GetEventDispatcher();

		void SetAbility(std::shared_ptr<IAbility> ability);
		std::shared_ptr<IAbility> GetAbility() { return mAbility; }

		std::shared_ptr<DebugData> GetDebugData() const { return std::move(mDebugData); }

		std::vector<std::string> GetAllNPCAgentNames() const;

	private:
		void InitializeDebugData();

	private:
		UWorld* mWorld;
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
		std::shared_ptr<IAbility> mAbility;
		AEventDispatcher* mEventDispatcher;
		std::shared_ptr<DebugData> mDebugData;
	};
};
