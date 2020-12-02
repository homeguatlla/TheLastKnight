// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include <TheLastKnight/utils/fsm/StatesMachine.h>

#include <TheLastKnight/Character/CharacterAttributes.h>
#include <TheLastKnight/Character/DA_CharacterAttributes.h>
#include <TheLastKnight/Character/fsm/CharacterContext.h>
#include <TheLastKnight/Character/fsm/states/CharacterStates.h>
#include <TheLastKnight/Character/ICharacter.h>
#include <TheLastKnight/Character/InputHandler.h>
#include <TheLastKnight/Character/AbilitiesToolChest.h>
#include <TheLastKnight/Character/AbilitiesToolBelt.h>
#include <TheLastKnight/Abilities/AbilitiesFactory.h>
#include <TheLastKnight/Debug/DebugData.h>

#include <vector>
#include "TheLastKnightCharacter.generated.h"


using TLN::ICharacter;
class UDA_CharacterAbilities;


DECLARE_DELEGATE_OneParam(FPressKeyDelegate, TLN::InputAction);
DECLARE_DELEGATE_OneParam(FReleaseKeyDelegate, TLN::InputAction);

UCLASS(config=Game)
class ATheLastKnightCharacter : public ACharacter, public ICharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Custom attributes
	std::shared_ptr<TLN::CharacterAttributes> mAttributes;

	//Abilities Tool Chest
	//TLN::AbilitiesToolChest mAbilitiesToolChest;
	//Abilities Tool belt
	TLN::AbilitiesToolBelt mAbilitiesToolBelt;

	//States machine to control character states
	using StatesMachine = core::utils::FSM::StatesMachine<TLN::CharacterState, TLN::CharacterContext>;
	std::vector<std::unique_ptr<StatesMachine>> mStatesMachines;
	std::shared_ptr<TLN::CharacterContext> mCharacterFSMContext;

	//Holds last input
	std::shared_ptr<TLN::InputHandler> mInputHandler;

	std::shared_ptr<TLN::AbilitiesFactory> mAbilitiesFactory;

	std::shared_ptr<DebugData> mDebugData;

	bool mHasNotifiedData;

public:
	ATheLastKnightCharacter();

	void BeginPlay() override;

	//inherited from ICharacter
	bool IsWalking() const override;
	bool IsIdle() const override;
	bool IsCasting() const override;
	bool IsReadyToCast() const override;

	void PlayCastingAnimation() override;
	void StopCastingAnimation() override;

	bool CanCast(TLN::InputAction action) const override;
	std::shared_ptr<TLN::IAbility> Cast() override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Set to true when casting one hand height */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool IsCastingOneHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attributes")
	UDA_CharacterAttributes* CharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Abilities")
	UDA_CharacterAbilities* mCharacterAbilities;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Tick(float DeltaSeconds) override;
	
	void PressKey(TLN::InputAction action);
	void ReleaseKey(TLN::InputAction action);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:
	void CreateStatesMachine();
	void CreateMovementStatesMachine();
	void CreateAbilityStatesMachine();
	void CreateDebugStatesMachine();
	void FillUpCharacterAttributes();
	void FillUpAbilitiesFactory();
	void AddDefaultAbilitiesToTheAbilitiesToolChest();
	void NotifyStartAttributeValues() const;

	//inherit from TLN::ICharacter
	void PerformMovement() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

