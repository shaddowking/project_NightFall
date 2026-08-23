#pragma once 
#include "Components/ActorComponent.h"
#include "NF_GridManager.h"
#include "NF_BuildSystemComponent.generated.h"

class ABuildable;
class UBuildableDataAsset;
class ANF_Player;
class UNF_GameInstance;

UCLASS()
class UBuildSystemComponent : public UActorComponent 
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<UBuildableDataAsset*> buildingList;

	UPROPERTY()
	UBuildableDataAsset* currentBuildingDAT;
	UPROPERTY()
	UNF_GameInstance* GameInstance = nullptr;

	UFUNCTION()
	void BuildmodeStart();
	UFUNCTION()
	void BuildmodeTick();
	UFUNCTION()
	void PlaceBuilding();
	UFUNCTION()
	void SwitchBuilding(int value);
	UFUNCTION()
	void BuildmodeEnd();


	UPROPERTY();
	ANF_Player* Player = nullptr;
	bool bIsBuildModeActive = false;

protected:

	UPROPERTY(EditInstanceOnly)
	float BuildRage = 1000;

private:


	ABuildable* GetAvalableGhostBuilding(FString BuildingName);

	TArray<ABuildable*> avalableGhostBuilding;

	UPROPERTY()
	ABuildable* createdBuilding = nullptr;
	UPROPERTY()
	ABuildable* AvalableBuilding = nullptr;

	FVector PlacableNormal;

	int currentID = 0;

	FTimerHandle BuildmodeTimerHandle;
	FVector TargetLocation;

	FNode currentNode;
};
