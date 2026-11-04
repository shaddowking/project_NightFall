#pragma once
#include "GameFramework/Actor.h"
#include "NF_SnapingPoints.generated.h"

class USphereComponent;

UCLASS()
class ASnapingPoint : public AActor
{
GENERATED_BODY()

public:

	ASnapingPoint();

	UPROPERTY( EditAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* SnapingPoint = nullptr;

	UPROPERTY(EditAnywhere)
	USphereComponent* SnapingPointRange = nullptr;

	bool IsOcupide = false;
};