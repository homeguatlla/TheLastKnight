#include "GroundCircleComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Agents/AI/NPCAIController.h>



void UGroundCircleComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BindToDelegate();

	this->SetVisibility(false);
	mAgentName = GetAgentName();
}

void UGroundCircleComponent::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));
	if (gameMode)
	{
		auto eventDispatcher = gameMode->GetEventDispatcher();

		eventDispatcher->OnEnableDebugMode.AddDynamic(this, &UGroundCircleComponent::OnEnableDebugMode);
		eventDispatcher->OnNextNPC.AddDynamic(this, &UGroundCircleComponent::OnNextNPC);
		eventDispatcher->OnPreviousNPC.AddDynamic(this, &UGroundCircleComponent::OnPreviousNPC);
	}
}

void UGroundCircleComponent::OnEnableDebugMode(bool enable)
{
	if(!enable)
	{
		this->SetVisibility(false);
	}
}

void UGroundCircleComponent::OnNextNPC(const ANPCAIController* controller)
{
	this->SetVisibility(mAgentName == controller->GetAgentName());
}

void UGroundCircleComponent::OnPreviousNPC(const ANPCAIController* controller)
{
	this->SetVisibility(mAgentName == controller->GetAgentName());
}

FString UGroundCircleComponent::GetAgentName() const
{
	FString name = FString("");

	auto actor = Cast<ACharacter>(GetOwner());
	if (actor != nullptr)
	{
		auto npcAIController = Cast<ANPCAIController>(actor->GetController());
		if (npcAIController != nullptr)
		{
			name = npcAIController->GetAgentName();
		}
	}
	return name;
}