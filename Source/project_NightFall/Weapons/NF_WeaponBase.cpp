#include "NF_WeaponBase.h"
#include "NF_WeaponComponent.h"
#include "../NF_ProjectilePoolComp.h"
#include "NF_Projectile.h"
#include "../NF_Player.h"
#include "Kismet/KismetMathLibrary.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("RootComonent");
	RootComponent = Root;

	FirePoint = CreateDefaultSubobject<USceneComponent>("FirePoint");
	FirePoint->SetupAttachment(Root);

	GunComponent = CreateDefaultSubobject<UWeaponComponent>("GunComponent");
	
	GunComponent->OnShoot.AddDynamic(this, &AWeaponBase::GunFire);
	GunComponent->OnRealese.AddDynamic(this, &AWeaponBase::GunRealese);
	GunComponent->OnActivate.AddDynamic(this, &AWeaponBase::WeaponActivate);
	GunComponent->OnDeactivate.AddDynamic(this, &AWeaponBase::DeActivate);
	GunComponent->OnRelode.AddDynamic(this, &AWeaponBase::GunRelode);

	

	projectilePoolComp = CreateDefaultSubobject<UProjectilePoolComp>("projectilePool");

}

void AWeaponBase::BeginPlay()
{

	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	GunComponent->OwningGun = this;



}

void AWeaponBase::GunFire()
{
}

void AWeaponBase::GunRealese()
{
}

void AWeaponBase::GunRelode()
{
	if (ExtraAmmo > 0 && bCanRelode && ShootsFired > 0)
	{

		bCanRelode = false;
		GetWorldTimerManager().SetTimer(RelodeTimerHandle, this, &AWeaponBase::RelodeFinished, RelodeTime, false);

	}

}

void AWeaponBase::WeaponActivate()
{
	SetActorHiddenInGame(false);
}


void AWeaponBase::DeActivate()
{
	SetActorHiddenInGame(true);
}

void AWeaponBase::SpawnBullet(FVector AimPoint, USceneComponent* GunFirePoint, float DamageModefire)
{
	ShootsFired++;
	
	FVector ShootDirection = AimPoint - GunFirePoint->GetComponentLocation();

	
	CurentBullet = projectilePoolComp->GetAvalableProjectile();

	CurentBullet->SetActorLocationAndRotation(GunFirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = BulletSpeed;
	CurentBullet->Damage = Damage;
	CurentBullet->ProjectileActivate();
	CurentBullet = nullptr;
	
}

void AWeaponBase::ResetCanShoot()
{
	GunComponent->Owner->bCanShoot = true;

}

void AWeaponBase::RelodeFinished()
{
	
	if (ShootsFired < ExtraAmmo)
	{
		CurrentAmmo = MaxAmmo;
		ExtraAmmo -= ShootsFired;
	}
	else
	{
		CurrentAmmo += ExtraAmmo;
		ExtraAmmo = 0;
	}

	//Update UI
	bCanRelode = true;
	ShootsFired = 0;
}
