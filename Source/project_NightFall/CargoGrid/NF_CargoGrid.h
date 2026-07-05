#pragma once
#include "GameFramework/Actor.h"
#include "NF_CargoGrid.generated.h"

USTRUCT(Blueprintable)
struct FCargoNode
{
	GENERATED_BODY()

	FVector Location;

	bool IsOcupide = false;
	bool IsAvalable = false;

	int id = -1;
};

class UBoxComponent;
class AItemBox;


UCLASS()
class ACargoGrid : public AActor
{
GENERATED_BODY()

public:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent)
	void DebugCargoGrid(FVector pos);

	ACargoGrid();

	UPROPERTY(EditAnywhere)
	UBoxComponent* CargoSnapingRange = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* GridStart = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* root= nullptr;

	UPROPERTY()
	AActor* BoxGhost = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> GhostTemplate;

	UPROPERTY(EditAnywhere)
	int CGrid_X;
	UPROPERTY(EditAnywhere)
	int CGrid_Y;
	UPROPERTY(EditAnywhere)
	int CGrid_Z;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float SlotSize = 50;


	void GenerateCargoGrid();
	void SnapBoxToGrid();
	void PlaceBox();


	UFUNCTION()
	void OnCargoBoxEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCargoBoxExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:

	UPROPERTY()
	AItemBox* CurrentCargoBox = nullptr;

	TArray<FCargoNode> CargoGrid;

	FCargoNode CurrentNode;

	float bestdistance;
	float newDist;	
};