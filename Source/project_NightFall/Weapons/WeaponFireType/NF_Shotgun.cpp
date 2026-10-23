#include "NF_Shotgun.h"
#include "../NF_WeaponComponent.h"

void AShotgun::GunFire()
{
	GunComponent->Owner->bCanShoot = false;

	FVector ViewOrigin;
	FRotator ViewRotation;

	GunComponent->Owner-> GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();
	FVector ViewRight = ViewRotation.Quaternion().GetRightVector();
	FVector ViewUp = ViewRotation.Quaternion().GetUpVector();

	FHitResult AimHit;

	GetWorld()->LineTraceSingleByChannel(AimHit, GunComponent->ViewOrigin, GunComponent->ViewOrigin + GunComponent->ViewForward * BulletRange, ECollisionChannel::ECC_Visibility);

	AimLocation = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	bulletsPerLine = FMath::Sqrt(PelletsPerShot);

	//StartAimLocation = FVector{ AimLocation.X - XBulletSpred/2,AimLocation.Y,AimLocation.Z - ZBulletSpred / 2 };

	StartAimLocation = AimLocation + ViewRight * XBulletSpred / 2 - (ViewUp * ZBulletSpred / 2);
	
	//DrawDebugLine(FirePoint->GetComponentLocation(), StartAimLocation);

	XdistanceBetweenPellets = XBulletSpred / bulletsPerLine;
	ZdistanceBetweenPellets = ZBulletSpred / bulletsPerLine;

	FVector shootlocation;

	

	for (int x = 0; x < bulletsPerLine; x++)
	{
		for (int z = 0; z < bulletsPerLine; z++)
		{
			//shootlocation = FVector{ StartAimLocation.X + XdistanceBetweenPellets * x, StartAimLocation.Y,StartAimLocation.Z + ZdistanceBetweenPellets * z };
			shootlocation = StartAimLocation - (ViewRight * XdistanceBetweenPellets * x) + (ViewUp * ZdistanceBetweenPellets * z);
			//DrawDebugLine(FirePoint->GetComponentLocation(), shootlocation);
			SpawnBullet(shootlocation, FirePoint);

			
		}
	}
	CurrentAmmo--;
	ShootsFired++;
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AShotgun::ResetCanShoot, TimeBetweenShots, false);

	
}
