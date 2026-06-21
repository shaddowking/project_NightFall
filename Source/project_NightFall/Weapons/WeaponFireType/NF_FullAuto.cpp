#include "NF_FullAuto.h"
#include "../NF_WeaponComponent.h"

void AFullAuto::GunFire()
{
	GunComponent->Owner->bCanShoot = false;

	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 5000, ECollisionChannel::ECC_Visibility);
	GunComponent->Owner->CreateDebugLine(GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * 50000);
	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;



	SpawnBullet(AimPoint, FirePoint);

	CurrentAmmo--;



	FTimerHandle GunTimerHandle;

	GetWorldTimerManager().SetTimer(GunTimerHandle, this, &AFullAuto::ResetCanShoot, TimeBetweenShots, false);

}
