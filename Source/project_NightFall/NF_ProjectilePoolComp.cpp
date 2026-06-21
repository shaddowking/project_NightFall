#include "NF_ProjectilePoolComp.h"
#include "Weapons/NF_Projectile.h"

void UProjectilePoolComp::BeginPlay()
{
	Super::BeginPlay();

	GenerateProjectilePool();
}

void UProjectilePoolComp::GenerateProjectilePool()
{
	if (ProjectileClass)
	{
		ANFProjectile* Currentprojectile = nullptr;
		for (size_t i = 0; i < PoolSize; i++)
		{

			Currentprojectile = GetWorld()->SpawnActor<ANFProjectile>(ProjectileClass);
			ProjectilePool.Add(Currentprojectile);
			Currentprojectile->ProjectileDeActivate();

		}
		Currentprojectile = nullptr;
	}

}

ANFProjectile* UProjectilePoolComp::GetAvalableProjectile()
{
	AvalableProjectile = nullptr;
	for(ANFProjectile* projectile : ProjectilePool)
	{
		if (projectile->IsActive == false)
		{
			AvalableProjectile = projectile;
		}
	}
	if (AvalableProjectile == nullptr)
	{
		AvalableProjectile = GetWorld()->SpawnActor<ANFProjectile>(ProjectileClass);
		ProjectilePool.Add(AvalableProjectile);
		AvalableProjectile->ProjectileDeActivate();
	}
	AvalableProjectile->IsActive = true;
	return AvalableProjectile;
}
