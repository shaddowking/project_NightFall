#pragma once

#include "Abilities/GameplayAbility.h"
#include "../NF_AbilityBase.h"
#include "NF_MineAbility.generated.h"

class AMine;

UCLASS()
class UMineAbility : public UNF_AbilityBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMine> mineTemplate;

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;




	void OnPrimaryPress() override;



private:

	void MineTick();

	FTimerHandle MineTimer;


	FRotator XRotation;
	FRotator YRotation;
	FRotator ZRotation;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> MineTargetingTemplate;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	AActor* MineTargeting = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector TargetNormal;
	FVector TargetLocation;
	FRotator CurrentTargetRotation;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator TargetingDirection;
	FRotator NormalDirection;
	FVector playerDirection;


};