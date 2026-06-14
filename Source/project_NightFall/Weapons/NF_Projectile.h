#pragma once

#include "GameFramework/Actor.h"

#include "NF_Projectile.generated.h"

class USphereComponent;
class ANF_Player;

UCLASS()
class ANFProjectile : public AActor
{
	GENERATED_BODY()

public:
	ANFProjectile();

	void Tick(float DeltaTime) override;

	UPROPERTY()
	ANF_Player* Owningplayer = nullptr;

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Damage = 10;

	float Duration;

	UPROPERTY(EditDefaultsOnly, Category = "Duration")
	float MaxDuration = 5;

	UPROPERTY(BlueprintReadOnly)
	bool IsActive = false;

	UFUNCTION()
	void ProjectileActivate();

	UFUNCTION()
	void ProjectileDeActivate();
	UFUNCTION(BlueprintImplementableEvent)
	void BPActivate();
	UFUNCTION(BlueprintImplementableEvent)
	void BPDeActivate();

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere = nullptr;

};