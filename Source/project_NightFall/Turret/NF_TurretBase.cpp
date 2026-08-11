#include "NF_TurretBase.h"
#include "../NF_ProjectilePoolComp.h"
#include "Components/SphereComponent.h"
#include "../Enemy/NF_EnemyBase.h"
#include "../NF_HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

ANF_TurretBase::ANF_TurretBase()
{
	projectilePoolComp = CreateDefaultSubobject<UProjectilePoolComp>("projectilePoolCop");

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Aimpoint = CreateDefaultSubobject<USceneComponent>("Aimpoint");
	Aimpoint->SetupAttachment(Root);

	TurretRange = CreateDefaultSubobject<USphereComponent>("TurretRange");
	TurretRange->SetupAttachment(Root);
	TurretRange->OnComponentBeginOverlap.AddDynamic(this, &ANF_TurretBase::OnEnemyEnter);
	TurretRange->OnComponentEndOverlap.AddDynamic(this, &ANF_TurretBase::OnEnemyExit);
}

void ANF_TurretBase::TurretFire()
{
	if (currentEnemy->HPComp->bIsDead)
	{
		currentEnemy = FindNextTarget();
	}
}

void ANF_TurretBase::BeginPlay()
{
	Super::BeginPlay();

	TurretAmmo = MaxTurretAmmo;
}

void ANF_TurretBase::OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ANF_EnemyBase>(OtherActor))
	{
		UpdateTargetList();
	}
	
}

void ANF_TurretBase::OnEnemyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ANF_EnemyBase>(OtherActor))
	{
		UpdateTargetList();
	}
}

ANF_EnemyBase* ANF_TurretBase::FindNextTarget()
{
	UpdateTargetList();
	BestDistance = std::numeric_limits<float>::max();
	float currentDist;
	ANF_EnemyBase* enemy = nullptr;
	for(ANF_EnemyBase* target : ValidTargets)
	{
		currentDist = FVector::Dist(GetActorLocation(), target->GetActorLocation()); 
		if (currentDist < BestDistance)
		{
			enemy = target;
			BestDistance = currentDist;
		}
	}

	return enemy;
}

void ANF_TurretBase::UpdateTargetList()
{
	TurretRange->GetOverlappingActors(TargetsInRange, ANF_EnemyBase::StaticClass());
	FHitResult hitResult;
	ANF_EnemyBase* enemy = nullptr;
	ValidTargets.Empty();
	for(AActor* target : TargetsInRange)
	{
		if (Cast<ANF_EnemyBase>(target)->HPComp->bIsDead)
		{
			continue;
		}
		FCollisionQueryParams query;
		query.AddIgnoredActor(this);
		query.AddIgnoredActor(target);

		GetWorld()->LineTraceSingleByChannel(hitResult, Aimpoint->GetComponentLocation(), target->GetActorLocation(), ECollisionChannel::ECC_Visibility, query);

		if (hitResult.bBlockingHit == false)
		{
			enemy = Cast<ANF_EnemyBase>(target);
			ValidTargets.Add(enemy);
		}
	}

}
