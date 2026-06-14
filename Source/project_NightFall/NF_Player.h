#pragma once
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NF_Player.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class ANF_Player : public ACharacter
{
GENERATED_BODY()

public:


protected:


	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	void BeginPlay()override;


	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

	void HandleMovemnt(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);

	//Weapon

	bool bCanShoot = true;




};