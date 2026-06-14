#include "NF_WeaponBase.h"
#include "NF_WeaponComponent.h"
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
	
	GunComponent->OwningGun = this;
}

void AWeaponBase::BeginPlay()
{
	GunComponent->CurrentAmmo = GunComponent->MaxAmmo;



}

void AWeaponBase::GunFire()
{
}

void AWeaponBase::GunRealese()
{
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
	FVector ShootDirection = AimPoint - GunFirePoint->GetComponentLocation();

	
	//CurentBullet = GunComponent->Owner->GetNextAvalableProjectile();

	CurentBullet->SetActorLocationAndRotation(GunFirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = GunComponent->BulletSpeed;
	CurentBullet->Damage = GunComponent->Damage;
	CurentBullet->ProjectileActivate();
	CurentBullet = nullptr;
	
}

void AWeaponBase::ResetCanShoot()
{
	GunComponent->Owner->bCanShoot = true;

}
