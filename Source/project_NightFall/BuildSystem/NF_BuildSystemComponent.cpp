#include "NF_BuildSystemComponent.h"
#include "../NF_Player.h"
#include "../NF_GameInstance.h"
#include "NF_GridManager.h"
#include "NF_BuildableDataAsset.h"

void UBuildSystemComponent::BuildmodeStart()
{

	if (!GameInstance)
	{
		GameInstance = Cast<UNF_GameInstance>(GetWorld()->GetFirstPlayerController()->GetGameInstance());
	}
	SwitchBuilding(0);

	Player->GetWorldTimerManager().SetTimer(BuildmodeTimerHandle, this, &UBuildSystemComponent::BuildmodeTick, 0.1, false);
	bIsBuildModeActive = true;
}

void UBuildSystemComponent::BuildmodeTick()
{
	if (Player)
	{
		currentNode = GameInstance->BuildGridManager->GetClosestNode(Player->GetPlacablePoint(BuildRage, PlacableNormal));
		TargetLocation = currentNode.Location;
		if (createdBuilding)
		{
			createdBuilding->SetActorLocation(TargetLocation);
		}


		if (bIsBuildModeActive)
		{
			Player->GetWorldTimerManager().SetTimer(BuildmodeTimerHandle, this, &UBuildSystemComponent::BuildmodeTick, 0.1, false);
		}
	}

	

}

void UBuildSystemComponent::PlaceBuilding()
{
	if (bIsBuildModeActive)
	{
		currentNode = GameInstance->BuildGridManager->GetClosestNode(Player->GetPlacablePoint(BuildRage, PlacableNormal));
		createdBuilding->SetActorLocation(TargetLocation);
		createdBuilding->SetupCreatedBuilding();
		createdBuilding->BuildingPlaced(currentBuildingDAT->XGridSize,currentBuildingDAT->YGridSize, currentNode.id,currentNode.Location,currentNode);

		createdBuilding = nullptr;
		BuildmodeEnd();
	}
}

void UBuildSystemComponent::SwitchBuilding(int value)
{
	if (createdBuilding)
	{
		avalableGhostBuilding.Add(createdBuilding);
		createdBuilding->SetActorHiddenInGame(true);
	}
	createdBuilding = nullptr;
	currentID += value;
	if (currentID < 0)
	{
		currentID = 0;
	}
	else if (currentID > buildingList.Num())
	{
		currentID = buildingList.Num();
	}

	currentBuildingDAT = buildingList[currentID];

	createdBuilding = GetAvalableGhostBuilding(currentBuildingDAT->BuildingName);

	if (!createdBuilding)
	{
		createdBuilding = GetWorld()->SpawnActor<ABuildable>(currentBuildingDAT->buildingTemplate,TargetLocation, FRotator::ZeroRotator);
		createdBuilding->SetupGhost();
		createdBuilding->BuildingName = currentBuildingDAT->BuildingName;
		
	}
	else
	{
		createdBuilding->SetActorHiddenInGame(false);
	}

	// Update UI and Ghost
}

void UBuildSystemComponent::BuildmodeEnd()
{
	if (createdBuilding)
	{
		createdBuilding->SetActorHiddenInGame(true);
	}
	createdBuilding = nullptr;
	bIsBuildModeActive = false;
	
	Player->StartResetShoot(1);

}

ABuildable* UBuildSystemComponent::GetAvalableGhostBuilding(FString BuildingName)
{
	AvalableBuilding = nullptr;
	

	for(ABuildable* building : avalableGhostBuilding)
	{
		if (AvalableBuilding)
		{
			continue;
		}
		if (building->BuildingName == BuildingName)
		{
			AvalableBuilding = building;
			continue;
		}
	}
	if (AvalableBuilding)
	{
		avalableGhostBuilding.Remove(AvalableBuilding);
	}
	return AvalableBuilding;
}
