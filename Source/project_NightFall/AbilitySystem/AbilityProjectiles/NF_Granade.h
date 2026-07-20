#pragma once

#include "GameFramework/Actor.h"

#include "NF_Granade.generated.h"

class USphereComponent;

UCLASS()
class AGrenade : public AActor
{
GENERATED_BODY()

public:

	AGrenade();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;


	UPROPERTY(EditAnywhere)
	USphereComponent* GrenadeCollision = nullptr;

	UFUNCTION()
	void OnGranadeHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 1000;
	UPROPERTY(EditAnywhere)
	float Damage = 20;

private:

	bool bHasHit = false;

	void GranadeExplode();

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OutActors;

};