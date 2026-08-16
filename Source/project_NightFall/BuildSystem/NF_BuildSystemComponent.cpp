#include "NF_BuildSystemComponent.h"

void UBuildSystemComponent::BuildmodeStart()
{
}

void UBuildSystemComponent::BuildmodeTick()
{
}

void UBuildSystemComponent::PlaceBuilding()
{
}

void UBuildSystemComponent::SwitchBuilding(int value)
{
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

	// Update UI and Ghost
}
