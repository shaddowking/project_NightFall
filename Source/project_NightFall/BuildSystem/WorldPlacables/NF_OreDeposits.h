#pragma once
#include "GameFramework/Actor.h"
#include "../NF_SnapingPoints.h"
#include "NF_OreDeposits.generated.h"

class UItemDataAsset;

UCLASS()
class AOreDeposit : public ASnapingPoint 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UItemDataAsset* ItemToGive = nullptr;
};