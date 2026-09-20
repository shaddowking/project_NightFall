#include "NF_TurretBase.h"
#include "../NF_ProjectilePoolComp.h"
#include "Components/SphereComponent.h"
#include "../Enemy/NF_EnemyBase.h"
#include "../NF_HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../NF_GameInstance.h"
#include "../BuildSystem/NF_GridManager.h"

ANF_TurretBase::ANF_TurretBase()
{
	projectilePoolComp = CreateDefaultSubobject<UProjectilePoolComp>("projectilePoolCop");

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Aimpoint = CreateDefaultSubobject<USceneComponent>("Aimpoint");
	Aimpoint->SetupAttachment(Root);

	ZRotPoint = CreateDefaultSubobject<USceneComponent>("ZRotPoint");
	ZRotPoint->SetupAttachment(Root);

	YRotPoint = CreateDefaultSubobject<USceneComponent>("YRotPoint");
	YRotPoint->SetupAttachment(ZRotPoint);
	
	FirePoint = CreateDefaultSubobject<USceneComponent>("FirePoint");
	FirePoint->SetupAttachment(YRotPoint);





	TurretRange = CreateDefaultSubobject<USphereComponent>("TurretRange");
	TurretRange->SetupAttachment(Root);
	TurretRange->OnComponentBeginOverlap.AddDynamic(this, &ANF_TurretBase::OnEnemyEnter);
	TurretRange->OnComponentEndOverlap.AddDynamic(this, &ANF_TurretBase::OnEnemyExit);

	PrimaryActorTick.bCanEverTick = true;
}

bool ANF_TurretBase::CanShoot(ACharacter* target)
{
	return false;
}

void ANF_TurretBase::TurretFire()
{
	if (currentEnemy->HPComp->bIsDead)
	{
		currentEnemy = FindNextTarget();
	}
	else if(currentEnemy)
	{

		GetWorldTimerManager().SetTimer(turretTimerHandle, this, &ANF_TurretBase::TurretFire, TimeBetweenFire, false);

	}
}

void ANF_TurretBase::BeginPlay()
{
	Super::BeginPlay();

	TurretAmmo = MaxTurretAmmo;
}

void ANF_TurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentEnemy)
	{
		TurretDirection = currentEnemy->GetActorLocation() - ZRotPoint->GetComponentLocation();
		TurretRotation = UKismetMathLibrary::MakeRotFromX(TurretDirection);

		// fix this
		ZRotPoint->SetRelativeRotation(FMath::RInterpTo(ZRotPoint->GetComponentRotation(), FRotator{ 0,TurretRotation.Yaw,0 }, DeltaTime, InterpSpeed));
		YRotPoint->SetRelativeRotation(FMath::RInterpTo(YRotPoint->GetComponentRotation(), FRotator{ TurretRotation.Pitch,0,0 }, DeltaTime, InterpSpeed));
		/*
		ZRotPoint->SetRelativeRotation(FRotator{0,TurretRotation.Yaw,0});
		YRotPoint->SetRelativeRotation(FRotator{ TurretRotation.Pitch,0,0});
		*/

	}
}



void ANF_TurretBase::OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ANF_EnemyBase>(OtherActor))
	{
		UpdateTargetList();
		if (!currentEnemy)
		{
			currentEnemy = FindNextTarget();
			if (currentEnemy)
			{
				TurretFire();
			}
		}
	}
	
}

void ANF_TurretBase::OnEnemyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ANF_EnemyBase>(OtherActor))
	{
		UpdateTargetList();
		if (OtherActor == currentEnemy)
		{
			currentEnemy = nullptr;
		}
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
