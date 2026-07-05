#include "NF_CargoGrid.h"
#include "Components/BoxComponent.h"
#include "NF_ItemBox.h"


void ACargoGrid::BeginPlay()
{
	Super::BeginPlay();
	GenerateCargoGrid();
	BoxGhost = GetWorld()->SpawnActor<AActor>(GhostTemplate);
	BoxGhost->SetActorHiddenInGame(true);
}

void ACargoGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	if (CurrentCargoBox)
	{

	}
}

ACargoGrid::ACargoGrid()
{

	root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = root;

	GridStart = CreateDefaultSubobject<USceneComponent>("GridStart");
	GridStart->SetupAttachment(root);

	CargoSnapingRange = CreateDefaultSubobject<UBoxComponent>("CargoSnapingRage");
	CargoSnapingRange->SetupAttachment(root);
	CargoSnapingRange->OnComponentBeginOverlap.AddDynamic(this, &ACargoGrid::OnCargoBoxEnter);
	CargoSnapingRange->OnComponentEndOverlap.AddDynamic(this, &ACargoGrid::OnCargoBoxExit);
}

void ACargoGrid::GenerateCargoGrid()
{
	FVector StartPos = GridStart->GetComponentLocation();
	FVector NodePosOfsett = FVector{ StartPos + (SlotSize / 2) };
	FVector NodePos;
	FCargoNode node;
	int	ID = 0;
	for (size_t z = 0; z < CGrid_Z; z++)
	{
		for (size_t x = 0; x < CGrid_X; x++)
		{
			for (size_t y = 0; y <CGrid_Y; y++)
			{
				NodePos = FVector{ NodePosOfsett.X + (x * SlotSize),NodePosOfsett.Y + (y * SlotSize) ,NodePosOfsett.Z + (z * SlotSize)};
				node.Location = NodePos;
				node.id = ID;
				
				if (z == 0)
				{
					node.IsAvalable = true;
				}
				DebugCargoGrid(NodePos);

				CargoGrid.Add(node);
				ID++;
			}
		}
	}
}

void ACargoGrid::SnapBoxToGrid()
{
	

	CurrentNode = CargoGrid[0];
	bestdistance = std::numeric_limits<float>::max();
	for (FCargoNode& node : CargoGrid) {

		if (node.IsOcupide == false&& node.IsAvalable && BoxGhost->GetActorLocation() != node.Location)
		{
			newDist = FVector::Distance(CurrentCargoBox->GetActorLocation(), node.Location);
			if (newDist < bestdistance)
			{
				CurrentNode = node;
				bestdistance = newDist;
			}
		}

	}
	BoxGhost->SetActorLocation(CurrentNode.Location);
}

void ACargoGrid::PlaceBox()
{
	if (BoxGhost)
	{
		CurrentCargoBox->SetActorLocation(BoxGhost->GetActorLocation());
		CurrentCargoBox = nullptr;
		BoxGhost->SetActorHiddenInGame(true);
		CargoGrid[CurrentNode.id].IsAvalable = false;
		if (CurrentNode.id+ (CGrid_Y + CGrid_X) < CargoGrid.Num())
		{
			CargoGrid[CurrentNode.id + (CGrid_Y + CGrid_X)].IsAvalable = false;

		}
	}
}

void ACargoGrid::OnCargoBoxEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentCargoBox = Cast<AItemBox>(OtherActor);
	if (CurrentCargoBox)
	{
		BoxGhost->SetActorHiddenInGame(false);
	}
	
}

void ACargoGrid::OnCargoBoxExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AItemBox>(OtherActor) && OtherActor == CurrentCargoBox)
	{
		CurrentCargoBox = nullptr;
	}
}
