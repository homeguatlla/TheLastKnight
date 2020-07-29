#include "AgentAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AAgentAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), mWayPoints);

	GoToRandomWayPoint();
}

ATargetPoint* AAgentAIController::GetRandomWayPoint()
{
	auto index = FMath::RandRange(0, mWayPoints.Num() - 1);
	return Cast<ATargetPoint>(mWayPoints[index]);
}

void AAgentAIController::GoToRandomWayPoint()
{
	float acceptanceRadius = 10;
	auto result = MoveToActor(mWayPoints[0]/*GetRandomWayPoint()*/, acceptanceRadius);
}