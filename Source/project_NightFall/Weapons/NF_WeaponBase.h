#pragma once

#include "GameFramework/Actor.h"

#include "NF_WeaponBase.generated.h"

class UWeaponComponent;
class ANF_Player;
class ANFProjectile;
class UProjectilePoolComp;

UCLASS()
class AWeaponBase : public AActor
{
GENERATED_BODY()

public:
	AWeaponBase();

	void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* FirePoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWeaponComponent* GunComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectilePoolComp* projectilePoolComp = nullptr;

	UPROPERTY(BlueprintReadWrite)
	ANF_Player* player = nullptr;




	UFUNCTION()
	virtual void GunFire();

	UFUNCTION()
	virtual void GunRealese();

	UFUNCTION()
	virtual void GunRelode();

	UFUNCTION()
	virtual void WeaponActivate();
	UFUNCTION()
	virtual void DeActivate();


	void SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint, float DamageModefire = 1);

	void ResetCanShoot();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float Damage = 10;

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

	bool bCanRelode = true;

protected:

	float ShootsFired = 0;

	UPROPERTY();
	ANFProjectile* CurentBullet = nullptr;

	FTimerHandle WeaponTimerHandle;

	void RelodeFinished();

	FTimerHandle RelodeTimerHandle;

};