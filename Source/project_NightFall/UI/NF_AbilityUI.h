#pragma once

#include "Blueprint/UserWidget.h"

#include "Abilities/GameplayAbility.h"

#include "NF_AbilityUI.generated.h"

class UAbilityDataAsset;

UCLASS()
class UAbilityUI : public UUserWidget
{
GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (ExposeOnSpawn = true),BlueprintReadWrite)
	FGameplayAbilitySpecHandle AbilitySpec;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateIcon(UAbilityDataAsset* ability, FGameplayAbilitySpecHandle Handle);
};