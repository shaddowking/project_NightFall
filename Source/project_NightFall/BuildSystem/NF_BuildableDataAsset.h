#pragma once 


#include "NF_Buildable.h"

#include "NF_BuildableDataAsset.generated.h"


UCLASS()
class UBuildableDataAsset : public UDataAsset
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuildable> buildingTemplate;

	UPROPERTY(EditInstanceOnly)
	FString BuildingName;

	UPROPERTY(EditInstanceOnly)
	int XGridSize = 0;
	UPROPERTY(EditInstanceOnly)
	int YGridSize = 0;
};