#include "NF_GridManager.h"
#include "Kismet/KismetSystemLibrary.h"

void ANF_GridManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateBuildingGrid();

	for(FNode cell : ValidBuildGrid)
	{
		DebugBuildGrid(cell.Location, CellSize / 2);
	}
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
	float WorldOfsetX = (Grid_X * CellSize * 0.5) - (CellSize * 0.5);
	float WorldOfsetY = (Grid_Y * CellSize * 0.5) - (CellSize * 0.5);
	float WorldOfsetZ = (Grid_Z * CellSize * 0.5) - (CellSize * 0.5);
	FNode NewNode;


	for (size_t z = 0; z < Grid_Z; z++)
	{
		for (size_t x = 0; x < Grid_X; x++)
		{
			for (size_t y = 0; y < Grid_Y; y++)
			{
				NewCell = FVector{ ManagerPos.X + (x * CellSize),ManagerPos.Y + (y * CellSize),ManagerPos.Z + (z * CellSize) };
				if (IsCellValid(NewCell))
				{
					ValidZLine.Add(z);
					NewNode.Location = NewCell;
					ValidBuildGrid.Add(NewNode);
				}
			}
		}
	}
}
