#include "NF_Granade.h"
#include "Components/SphereComponent.h"
#include "../../NF_Player.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../NF_HealthComponent.h"
#include "../../Enemy/NF_EnemyBase.h"


AGrenade::AGrenade()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	GrenadeCollision = CreateDefaultSubobject<USphereComponent>("GrenadeCollision");
	GrenadeCollision->SetupAttachment(Root);

	GrenadeCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrenade::OnGranadeHit);
	
}

void AGrenade::OnGranadeHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ANF_Player>(OtherActor) && OtherActor != this && bHasHit == false)
	{
		bHasHit = true;	
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, "GranadeHit");
		GranadeExplode();

	}
}

void AGrenade::GranadeExplode()
{
	TArray<AActor*> targets;
	ActorsToIgnore.Add(this);
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplosionRadius, ObjectTypes, ANF_EnemyBase::StaticClass(), ActorsToIgnore, targets);

	if (targets.Num()> 0)
	{
		for(AActor* target : targets)
		{
			UHealthComponent* healthComponent = target->FindComponentByClass<UHealthComponent>();
			if (healthComponent)
			{
				healthComponent->Damage(Damage);
				healthComponent = nullptr;
			}
		}
	}

	Destroy();
}
