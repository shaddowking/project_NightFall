#pragma once
#include "GameFramework/Actor.h"

#include "NF_Buildable.generated.h"

UCLASS()
class ABuildable : public AActor
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetupGhost();
	UFUNCTION(BlueprintImplementableEvent)
	void SetupCreatedBuilding();

	UPROPERTY()
	FString BuildingName;
protected:


};