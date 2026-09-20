#pragma once
#include "NF_TurretBase.h"
#include "NF_LightTurret.generated.h"


UCLASS()
class ALightTurret : public ANF_TurretBase
{

	GENERATED_BODY()


public:

	void TurretFire() override;

	bool CanShoot(ACharacter* target) override;

	
	float bestdistance = 0;
	UPROPERTY(EditAnywhere)
	float Radius = 0;
	UPROPERTY(EditAnywhere)
	float angle = 0;
	FCollisionQueryParams params;
	FHitResult FovHit;
	UPROPERTY(BlueprintReadOnly)
	AActor* TargetActor = nullptr;
};