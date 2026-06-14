#pragma once

#include "GameFramework/Actor.h"

#include "NF_WeaponBase.generated.h"

class UWeaponComponent;
class ANF_Player;
class ANFProjectile;

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

	UPROPERTY(BlueprintReadWrite)
	ANF_Player* player = nullptr;




	UFUNCTION()
	virtual void GunFire();

	UFUNCTION()
	virtual void GunRealese();
	UFUNCTION()
	virtual void WeaponActivate();
	UFUNCTION()
	virtual void DeActivate();


	void SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint, float DamageModefire = 1);

	void ResetCanShoot();

protected:

	UPROPERTY();
	ANFProjectile* CurentBullet = nullptr;

};