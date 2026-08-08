#pragma once
#include "GameFramework/Actor.h"
#include "NF_Mine.generated.h"

class USphereComponent;


UCLASS()
class AMine : public AActor
{
GENERATED_BODY()

public:

	AMine();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;


	UPROPERTY(EditAnywhere)
	USphereComponent* MineCollision = nullptr;



	UFUNCTION()
	void OnMineHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 1000;
	UPROPERTY(EditAnywhere)
	float Damage = 20;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OutActors;
};