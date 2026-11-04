#pragma once

#include "NF_ItemDataAsset.generated.h"

UCLASS()
class UItemDataAsset : public UDataAsset
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString ItemName;
};


