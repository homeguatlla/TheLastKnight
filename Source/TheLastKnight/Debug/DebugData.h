#pragma once

class ANPCAIController;

class DebugData
{
	public:
		DebugData() = default;
		virtual ~DebugData() = default;
		const ANPCAIController* GetCurrentNPCController() const { return mCurrentNPCController; }
		void SetCurrentNPCController(const ANPCAIController* controller);

	private:
		const ANPCAIController* mCurrentNPCController;
};
