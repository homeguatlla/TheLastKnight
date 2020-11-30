// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <memory>
#include "Components/ActorComponent.h"
#include "MeshColorComponent.generated.h"

class UMaterialInstanceDynamic;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THELASTKNIGHT_API UMeshColorComponent : public UActorComponent
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;

	private:
		void BindToDelegate();
		UFUNCTION()
		void OnEnableDebugMode(bool enable);
		UFUNCTION()
		void OnNextNPC(const ANPCAIController* controller);
		UFUNCTION()
		void OnPreviousNPC(const ANPCAIController* controller);

		FString GetAgentName() const;
		UMaterialInstanceDynamic* CreateAndAssignMaterialInstanceDynamicToMesh();
		void SetColor(const FColor& color);
	
	public:
		/** Color to set into the mesh material as ColorBase */
		UPROPERTY(EditAnywhere, Category = "Mesh Color")
		FColor mColor;

	private:
		FString mAgentName;
		UMaterialInstanceDynamic* mDynamicMaterial;
};
