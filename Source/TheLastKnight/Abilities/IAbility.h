#pragma once
#include "CoreMinimal.h"

namespace TLN
{
	class IAbility
	{
		public:
			virtual bool CanCast(int availableMana) const = 0;
			virtual void CastSpell(const FVector& location) = 0;
			virtual int GetCastCost() = 0;
			virtual void Update(float deltaTime) = 0;
			virtual bool IsCasting() const = 0;
			virtual bool IsReadyToCast() const = 0;
			//void Empty() {};
	};
};