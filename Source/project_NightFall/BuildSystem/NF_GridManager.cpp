#include "NF_GridManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NF_SnapingPoints.h"
#include "../NF_GameInstance.h"

void ANF_GridManager::BeginPlay()
{
	Super::BeginPlay();

	GenerateBuildingGrid();
	Cast<UNF_GameInstance>(GetWorld()->GetFirstPlayerController()->GetGameInstance())->BuildGridManager = this;
	/*
	for(FChunk chunk : Chunks)
	{
		for(FNode node : chunk.NodesInChunk)
		{
			DebugBuildGrid(node.Location, CellSize);
		}
	}
	
	for (FNode node : ValidBuildGrid)
	{
		DebugBuildGrid(node.Location, CellSize);
	}
	*/
}

FNode ANF_GridManager::GetClosestNode(FVector AimPoint, int xNodes, int yNodes)
{
	ClosestNode = ValidBuildGrid[0];
	bestdistance = std::numeric_limits<float>::max();
	for (FNode& node : ValidBuildGrid) {

		if (IsNodeGroupValid(node,xNodes,yNodes))
		{
			newDist = FVector::Distance(AimPoint, node.Location);
			if (newDist < bestdistance)
			{
				ClosestNode = node;	
				bestdistance = newDist;
			}
		}

	}
	DebugSelectedNode(ClosestNode.Location, CellSize);
	return ClosestNode;
}

bool ANF_GridManager::IsNodeGroupValid(FNode startnode, int xNodes, int yNodes)
{
	GroupStart = ValidBuildGrid.Find(startnode);
	Currentid = GroupStart;
	bGroupeIsValid = false;



	for (size_t x = 0; x < xNodes; x++)
	{
		for (size_t y = 0; y < yNodes; y++)
		{
			Currentid = (GroupStart + x) + (Grid_Y * y);
			
			if (Currentid > ValidBuildGrid.Num()-1 || Currentid < 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Array oute of index");
				return false;
			}
			
			if (ValidBuildGrid[Currentid].IsOcupide == true)
			{
				bGroupeIsValid = false;
				return false;
			}
			else
			{
				bGroupeIsValid = true;
			}

		}
	}
	if (bGroupeIsValid)
	{
		return true;
	}
	return false;

}

void ANF_GridManager::SetNodesOcupide(int xNodes, int yNodes, int StartID, FVector NodePos, FNode StartNode)
{
	int IDStart = ValidBuildGrid.Find(StartNode);
	int id = IDStart;
	
	
	for (size_t x = 0; x < xNodes; x++)
	{
		for (size_t y = 0; y < yNodes; y++)
		{
			id = (IDStart + x) + (Grid_Y * y);
			ValidBuildGrid[id].IsOcupide = true;
			DebugCreatedNode(ValidBuildGrid[id].Location, CellSize);

		}
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
	FNode NewNode;
	FVector cellExtent = FVector{ CellSize,CellSize,CellSize };


	for (float z = 0; z < Grid_Z; z++)
	{
		
		for (float x = 0; x < Grid_X; x++)
		{
			for (float y = 0; y < Grid_Y; y++)
			{
				NewCell = FVector{ ManagerPos.X + (x * CellSize),ManagerPos.Y + (y * CellSize),ManagerPos.Z + (z * CellSize) };
				if (IsCellValid(NewCell))
				{
					OutActors.Empty();

					UKismetSystemLibrary::BoxOverlapActors(this, NewCell, cellExtent, ObjectTypes, ASnapingPoint::StaticClass(), ActorsToIgnore, OutActors);
					ValidZLine.Add(z);
					if (OutActors.Num() <= 0)
					{
						NewNode.GridLocation = FVector{ x,y,z };
						NewNode.Location = NewCell;
						NewNode.id = y * Grid_X + x;
						ValidBuildGrid.Add(NewNode);

					}
					
				}
			}
		}
	}

	// Chunk Generatin script : currentlry not used

	/*
	FChunk newChunk;
	for (size_t x = 0; x < Chunk_X; x++)
	{
		for (size_t y = 0; y < Chunk_Y; y++)
		{
			newChunk.id = x * Chunk_X + y;
			newChunk.Location = FVector{ ManagerPos.X + (x * CellSize*Chunk_X),ManagerPos.Y + (y * chunkSize*Chunk_Y),ManagerPos.Z };
			Chunks.Add(newChunk);
		}
	}

	XnodeAbounte = Grid_X / Chunk_X;
	YnodeAbounte = Grid_Y / Chunk_Y;

	for(FChunk& chunk : Chunks)
	{
		/*
		for (size_t x = 0; x < XnodeAbounte; x++)
		{
			CX = x + XnodeAbounte * chunk.id;
			for (size_t y = 0; y < YnodeAbounte; y++)
			{
				CY = y + YnodeAbounte * chunk.id;

				index = CX * Grid_X + CY;
				if (index > ValidBuildGrid.Num())
				{
					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, "Invlid ID");
				}
				else
				{
					chunk.NodesInChunk.Add(ValidBuildGrid[index]);

				}
			}
		}
		

	

		for (size_t y = 0; y < YnodeAbounte; y++)
		{
			CY = y + YnodeAbounte * chunk.id;
			for (size_t x = 0; x < XnodeAbounte; x++)
			{
				CX = x + XnodeAbounte * chunk.id;
				index = CX * Chunk_X + CY;
				if (index > ValidBuildGrid.Num())
				{
					TX = x;
					TY = y;
					TID = chunk.id;
					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, "Invlid ID");
				}
				else
				{
					chunk.NodesInChunk.Add(ValidBuildGrid[index]);

				}
			}

		}


	}

	*/

}
