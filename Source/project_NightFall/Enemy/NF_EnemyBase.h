#pragma once

#include "GameFramework/Character.h"
#include "NF_EnemyBase.generated.h"

class UHealthComponent;


UCLASS()
class ANF_EnemyBase : public ACharacter
{

	GENERATED_BODY()

public:

	ANF_EnemyBase();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UHealthComponent* HPComp = nullptr;

	UFUNCTION()
	void OnDamage();
	
	UFUNCTION()	
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void DebugDeath();
};