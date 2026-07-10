#pragma once

#include "GameFramework/Actor.h"

#include "NF_GravityProjector.generated.h"

class AItemBox;
class ANF_Player;

UCLASS()
class AGravityProjector : public AActor
{

	GENERATED_BODY()

public:

	UPROPERTY()
	AItemBox* currentBox = nullptr;

	void BickupBox(AItemBox* box);

	void ProjectorTick();

	void ReleaseBox();

	void ChangeTetherDistance(float Value);

	bool IsInSight();

	UPROPERTY();
	ANF_Player* owningplayer = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void DebugEndpoint(FVector endpoint);

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float TetherDistance = 500;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float DistanceIncreaseMultiplier = 2;

	FVector TetherEnd;

	FVector PlayerForward;

	FVector viewOrigin;

	FRotator ViewRotation;

	FHitResult AimHit;

	float TetherMinDistance = 100;

	float TetherMaxDistance = 5000;

	FCollisionQueryParams params;


};