#pragma once
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NF_Player.generated.h"


class UInputMappingContext;
class UInputAction;
class UWeaponComponent;
class AWeaponBase;
class UHealthComponent;
class AGravityProjector;

UENUM(BlueprintType)
enum class EPlayerEquipTyper : uint8
{
	Gun,
	GravityProjector,
	ability,
	build
};


UCLASS()
class ANF_Player : public ACharacter
{
GENERATED_BODY()

public:

	ANF_Player();

	bool bCanShoot = true;
	UFUNCTION(BlueprintImplementableEvent)
	void AttachWeaponToPlayer(AActor* currentweapon);

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateDebugLine(FVector start, FVector end);

	UPROPERTY(BlueprintReadWrite)
	UHealthComponent* HPComp = nullptr;

	EPlayerEquipTyper EquipType;

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
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* GravProjectorAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* GravProjectorEditTetherAction;


	void BeginPlay()override;

	

	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

	void HandleMovemnt(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);
	void HandleWeaponFire();
	void HandleWeaponRealse();
	void HandleRelode();
	void HandleEquipGravProjector();
	void HandleEditGravTether(const FInputActionValue& value);



	//Weapon

	UPROPERTY()
	UWeaponComponent* currentWeapon = nullptr;

	//
	//GravityProjector

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGravityProjector> projectorTemplate;
	UPROPERTY();
	AGravityProjector* graveProjector = nullptr;

	//

	UFUNCTION()
	void OnDamage();

	UFUNCTION()
	void OnDeath();

private:




	//Weapon

	FVector ViewOrigin;
	FRotator ViewRotation;
	FVector ViewForward;

	UFUNCTION()
	void EquipWeapon(AWeaponBase* weapon);
};