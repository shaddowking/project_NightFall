#pragma once

#include "../NF_WeaponBase.h"

#include "NF_Shotgun.generated.h"

UCLASS()
class AShotgun : public AWeaponBase 
{
	GENERATED_BODY()

public:

	void GunFire() override;


	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gun Stats")
	float PelletsPerShot = 16;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun Stats")
	int ZBulletSpred = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun Stats")
	int XBulletSpred = 100;



private:

	FVector AimLocation;

	FVector StartAimLocation;
	float bulletsPerLine;
	float XdistanceBetweenPellets;
	float ZdistanceBetweenPellets;
	
};