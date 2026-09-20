#include "NF_LightTurret.h"
#include "../Enemy/NF_EnemyBase.h"
#include "../Weapons/NF_Projectile.h"
#include "../NF_ProjectilePoolComp.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"


void ALightTurret::TurretFire()
{
	if (!currentEnemy)
	{
		return;
	}
	if (CanShoot(currentEnemy))
	{
		FHitResult AimHit;
		GetWorld()->LineTraceSingleByChannel(AimHit, Aimpoint->GetComponentLocation(), currentEnemy->GetActorLocation(), ECollisionChannel::ECC_Visibility);
		FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

		FVector ShootDirection = AimPoint - Aimpoint->GetComponentLocation();


		CurentBullet = projectilePoolComp->GetAvalableProjectile();

		CurentBullet->SetActorLocationAndRotation(FirePoint->GetComponentLocation(), UKismetMathLibrary::MakeRotFromX(ShootDirection));

		CurentBullet->Speed = BulletSpeed;
		CurentBullet->Damage = turretDamage;
		CurentBullet->ProjectileActivate();
		CurentBullet = nullptr;
	}
	
	
	Super::TurretFire();
}

bool ALightTurret::CanShoot(ACharacter* target)
{
	bestdistance = Radius * 10;
	FTransform targetTransform = target->GetActorTransform();
	FVector directionToTarget = (targetTransform.GetLocation() - GetActorLocation()).GetSafeNormal();
	params.ClearIgnoredActors();
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(target);

	if (FVector::DotProduct(GetActorLocation(), directionToTarget) < angle)
	{
		float distanceToTarget = FVector::Distance(GetActorLocation(), targetTransform.GetLocation());
		GetWorld()->LineTraceSingleByChannel(FovHit, GetActorLocation(), targetTransform.GetLocation(), ECollisionChannel::ECC_Visibility, params);
		if (!FovHit.bBlockingHit)
		{
			if (distanceToTarget < bestdistance)
			{
				bestdistance = distanceToTarget;
				TargetActor = target;
			}
		}
	}

	return TargetActor != nullptr;
}
