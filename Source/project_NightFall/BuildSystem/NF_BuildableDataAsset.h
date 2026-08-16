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
};