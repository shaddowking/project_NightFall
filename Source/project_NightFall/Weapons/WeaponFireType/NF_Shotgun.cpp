#include "NF_Shotgun.h"
#include "../NF_WeaponComponent.h"

void AShotgun::GunFire()
{
	FHitResult AimHit;

	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * BulletRange, ECollisionChannel::ECC_Visibility);

	AimLocation = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	bulletsPerLine = FMath::Sqrt(PelletsPerShot);

	StartAimLocation = FVector{ AimLocation.X + XBulletSpred,AimLocation.Y,AimLocation.Z + ZBulletSpred };

	XdistanceBetweenPellets = XBulletSpred / bulletsPerLine;
	ZdistanceBetweenPellets = ZBulletSpred / bulletsPerLine;

	
}
