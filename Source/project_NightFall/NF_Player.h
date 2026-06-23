#pragma once
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NF_Player.generated.h"


class UInputMappingContext;
class UInputAction;
class UWeaponComponent;
class AWeaponBase;
class UHealthComponent;

UCLASS()
class ANF_Player : public ACharacter
{
GENERATED_BODY()

public:

	ANF_Player();

	bool bCanShoot = true;
	UFUNCTION(BlueprintImplementableEvent)
	void AttachWeaponToPlayer(AWeaponBase* currentweapon);

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateDebugLine(FVector start, FVector end);

	UPROPERTY(BlueprintReadWrite)
	UHealthComponent* HPComp = nullptr;

protected:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeaponBase> StartWeapon;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RelodeAction;


	void BeginPlay()override;

	

	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

	void HandleMovemnt(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);
	void HandleWeaponFire();
	void HandleWeaponRealse();
	void HandleRelode();


	//Weapon

	UPROPERTY()
	UWeaponComponent* currentWeapon = nullptr;

	//

	void OnDamage();

	void OnDeath();

private:




	//Weapon

	FVector ViewOrigin;
	FRotator ViewRotation;
	FVector ViewForward;

	UFUNCTION()
	void EquipWeapon(AWeaponBase* weapon);
};