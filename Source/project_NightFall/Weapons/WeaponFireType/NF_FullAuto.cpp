#include "NF_FullAuto.h"
#include "../NF_WeaponComponent.h"

void AFullAuto::GunFire()
{
	GunComponent->Owner->bCanShoot = false;


	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * BulletRange, ECollisionChannel::ECC_Visibility);
	GunComponent->Owner->CreateDebugLine(GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 50000);
	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;



	SpawnBullet(AimPoint, FirePoint);

	CurrentAmmo--;
	ShootsFired++;



	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AFullAuto::ResetCanShoot, TimeBetweenShots, false);

}
