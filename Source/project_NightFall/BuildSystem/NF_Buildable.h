#pragma once
#include "GameFramework/Actor.h"
#include "NF_GridManager.h"
#include "NF_BuildingTypeEnum.h"
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
	virtual void BuildingPlaced();
	UPROPERTY()
	FString BuildingName;


	UFUNCTION(BlueprintImplementableEvent)
	void EditCanBuildColor(bool CanBuild);

	UPROPERTY(EditAnywhere)
	bool bIsBuild = false;

	UPROPERTY(EditAnywhere)
	EBuildType buildtype = EBuildType::Grid;
protected:


};