// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheLastKnightCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Animation/AnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include <TheLastKnight/Character/fsm/states/Idle.h>
#include <TheLastKnight/Character/fsm/states/Walk.h>
#include <TheLastKnight/Character/fsm/states/Casting.h>
#include <TheLastKnight/Character/fsm/states/IdleAbility.h>
#include <TheLastKnight/Character/fsm/states/Cooldown.h>

#include <TheLastKnight/Character/fsm/transitions/EnterIdle.h>
#include <TheLastKnight/Character/fsm/transitions/EnterWalk.h>
#include <TheLastKnight/Character/fsm/transitions/EnterCast.h>
#include <TheLastKnight/Character/fsm/transitions/EnterIdleAbility.h>
#include <TheLastKnight/Character/fsm/transitions/EnterCooldown.h>

#include <TheLastKnight/Character/InputHandler.h>
#include <TheLastKnight/Character/AbilitiesToolChest.h>

#include <TheLastKnight/Abilities/IAbility.h>
#include <TheLastKnight/Abilities/Ability.h>
#include <TheLastKnight/Abilities/HealthAbility.h>

#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbilities.h>
#include <TheLastKnight/Abilities/DataAssets/DA_CharacterAbility.h>

#include <memory>

#include <cassert>

using namespace TLN;

//////////////////////////////////////////////////////////////////////////
// ATheLastKnightCharacter

ATheLastKnightCharacter::ATheLastKnightCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ATheLastKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	mInputHandler = std::make_shared<InputHandler>();

	FillUpCharacterAttributes();
	FillUpAbilitiesFactory();
	CreateStatesMachine();
	AddDefaultAbilitiesToTheAbilitiesToolChest();
}

void ATheLastKnightCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UE_LOG(LogTemp, Log, TEXT("Character FSM:"));
	for (auto&& machine : mStatesMachines)
	{
		machine->Update(DeltaSeconds);
		UE_LOG(LogTemp, Log, TEXT("Character FSM state: %d"), machine->GetCurrentState()->GetID());
	}
}

bool ATheLastKnightCharacter::IsWalking() const
{
	auto characterMovement = GetCharacterMovement();
	return characterMovement->IsWalking() && !characterMovement->Velocity.IsZero();
}

bool ATheLastKnightCharacter::IsIdle() const
{
	auto characterMovement = GetCharacterMovement();
	return characterMovement->IsWalking() && characterMovement->Velocity.IsZero();
}

bool ATheLastKnightCharacter::IsCasting() const
{
	return mStatesMachines[1]->GetCurrentState()->GetID() == CharacterState::STATE_CASTING;
}

bool ATheLastKnightCharacter::IsReadyToCast() const
{
	return mAbilitiesToolChest.IsReadyToCast();
}

void ATheLastKnightCharacter::PlayCastingAnimation()
{
	IsCastingOneHeight = true;
}

void ATheLastKnightCharacter::StopCastingAnimation()
{
	IsCastingOneHeight = false;
}

bool ATheLastKnightCharacter::CanCast(InputAction action) const
{
	return mAbilitiesToolChest.CanCast(action, mAttributes.GetMana());
}

std::shared_ptr<TLN::IAbility> ATheLastKnightCharacter::Cast()
{
	TLN::InputAction action;
	if (mInputHandler->IsActionPressed(InputAction::ABILITY1))
	{
		action = InputAction::ABILITY1;
	} 
	else if (mInputHandler->IsActionPressed(InputAction::ABILITY2))
	{
		action = InputAction::ABILITY2;
	}

	auto ability = mAbilitiesToolChest.GetAbility(action);
	if (ability)
	{
		mAttributes.SetMana(mAttributes.GetMana() - ability->GetCastCost());
		ability->Cast(GetActorLocation());
	}

	return ability;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheLastKnightCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheLastKnightCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheLastKnightCharacter::MoveRight);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("Ability1", IE_Pressed, this, &ATheLastKnightCharacter::PressKey, TLN::InputAction::ABILITY1);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("Ability1", IE_Released, this, &ATheLastKnightCharacter::ReleaseKey, TLN::InputAction::ABILITY1);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("Ability2", IE_Pressed, this, &ATheLastKnightCharacter::PressKey, TLN::InputAction::ABILITY2);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("Ability2", IE_Released, this, &ATheLastKnightCharacter::ReleaseKey, TLN::InputAction::ABILITY2);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATheLastKnightCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATheLastKnightCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATheLastKnightCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATheLastKnightCharacter::TouchStopped);
}

void ATheLastKnightCharacter::CreateMovementStatesMachine()
{
	auto statesMachine = std::make_unique<StatesMachine>(mCharacterFSMContext);

	auto idle = std::make_shared<Idle>();
	auto walk = std::make_shared<Walk>();

	statesMachine->AddState(idle);
	statesMachine->AddState(walk);

	//from Idle
	statesMachine->AddTransition(std::make_unique<EnterWalk>(idle, walk));

	//from Walk
	statesMachine->AddTransition(std::make_unique<EnterIdle>(walk, idle));

	statesMachine->SetInitialState(idle->GetID());

	mStatesMachines.push_back(std::move(statesMachine));
}

void ATheLastKnightCharacter::CreateAbilityStatesMachine()
{
	auto statesMachine = std::make_unique<StatesMachine>(mCharacterFSMContext);

	auto idle = std::make_shared<IdleAbility>();
	auto cast = std::make_shared<Casting>();
	auto cooldown = std::make_shared<Cooldown>();

	statesMachine->AddState(idle);
	statesMachine->AddState(cast);
	statesMachine->AddState(cooldown);

	//from Idle
	statesMachine->AddTransition(std::make_unique<EnterCast>(idle, cast));

	//from Cast
	statesMachine->AddTransition(std::make_unique<EnterCooldown>(cast, cooldown));

	//from Cooldown
	statesMachine->AddTransition(std::make_unique<EnterIdleAbility>(cooldown, idle));

	statesMachine->SetInitialState(idle->GetID());

	mStatesMachines.push_back(std::move(statesMachine));
}

void ATheLastKnightCharacter::CreateStatesMachine()
{
	mCharacterFSMContext = std::make_shared<CharacterContext>(this, mInputHandler);
	CreateMovementStatesMachine();
	CreateAbilityStatesMachine();
}

void ATheLastKnightCharacter::FillUpCharacterAttributes()
{
	if (CharacterAttributes)
	{
		uint8 maxHealth = CharacterAttributes->GetMaxHealth();
		assert(maxHealth > 0);
		mAttributes.SetMaxHealth(maxHealth);

		uint8 maxMana = CharacterAttributes->GetMaxMana();
		assert(maxMana > 0);
		mAttributes.SetMaxMana(maxMana);
	}
}

void ATheLastKnightCharacter::FillUpAbilitiesFactory()
{
	mAbilitiesFactory = std::make_shared<AbilitiesFactory>(mCharacterAbilities);
	mAbilitiesFactory->Register(
		HealthAbility::GetName(), 
		[](AAbility* ability, UDA_CharacterAbility* abilityDA) 
		{
			return HealthAbility::Create(ability, abilityDA);
		}
	);
}

void ATheLastKnightCharacter::AddDefaultAbilitiesToTheAbilitiesToolChest()
{
	auto ability = mAbilitiesFactory->Create(HealthAbility::GetName(), GetWorld(), this);
	auto index = mAbilitiesToolChest.AddAbility(ability);
	mAbilitiesToolChest.BindAbilityToToolBelt(TLN::InputAction::ABILITY1, index);
	mAbilitiesToolChest.BindAbilityToToolBelt(TLN::InputAction::ABILITY2, index);
}

void ATheLastKnightCharacter::PerformMovement()
{
	
}


void ATheLastKnightCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATheLastKnightCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATheLastKnightCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATheLastKnightCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheLastKnightCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATheLastKnightCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !IsCasting())
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ATheLastKnightCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) && !IsCasting())
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATheLastKnightCharacter::PressKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, true);
}

void ATheLastKnightCharacter::ReleaseKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, false);
	UE_LOG(LogTemp, Log, TEXT("ATheLastKnightCharacter::ReleaseKey"));
}
