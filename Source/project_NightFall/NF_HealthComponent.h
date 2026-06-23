#pragma once
#include "Components/ActorComponent.h"
#include "NF_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNFHPSigniture);


UCLASS()
class UHealthComponent : public UActorComponent
{
GENERATED_BODY()

public:

	void BeginPlay() override;


	void Damage(float damage)
	{
		CurrentHealth -= damage;
		OnDamage.Broadcast();
		if (CurrentHealth <= 0)
		{
			OnDeath.Broadcast();
		}
	}

	void Heal(float value)
	{
		CurrentHealth += value;

		if (CurrentHealth > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
	}


	float CurrentHealth;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(BlueprintAssignable)
	FNFHPSigniture OnDamage;

	UPROPERTY(BlueprintAssignable)
	FNFHPSigniture OnDeath;
};