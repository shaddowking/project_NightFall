#include "NF_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/NF_WeaponComponent.h"
#include "Weapons/NF_WeaponBase.h"
#include "NF_HealthComponent.h"
#include "CargoGrid/NF_GravityProjector.h"
#include "AbilitySystem/NF_AbilitySystemComponent.h"
#include "AbilitySystem/AbilityDataAsset.h"
#include "UI/NF_HUD.h"
#include "UI/NF_PlayerHUD.h"

ANF_Player::ANF_Player()
{

	HPComp = CreateDefaultSubobject<UHealthComponent>("HPComp");

	HPComp->OnDamage.AddDynamic(this, &ANF_Player::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &ANF_Player::OnDeath);

	AbilityComp = CreateDefaultSubobject<UNF_AbilitySystemComp>("AbilityComponent");


	PrimaryActorTick.bCanEverTick = true;
}

void ANF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANF_Player::GiveAbilityToPlayer(bool bIsPrimaryAbility,UAbilityDataAsset* abilityDAT)
{
	if (abilityDAT)
	{

		//UpdateAbilityUI(bIsPrimaryAbility, abilityDAT);

		CurrentSpecHandle = AbilityComp->GiveAbility(FGameplayAbilitySpec(abilityDAT->abilityClass, 1, static_cast<int32>(EGASAbilityInputID::Confirm), this));
		HudClass->PlayerHud->UpdateAbilityUI(bIsPrimaryAbility, abilityDAT,CurrentSpecHandle);

		if (bIsPrimaryAbility)
		{
			if (abilityDAT->abilityClass != primaryAbility)
			{
				primaryAbility = abilityDAT->abilityClass;
			}

			primarySpecHandle = CurrentSpecHandle;
		}
		else
		{
			if (abilityDAT->abilityClass != secondaryAbility)
			{
				secondaryAbility = abilityDAT->abilityClass;
			}

			secondarySpecHandle = CurrentSpecHandle;
		}
	}
}



void ANF_Player::BeginPlay()
{
	Super::BeginPlay();
	HudClass = Cast<A_NF_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
			Subsystem = nullptr;
		}
		PlayerController = nullptr;

	}

	SetupAbilityUI();
	
	if (StartWeapon)
	{
		EquipWeapon(GetWorld()->SpawnActor<AWeaponBase>(StartWeapon));
		EquipType = EPlayerEquipTyper::Gun;
	}

	if (projectorTemplate)
	{
		graveProjector = GetWorld()->SpawnActor<AGravityProjector>(projectorTemplate);
		AttachWeaponToPlayer(graveProjector);
		graveProjector->owningplayer = this;
		graveProjector->SetActorHiddenInGame(true);
	}

	if (AbilityComp)
	{
		if (PrimaryAbilityDAT)
		{
			GiveAbilityToPlayer(true, PrimaryAbilityDAT);
		}
	}
}

void ANF_Player::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleMovemnt);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleLook);


		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleWeaponFire);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ANF_Player::HandleWeaponRealse);

		EnhancedInputComponent->BindAction(RelodeAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleRelode);
		EnhancedInputComponent->BindAction(GravProjectorAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleEquipGravProjector);
		EnhancedInputComponent->BindAction(GravProjectorEditTetherAction, ETriggerEvent::Triggered, this, &ANF_Player::HandleEditGravTether);



		if (AbilityComp && playerInputComponent)
		{
			AbilityComp->BindAbilityActivationToInputComponent(playerInputComponent, FGameplayAbilityInputBinds(
				"Confirm",
				"Cancel",
				"EGASAbilityInputID",
				static_cast<int32>(EGASAbilityInputID::Confirm),
				static_cast<int32>(EGASAbilityInputID::Cancel)));
		}

	}
}

void ANF_Player::HandleMovemnt(const FInputActionValue& value)
{
	const FVector2D InputVector = value.Get<FVector2D>();

	// If no input, do nothing
	if (InputVector.IsZero()) return;

	// Movement directions
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement
	AddMovementInput(Forward, InputVector.Y);
	AddMovementInput(Right, InputVector.X);
}

void ANF_Player::HandleLook(const FInputActionValue& value)
{
	const FVector2d LookVector = value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void ANF_Player::HandleWeaponFire()
{
	
	GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	ViewForward = ViewRotation.Quaternion().GetForwardVector();

	if (currentWeapon && currentWeapon->OwningGun->bCanRelode == true && bCanShoot && EquipType == EPlayerEquipTyper::Gun)
	{
		
		
		currentWeapon->UseWeapon(ViewOrigin, ViewForward);
	}
	else if (EquipType == EPlayerEquipTyper::GravityProjector)
	{
		graveProjector->ProjectorTick();
	}
	else if (CurrentActiveAbility && EquipType == EPlayerEquipTyper::ability)
	{
		CurrentActiveAbility->OnPrimaryPress();
	}
}

void ANF_Player::HandleWeaponRealse()
{
	

	if (currentWeapon && EquipType == EPlayerEquipTyper::Gun)
	{
		currentWeapon->RealeseWeapon();
	}
	else if (EquipType == EPlayerEquipTyper::GravityProjector)
	{
		graveProjector->ReleaseBox();
	}
	else if (CurrentActiveAbility && EquipType == EPlayerEquipTyper::ability)
	{
		CurrentActiveAbility->OnPrimaryPress();
	}
}

void ANF_Player::HandleRelode()
{
	if (currentWeapon)
	{
		currentWeapon->RelodeWeapon();
	}
}

void ANF_Player::HandleEquipGravProjector()
{
	if (EquipType != EPlayerEquipTyper::GravityProjector)
	{
		graveProjector->SetActorHiddenInGame(false);
		EquipType = EPlayerEquipTyper::GravityProjector;
		currentWeapon->DeactivateWeapon();
	}
	else
	{
		graveProjector->SetActorHiddenInGame(true);
		currentWeapon->ActivateWeapon();
		EquipType = EPlayerEquipTyper::Gun;
	}
	
}

void ANF_Player::HandleEditGravTether(const FInputActionValue& value)
{

	const float ChangeValue = value.Get<float>();

	if (EquipType == EPlayerEquipTyper::GravityProjector)
	{
		graveProjector->ChangeTetherDistance(ChangeValue);
	}
}

void ANF_Player::OnDamage()
{
}

void ANF_Player::OnDeath()
{
}

void ANF_Player::EquipWeapon(AWeaponBase* weapon)
{
	if (weapon)
	{
		AttachWeaponToPlayer(weapon);
		currentWeapon = weapon->GunComponent;
		currentWeapon->ActivateWeapon();
		currentWeapon->Owner = this;
		

	}
}



void ANF_Player::StartResetShoot(float time)
{
	GetWorldTimerManager().SetTimer(shootTimerHandle, this, &ANF_Player::ResetPlayerCanShoot, time, false);

}
void ANF_Player::ResetPlayerCanShoot()
{
	bCanShoot = true;
}


