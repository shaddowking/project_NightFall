#pragma once

#include "Components/ActorComponent.h"

#include "../NF_Player.h"

#include "NF_WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNFWeaponSigniture);

class AWeaponBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class UWeaponComponent : public UActorComponent
{
GENERATED_BODY()

public:

	virtual void UseWeapon(FVector origin = FVector::Zero(), FVector Forward = FVector::Zero())
	{
		ViewOrigin = origin;
		ViewForward = Forward;
		OnShoot.Broadcast();
	}

	virtual void RealeseWeapon()
	{
		OnRealese.Broadcast();
	}

	void ActivateWeapon()
	{
		OnActivate.Broadcast();
	}

	void DeactivateWeapon()
	{
		OnDeactivate.Broadcast();
	}

	

	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnShoot;
	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnRealese;
	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnActivate;
	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnDeactivate;



	UPROPERTY(BlueprintReadOnly)
	FVector ViewOrigin;
	UPROPERTY(BlueprintReadOnly)
	FVector ViewForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float Damage = 10;

	UPROPERTY(BlueprintReadWrite)
	ANF_Player* Owner = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float MaxAmmo = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float ExtraAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float RelodeTime = 2;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float BulletSpeed = 2000;

	UPROPERTY()
	AWeaponBase* OwningGun = nullptr;

};