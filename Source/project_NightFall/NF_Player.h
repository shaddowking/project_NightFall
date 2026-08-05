#pragma once
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Abilities/GameplayAbility.h"
#include "NF_Player.generated.h"


class UInputMappingContext;
class UInputAction;
class UWeaponComponent;
class AWeaponBase;
class UHealthComponent;
class AGravityProjector;
class UNF_AbilitySystemComp;
class UGameplayAbility;
class UAbilityDataAsset;
class A_NF_HUD;
class UNF_AbilityBase;

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel")

};


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	UNF_AbilitySystemComp* AbilityComp = nullptr;

	EPlayerEquipTyper EquipType;

	UPROPERTY(EditAnywhere)
	UAbilityDataAsset* PrimaryAbilityDAT = nullptr;

	UPROPERTY(EditAnywhere)
	UAbilityDataAsset* SecondaryAbilityDAT = nullptr;


	UFUNCTION(BlueprintCallable)
	void GiveAbilityToPlayer(bool bIsPrimaryAbility,UAbilityDataAsset* abilityDAT);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateAbilityUI(bool bIsPrimaryAbility, UAbilityDataAsset* abilityDAT);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupAbilityUI();

	UPROPERTY(BlueprintReadOnly)
	A_NF_HUD* HudClass = nullptr;

	UPROPERTY()
	FGameplayAbilitySpecHandle CurrentSpecHandle;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAbilitySpecHandle primarySpecHandle;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAbilitySpecHandle secondarySpecHandle;

	UPROPERTY()
	UNF_AbilityBase* CurrentActiveAbility = nullptr;


	UFUNCTION()
	void StartResetShoot(float time);

	UFUNCTION()
	void ResetPlayerCanShoot();

	FVector GetPlacablePoint(float Range, FVector& Normal);
	FVector GetAimPoint(float Range);
	FHitResult AimHit;

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

	FTimerHandle shootTimerHandle;

	//Ability

	TSubclassOf<UGameplayAbility> primaryAbility;

	TSubclassOf<UGameplayAbility> secondaryAbility;

	//----------
	//Weapon

	FVector ViewOrigin;
	FRotator ViewRotation;
	FVector ViewForward;

	UFUNCTION()
	void EquipWeapon(AWeaponBase* weapon);
};