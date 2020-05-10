#pragma once
#include "CoreMinimal.h"
#include <TheLastKnight/Abilities/AbilitityBase.h>

class ABPHealthAbility;

namespace TLN
{
	class HealthAbility : public AbilityBase
	{
		ABPHealthAbility* mBPHealthAbility;

	public:
		HealthAbility(ABPHealthAbility* ability);

		void DoCast(const FVector& location) override;
	};
};