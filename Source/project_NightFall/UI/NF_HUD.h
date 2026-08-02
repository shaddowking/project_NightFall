#pragma once

#include "GameFramework/HUD.h"

#include "NF_HUD.generated.h"

class UAbilityUI;
class UPlayerHud;

UCLASS()
class A_NF_HUD : public AHUD {

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	UAbilityUI* primaryAbilityUI = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UAbilityUI* secondaryAbilityUI = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UPlayerHud* PlayerHud = nullptr;

};