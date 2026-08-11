#include "NF_Mine.h"
#include "Components/SphereComponent.h"
#include "../../NF_Player.h"

#include "../../Enemy/NF_EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../NF_HealthComponent.h"

AMine::AMine()
{

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	MineCollision = CreateDefaultSubobject<USphereComponent>("GrenadeCollision");
	MineCollision->SetupAttachment(Root);

	MineCollision->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnMineHit);
}

void AMine::OnMineHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ANF_Player>(OtherActor) && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		
		TArray<AActor*> targets;
		ActorsToIgnore.Add(this);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplosionRadius, ObjectTypes, ANF_EnemyBase::StaticClass(), ActorsToIgnore, targets);

		if (targets.Num() > 0)
		{
			for (AActor* target : targets)
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
}
