#pragma once

#include "Abilities/GameplayAbility.h"
#include "NF_AbilityBase.h"

#include "AbilityDataAsset.generated.h"

UCLASS()
class UAbilityDataAsset : public UDataAsset {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UNF_AbilityBase> abilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString AbilityName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FSlateBrush AbilityIcon;
};