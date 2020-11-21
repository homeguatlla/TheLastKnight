#pragma once

#include<string>


class DebugData
{
	public:
		DebugData() = default;
		virtual ~DebugData() = default;
		std::string GetCurrentNPCName() const { return mCurrentNPCName; }
		void SetCurrentNPCName(const std::string& name);

	private:
		std::string mCurrentNPCName;
};
