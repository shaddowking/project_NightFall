#pragma once

#include "Blueprint/UserWidget.h"

#include "Abilities/GameplayAbility.h"

#include "NF_AbilityUI.generated.h"

class UAbilityDataAsset;
class UNF_AbilityBase;

UCLASS()
class UAbilityUI : public UUserWidget
{
GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (ExposeOnSpawn = true),BlueprintReadWrite)
	FGameplayAbilitySpecHandle AbilitySpec;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateIcon(UAbilityDataAsset* ability, FGameplayAbilitySpecHandle Handle);

protected:

	UPROPERTY( BlueprintReadWrite)
	UNF_AbilityBase* currentAbility = nullptr;
};