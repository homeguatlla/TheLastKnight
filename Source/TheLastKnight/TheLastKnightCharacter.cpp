// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheLastKnightCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include <TheLastKnight/Character/fsm/states/Idle.h>
#include <TheLastKnight/Character/fsm/states/Walk.h>
#include <TheLastKnight/Character/fsm/states/Casting.h>

#include <TheLastKnight/Character/fsm/transitions/EnterIdle.h>
#include <TheLastKnight/Character/fsm/transitions/EnterWalk.h>
#include <TheLastKnight/Character/fsm/transitions/EnterCast.h>

#include <TheLastKnight/Character/InputHandler.h>
#include <TheLastKnight/Character/AbilitiesToolChest.h>

#include <TheLastKnight/Abilities/IAbility.h>
#include <TheLastKnight/Abilities/BPHealthAbility.h>
#include <TheLastKnight/Abilities/HealthAbility.h>

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
	CreateStatesMachine();
	AddDefaultAbilitiesToTheAbilitiesToolChest();
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
	return mIsCasting;
}

bool ATheLastKnightCharacter::CanCast(InputAction action) const
{
	return mAbilitiesToolChest.CanCast(action, mAttributes.GetMana());
}

void ATheLastKnightCharacter::Cast()
{
	TLN::Action action;
	if (mInputHandler->IsActionPressed(InputAction::ABILITY1))
	{
		action = mInputHandler->GetAction(InputAction::ABILITY1);
	} 
	else if (mInputHandler->IsActionPressed(InputAction::ABILITY2))
	{
		action = mInputHandler->GetAction(InputAction::ABILITY2);
	}

	mIsCasting = true;
	auto ability = mAbilitiesToolChest.GetAbility(InputAction::ABILITY1);
	mAttributes.SetMana(mAttributes.GetMana() - ability->GetCastCost());
	ability->Cast(GetActorLocation());
}

void ATheLastKnightCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	mStatesMachine->Update(DeltaSeconds);

	UE_LOG(LogTemp, Log, TEXT("Character FSM state: %d"), mStatesMachine->GetCurrentState()->GetID());
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

	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &ATheLastKnightCharacter::Ability1);
	PlayerInputComponent->BindAction("Ability1", IE_Released, this, &ATheLastKnightCharacter::StopAbility1);


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

void ATheLastKnightCharacter::CreateStatesMachine()
{
	mCharacterFSMContext = std::make_shared<CharacterContext>(this, mInputHandler);
	mStatesMachine = std::make_unique<core::utils::FSM::StatesMachine<CharacterState, CharacterContext>>(mCharacterFSMContext);

	auto idle = std::make_shared<Idle>();
	auto walk = std::make_shared<Walk>();
	auto cast = std::make_shared<Casting>();

	mStatesMachine->AddState(idle);
	mStatesMachine->AddState(walk);
	mStatesMachine->AddState(cast);
	
	//from Idle
	mStatesMachine->AddTransition(std::make_unique<EnterWalk>(idle, walk));
	mStatesMachine->AddTransition(std::make_unique<EnterCast>(idle, cast));

	//from Walk
	mStatesMachine->AddTransition(std::make_unique<EnterIdle>(walk, idle));
	mStatesMachine->AddTransition(std::make_unique<EnterCast>(idle, cast));

	//from Cast
	mStatesMachine->AddTransition(std::make_unique<EnterIdle>(cast, idle));
	mStatesMachine->AddTransition(std::make_unique<EnterWalk>(cast, walk));

	mStatesMachine->SetInitialState(idle->GetID());
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

void ATheLastKnightCharacter::AddDefaultAbilitiesToTheAbilitiesToolChest()
{
	auto bpHealthAbility = GetWorld()->SpawnActor<ABPHealthAbility>(ABPHealthAbility::StaticClass());
	auto healthAbility = std::make_shared<HealthAbility>(bpHealthAbility);

	auto index = mAbilitiesToolChest.AddAbility(healthAbility);
	mAbilitiesToolChest.BindAbilityToToolBelt(TLN::InputAction::ABILITY1, index);
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
	if ((Controller != NULL) && (Value != 0.0f))
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
	if ( (Controller != NULL) && (Value != 0.0f) )
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

void ATheLastKnightCharacter::Ability1()
{
	mInputHandler->Ability1(true);
	//mIsAbility1Pressed = true;
	//mAbility1KeyHoldTime = 0.0f;
}

void ATheLastKnightCharacter::StopAbility1()
{
	mInputHandler->Ability1(false);
	//mIsAbility1Pressed = false;
}
