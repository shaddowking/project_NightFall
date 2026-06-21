#include "NF_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/NF_WeaponComponent.h"
#include "Weapons/NF_WeaponBase.h"

ANF_Player::ANF_Player()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANF_Player::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
			Subsystem = nullptr;
		}
		PlayerController = nullptr;

	}
	
	if (StartWeapon)
	{
		EquipWeapon(GetWorld()->SpawnActor<AWeaponBase>(StartWeapon));
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
	if (currentWeapon)
	{
		
		GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

		ViewForward = ViewRotation.Quaternion().GetForwardVector();
		currentWeapon->UseWeapon(ViewOrigin, ViewForward);
	}
}

void ANF_Player::HandleWeaponRealse()
{
	if (currentWeapon)
	{
		currentWeapon->RealeseWeapon();
	}
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


