#pragma once

#include "GameFramework/Actor.h"

#include "NF_GridManager.generated.h"


USTRUCT(Blueprintable)
struct FNode
{
	GENERATED_BODY()

	FVector Location;

	bool IsOcupide = false;

};

UCLASS()
class ANF_GridManager : public AActor
{

	GENERATED_BODY()

public:

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DebugBuildGrid(FVector pos, float extend);

	FVector GetClosestNode(FVector AimPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CellSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_X = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_Y = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_Z = 100;	
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FNode> ValidBuildGrid;


protected:

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OutActors;

private:


	FNode ClosestNode;
	float bestdistance = std::numeric_limits<float>::max();
	float newDist;


	FHitResult ValidHit;

	FVector NewCell;

	TArray<int> ValidZLine;

	bool IsCellValid(FVector CellPos);

	void GenerateBuildingGrid();




};