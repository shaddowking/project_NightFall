#include "NF_LightTurret.h"
#include "../Enemy/NF_EnemyBase.h"
#include "../Weapons/NF_Projectile.h"
#include "../NF_ProjectilePoolComp.h"
#include "Kismet/KismetMathLibrary.h"


void ALightTurret::TurretFire()
{
	if (!currentEnemy)
	{
		return;
	}
	FHitResult AimHit;
	GetWorld()->LineTraceSingleByChannel(AimHit, Aimpoint->GetComponentLocation(),currentEnemy->GetActorLocation(), ECollisionChannel::ECC_Visibility);
	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	FVector ShootDirection = AimPoint - Aimpoint->GetComponentLocation();

	
	CurentBullet = projectilePoolComp->GetAvalableProjectile();

	CurentBullet->SetActorLocationAndRotation(FirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

	CurentBullet->Speed = BulletSpeed;
	CurentBullet->Damage = turretDamage;
	CurentBullet->ProjectileActivate();
	CurentBullet = nullptr;
	
	Super::TurretFire();
}
