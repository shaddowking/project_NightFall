#include "NF_Projectile.h"
#include "Components/SphereComponent.h"
#include "../NF_Player.h"

ANFProjectile::ANFProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("sphere");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ANFProjectile::OnProjectileHit);
	RootComponent = Sphere;
	PrimaryActorTick.bCanEverTick = true;
}

void ANFProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActive)
	{
		AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime, false);


		if (Duration <= 0)
		{
			ProjectileDeActivate();
		}
		else
		{
			Duration -= DeltaTime;
		}
	}
}

void ANFProjectile::ProjectileActivate()
{
	SetActorTickEnabled(true);
	Duration = MaxDuration;
	SetActorHiddenInGame(false);
	IsActive = true;
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ANFProjectile::ProjectileDeActivate()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	IsActive = false;
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



void ANFProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive)
	{
		AActor* HitActor = OtherActor;
		ANFProjectile* hitprojectile = Cast<ANFProjectile>(HitActor);
		if (HitActor && hitprojectile == nullptr && HitActor != Owningplayer)
		{
			// Readd when ading health component

			/*
			UHealthComponent* healthComponent = HitActor->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->TakeDamage(Damage);
				healthComponent = nullptr;
			}
			*/

		}

		if (HitActor != Owningplayer)
		{
			ProjectileDeActivate();
		}

		HitActor = nullptr;
		hitprojectile = nullptr;

	}
}
