#pragma once

#include "GameFramework/Actor.h"
#include "../BuildSystem/NF_Buildable.h"
#include "NF_TurretBase.generated.h"

class UProjectilePoolComp;
class USphereComponent;
class ANF_EnemyBase;
class ANFProjectile;

UCLASS()
class ANF_TurretBase : public ABuildable
{
	GENERATED_BODY()

public:

	ANF_TurretBase();

	UPROPERTY(EditAnywhere)
	UProjectilePoolComp* projectilePoolComp = nullptr;

	UPROPERTY()
	USceneComponent* Root = nullptr;

	UPROPERTY(EditInstanceOnly)
	USceneComponent* FirePoint = nullptr;
	UPROPERTY(EditInstanceOnly)
	USceneComponent* Aimpoint = nullptr;

	UPROPERTY(EditInstanceOnly)
	USceneComponent* YRotPoint = nullptr;

	UPROPERTY(EditInstanceOnly)
	USceneComponent* ZRotPoint= nullptr;

	UPROPERTY(EditAnywhere)
	USphereComponent* TurretRange = nullptr;
	virtual bool CanShoot(ACharacter* target);
	virtual void TurretFire();

	virtual void UpdateTargetList();


	void BeginPlay()override;

	void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly)
	float InterpSpeed = 2;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenFire = 1;

	UPROPERTY(EditDefaultsOnly)
	float turretDamage = 5;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpeed = 500;

	UPROPERTY(EditDefaultsOnly)
	float MaxTurretAmmo = 200;

	float TurretAmmo;

	FTimerHandle turretTimerHandle;

protected:

	UFUNCTION()
	void OnEnemyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEnemyExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	ANF_EnemyBase* currentEnemy = nullptr;

	UPROPERTY()
	TArray<ANF_EnemyBase*> ValidTargets;

	UPROPERTY()
	TArray<AActor*> TargetsInRange;

	UFUNCTION()
	ANF_EnemyBase* FindNextTarget();


	float BestDistance;

	UPROPERTY()
	ANFProjectile* CurentBullet = nullptr;

	float TargetAngle;

	bool IsBetween(float value, float min, float max);

	FVector TurretDirection;
	FRotator TurretRotation;

	FVector YTurretDirection;
	FRotator YTurretRotation;
	UFUNCTION(BlueprintImplementableEvent)
	void DebugTarget(FVector targetLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void Debugdirection(FRotator direction);

	UFUNCTION(BlueprintImplementableEvent)
	void DrawDebugLine(FVector A, FVector B);
private:




};