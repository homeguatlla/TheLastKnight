#include <TheLastKnight/Character/fsm/transitions/EnterIdle.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterIdle::EnterIdle(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterIdle::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterIdle::CanPerformTransition() const
	{
		return true;
		//return NPhysics::NMath::IsNearlyEqual(mPhysicsComponent->GetVelocity(), glm::vec3(0.0f)) &&
		//	mCollisionComponent->IsOnGround();
	}
};