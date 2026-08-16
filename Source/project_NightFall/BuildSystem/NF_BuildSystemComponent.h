#pragma once 
#include "Components/ActorComponent.h"
#include "NF_BuildSystemComponent.generated.h"

class ABuildable;
class UBuildableDataAsset;

UCLASS()
class UBuildSystemComponent : public UActorComponent 
{

	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	TArray<UBuildableDataAsset*> buildingList;

	UPROPERTY()
	UBuildableDataAsset* currentBuildingDAT;

	void BuildmodeStart();

	void BuildmodeTick();

	void PlaceBuilding();

	void SwitchBuilding(int value);

private:

	int currentID = 0;
};
