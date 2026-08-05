#pragma once
#include "Abilities/GameplayAbility.h"
#include "NF_AbilityBase.generated.h"

class ANF_Player;

UCLASS()
class UNF_AbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void OnPrimaryPress();

	virtual void OnSecondaryPress();

	virtual void NF_AbilityEnd();


	 FGameplayAbilitySpecHandle handle;
	 const FGameplayAbilityActorInfo* actorInfo;
	 FGameplayAbilityActivationInfo activationInfo;
	 const FGameplayEventData* triggerEventData;

	 UPROPERTY(BlueprintReadWrite)
	 bool bColldownActive = false;

	 bool bIsAbilityActive = false;

	 UPROPERTY()
	 ANF_Player* player = nullptr;


};