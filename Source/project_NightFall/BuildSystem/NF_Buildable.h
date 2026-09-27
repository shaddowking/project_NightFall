#pragma once
#include "GameFramework/Actor.h"
#include "NF_GridManager.h"
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

	virtual void BuildingPlaced(int X, int Y,int nodeID,FVector nodepos,FNode startNode);

	UPROPERTY()
	FString BuildingName;

	bool bIsBuild = false;
protected:


};