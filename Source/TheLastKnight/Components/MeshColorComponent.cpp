#include "MeshColorComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Materials/MaterialInterface.h>
#include <Components/SkeletalMeshComponent.h>
#include <TheLastKnight/TheLastKnightGameMode.h>
#include <TheLastKnight/Agents/AI/NPCAIController.h>

const FColor DEFAULT_COLOR(FColor::White);
const FName MATERIAL_ATTRIBUTE_COLORBASE("ColorBase");

void UMeshColorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BindToDelegate();

	mAgentName = GetAgentName();
	mDynamicMaterial = CreateAndAssignMaterialInstanceDynamicToMesh();
}

void UMeshColorComponent::BindToDelegate()
{
	auto gameMode = Cast<ATheLastKnightGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));
	if (gameMode)
	{
		auto eventDispatcher = gameMode->GetEventDispatcher();

		eventDispatcher->OnEnableDebugMode.AddDynamic(this, &UMeshColorComponent::OnEnableDebugMode);
		eventDispatcher->OnNextNPC.AddDynamic(this, &UMeshColorComponent::OnNextNPC);
		eventDispatcher->OnPreviousNPC.AddDynamic(this, &UMeshColorComponent::OnPreviousNPC);
	}
}

void UMeshColorComponent::OnEnableDebugMode(bool enable)
{
	if(!enable)
	{
		SetColor(DEFAULT_COLOR);
		
		/*
		TArray<UStaticMeshComponent*> meshComponents;
		GetOwner()->GetComponents<UStaticMeshComponent>(meshComponents);
		for (auto i = 0; i < meshComponents.Num(); i++)
		{
			auto staticMeshComponent = meshComponents[i];
			auto staticMesh = staticMeshComponent->StaticMesh;
			auto material = staticMesh->GetMaterial(0);
			mDynamicMaterial
		}*/
	}
}

void UMeshColorComponent::OnNextNPC(const FString& name)
{
	SetColor( mAgentName == name ? mColor : DEFAULT_COLOR);
}

void UMeshColorComponent::OnPreviousNPC(const FString& name)
{
	SetColor(mAgentName == name ? mColor : DEFAULT_COLOR);
}

FString UMeshColorComponent::GetAgentName() const
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

UMaterialInstanceDynamic* UMeshColorComponent::CreateAndAssignMaterialInstanceDynamicToMesh()
{
	UMaterialInstanceDynamic* dynamicMaterial = nullptr;

	auto actor = Cast<ACharacter>(GetOwner());
	if(actor != nullptr)
	{
		auto meshComponent = actor->FindComponentByClass<USkeletalMeshComponent>();
		if(meshComponent != nullptr)
		{ 
			auto material = meshComponent->GetMaterial(0);
			if(material != nullptr)
			{ 
				dynamicMaterial = UMaterialInstanceDynamic::Create(material, NULL);
				if(dynamicMaterial != nullptr)
				{
					meshComponent->SetMaterial(0, dynamicMaterial);
				}
			}
		}
	}

	check(dynamicMaterial != nullptr);

	return dynamicMaterial;
}

void UMeshColorComponent::SetColor(const FColor& color)
{
	mDynamicMaterial->SetVectorParameterValue(MATERIAL_ATTRIBUTE_COLORBASE, color);
}