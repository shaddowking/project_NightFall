#pragma once
#include "Components/ActorComponent.h"

#include "NF_ProjectilePoolComp.generated.h"

class ANFProjectile;

UCLASS()
class UProjectilePoolComp : public UActorComponent
{
	GENERATED_BODY()

public:

	void BeginPlay() override;


	UFUNCTION()
	void GenerateProjectilePool();

	ANFProjectile* GetAvalableProjectile();


	UPROPERTY(EditAnywhere)
	float PoolSize = 30;

	UPROPERTY(EditAnywhere) 
	TSubclassOf<ANFProjectile> ProjectileClass;

	UPROPERTY()
	TArray<ANFProjectile*> ProjectilePool;

	UPROPERTY()
	ANFProjectile* AvalableProjectile = nullptr;
	
};