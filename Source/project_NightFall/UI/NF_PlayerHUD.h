#pragma once

#include "Blueprint/UserWidget.h"
#include "Abilities/GameplayAbility.h"
#include "NF_PlayerHUD.generated.h"

class UAbilityDataAsset;

UCLASS()
class UPlayerHud : public UUserWidget
{
GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateAbilityUI(bool bIsPrimaryAbility, UAbilityDataAsset* abilityDAT,FGameplayAbilitySpecHandle Handle);
};