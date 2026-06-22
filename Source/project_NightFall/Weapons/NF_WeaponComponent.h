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

	virtual void RelodeWeapon()
	{
		OnRelode.Broadcast();

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
	FNFWeaponSigniture OnRelode;
	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnActivate;
	UPROPERTY(BlueprintAssignable)
	FNFWeaponSigniture OnDeactivate;



	UPROPERTY(BlueprintReadOnly)
	FVector ViewOrigin;
	UPROPERTY(BlueprintReadOnly)
	FVector ViewForward;

	

	UPROPERTY(BlueprintReadWrite)
	ANF_Player* Owner = nullptr;

	

	UPROPERTY()
	AWeaponBase* OwningGun = nullptr;

};