#include "NF_MineAbility.h"
#include "../../NF_Player.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"


#include "../AbilityProjectiles/NF_Mine.h"

void UMineAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	handle = Handle;
	actorInfo = ActorInfo;
	activationInfo = ActivationInfo;
	triggerEventData = TriggerEventData;
	bColldownActive = false;
	bIsAbilityActive = true;

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

	}



	player = Cast<ANF_Player>(ActorInfo->AvatarActor.Get());

	player->CurrentActiveAbility = this;
	player->EquipType = EPlayerEquipTyper::ability;
	if (!MineTargeting)
	{
		MineTargeting = GetWorld()->SpawnActor(MineTargetingTemplate);
	}
	MineTargeting->SetActorHiddenInGame(false);
	MineTick();
}

void UMineAbility::OnPrimaryPress()
{
	AMine* createdMine = GetWorld()->SpawnActor<AMine>(mineTemplate, TargetLocation, NormalDirection);
	MineTargeting->SetActorHiddenInGame(true);

	bIsAbilityActive = false;
	NF_AbilityEnd();
}

void UMineAbility::MineTick()
{

	playerDirection = MineTargeting->GetActorLocation() - player->GetActorLocation();
	TargetLocation = player->GetPlacablePoint(5000, TargetNormal);
	CurrentTargetRotation = MineTargeting->GetActorRotation();


	NormalDirection = UKismetMathLibrary::MakeRotFromZ(TargetNormal);


	MineTargeting->SetActorRotation(NormalDirection);
	MineTargeting->SetActorLocation(TargetLocation);



	if (bIsAbilityActive)
	{
		player->GetWorldTimerManager().SetTimer(MineTimer, this, &UMineAbility::MineTick, 0.1, false);

	}
}
