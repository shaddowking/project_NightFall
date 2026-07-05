#include "NF_GridManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NF_SnapingPoints.h"

void ANF_GridManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateBuildingGrid();

	for(FNode node : ValidBuildGrid)
	{
		DebugBuildGrid(node.Location, CellSize);
	}

}

FVector ANF_GridManager::GetClosestNode(FVector AimPoint)
{
	ClosestNode = ValidBuildGrid[0];
	bestdistance = std::numeric_limits<float>::max();
	for (FNode& node : ValidBuildGrid) {

		if (node.IsOcupide == false)
		{
			newDist = FVector::Distance(AimPoint, node.Location);
			if (newDist < bestdistance)
			{
				ClosestNode = node;
				bestdistance = newDist;
			}
		}

	}

	return ClosestNode.Location;
}

bool ANF_GridManager::IsCellValid(FVector CellPos)
{
	if (!ValidZLine.Contains(CellPos.Z))
	{
		GetWorld()->LineTraceSingleByChannel(ValidHit, CellPos, CellPos + FVector::DownVector * (CellSize / 2), ECollisionChannel::ECC_Visibility);


		if (ValidHit.bBlockingHit)
		{
			return true;
		}
	}
	return false;
}

void ANF_GridManager::GenerateBuildingGrid()
{
	FVector ManagerPos = GetActorLocation();
	FNode NewNode;
	FVector cellExtent = FVector{ CellSize,CellSize,CellSize };


	for (size_t z = 0; z < Grid_Z; z++)
	{
		
		for (size_t x = 0; x < Grid_X; x++)
		{
			for (size_t y = 0; y < Grid_Y; y++)
			{
				NewCell = FVector{ ManagerPos.X + (x * CellSize),ManagerPos.Y + (y * CellSize),ManagerPos.Z + (z * CellSize) };
				if (IsCellValid(NewCell))
				{
					OutActors.Empty();

					UKismetSystemLibrary::BoxOverlapActors(this, NewCell, cellExtent, ObjectTypes, ASnapingPoint::StaticClass(), ActorsToIgnore, OutActors);
					ValidZLine.Add(z);
					if (OutActors.Num() <= 0)
					{
						NewNode.Location = NewCell;
						ValidBuildGrid.Add(NewNode);
					}
					
				}
			}
		}
	}
}
