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

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SnapingPointRange = nullptr;
};