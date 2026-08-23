#pragma once

#include "GameFramework/Actor.h"

#include "NF_GridManager.generated.h"


USTRUCT(Blueprintable)
struct FNode
{
	GENERATED_BODY()

	FVector Location;

	int id;

	bool IsOcupide = false;

};

USTRUCT(Blueprintable)
struct FChunk
{
	GENERATED_BODY()

	FVector Location;

	int id;

	TArray<FNode> NodesInChunk;

};

UCLASS()
class ANF_GridManager : public AActor
{

	GENERATED_BODY()

public:

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DebugBuildGrid(FVector pos, float extend);

	UFUNCTION(BlueprintImplementableEvent)
	void Debugchunk(int id);

	FNode GetClosestNode(FVector AimPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CellSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_X = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_Y = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Grid_Z = 100;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int chunkSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Chunk_X = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Chunk_Y = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Chunk_Z = 10;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FNode> ValidBuildGrid;

	TArray<FChunk> Chunks;


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


	int CX;
	int CY;
	int index;
	int XnodeAbounte;
	int YnodeAbounte;
	int TX;
	int TY;
	int TID;

};