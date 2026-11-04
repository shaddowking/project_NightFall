#include "NF_BuildSystemComponent.h"
#include "../NF_Player.h"
#include "../NF_GameInstance.h"
#include "NF_GridManager.h"
#include "NF_BuildableDataAsset.h"
#include "../Weapons/NF_WeaponComponent.h"
#include "NF_BuildingTypeEnum.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NF_SnapingPoints.h"

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
	if (Player && createdBuilding)
	{
		if (createdBuilding->buildtype == EBuildType::Grid)
		{
			currentNode = GameInstance->BuildGridManager->GetClosestNode(Player->GetPlacablePoint(BuildRage, PlacableNormal), currentBuildingDAT->XGridSize, currentBuildingDAT->YGridSize);
			TargetLocation = currentNode.Location;
			if (createdBuilding && GameInstance->BuildGridManager->IsNodeGroupValid(currentNode, currentBuildingDAT->XGridSize, currentBuildingDAT->YGridSize))
			{
				createdBuilding->SetActorLocation(TargetLocation);
			}
		}
		else if (createdBuilding->buildtype == EBuildType::Snappoint)
		{
			TargetLocation = Player->GetPlacablePoint(BuildRage, PlacableNormal);
			UKismetSystemLibrary::BoxOverlapActors(this, TargetLocation, FVector{5,5,5}, ObjectTypes, ASnapingPoint::StaticClass(), ActorsToIgnore, OutActors);
			if (OutActors.Num() > 0)
			{
				
				currentpoint = Cast<ASnapingPoint>(OutActors[0]);
				if (currentpoint->IsOcupide == false)
				{
					TargetLocation = currentpoint->SnapingPoint->GetComponentLocation();
					createdBuilding->SetActorLocation(TargetLocation);
					bIsOnSnapingPoint = true;
					createdBuilding->EditCanBuildColor(bIsOnSnapingPoint);
				}
				
			}
			else
			{
				bIsOnSnapingPoint = false;
				createdBuilding->SetActorLocation(TargetLocation);
				createdBuilding->EditCanBuildColor(bIsOnSnapingPoint);
			}

		}
		


		if (bIsBuildModeActive)
		{
			Player->GetWorldTimerManager().SetTimer(BuildmodeTimerHandle, this, &UBuildSystemComponent::BuildmodeTick, 0.1, false);
		}
	}

	

}

void UBuildSystemComponent::PlaceBuilding()
{
	if (bIsBuildModeActive && GameInstance->BuildGridManager->IsNodeGroupValid(currentNode, currentBuildingDAT->XGridSize, currentBuildingDAT->YGridSize) && createdBuilding->buildtype == EBuildType::Grid)
	{
		
		currentNode = GameInstance->BuildGridManager->GetClosestNode(Player->GetPlacablePoint(BuildRage, PlacableNormal), currentBuildingDAT->XGridSize, currentBuildingDAT->YGridSize);
		createdBuilding->SetActorLocation(TargetLocation);
		createdBuilding->SetupCreatedBuilding();
		createdBuilding->BuildingPlaced(currentBuildingDAT->XGridSize, currentBuildingDAT->YGridSize, currentNode.id, currentNode.Location, currentNode);
		

		createdBuilding = nullptr;
		currentpoint = nullptr;
		BuildmodeEnd();	
	}
	else if (createdBuilding->buildtype == EBuildType::Snappoint && bIsBuildModeActive && bIsOnSnapingPoint)
	{
		currentpoint->IsOcupide = true;
		createdBuilding->SetActorLocation(TargetLocation);
		createdBuilding->SetupCreatedBuilding();
		createdBuilding = nullptr;
		currentpoint = nullptr;
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
	else if (currentID > buildingList.Num()-1)
	{
		currentID = buildingList.Num()-1;
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
	Player->EquipType = EPlayerEquipTyper::Gun;
	Player->currentWeapon->ActivateWeapon();

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
