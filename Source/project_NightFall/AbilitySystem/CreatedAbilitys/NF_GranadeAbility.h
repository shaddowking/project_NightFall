#pragma once

#include "Abilities/GameplayAbility.h"
#include "NF_GranadeAbility.generated.h"

class AGrenade;

UCLASS()
class UGranadeAbility : public UGameplayAbility
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGrenade> grenadeTemplate;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;


};