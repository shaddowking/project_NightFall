#include "NF_GranadeAbility.h"
#include "GameFramework/Character.h"
#include "../../NF_Player.h"
#include "AbilitySystemComponent.h"
#include "../AbilityProjectiles/NF_Granade.h"
#include "Components/SphereComponent.h"

void UGranadeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	handle = Handle;
	actorInfo = ActorInfo;
	activationInfo = ActivationInfo;
	triggerEventData = TriggerEventData;
	bColldownActive = false;

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

	}



	player = Cast<ANF_Player>(ActorInfo->AvatarActor.Get());

	player->CurrentActiveAbility = this;
	player->EquipType = EPlayerEquipTyper::ability;

	/*
	FVector viewOrigin;
	FVector PlayerForward;
	FRotator ViewRotation;

	player->GetController()->GetPlayerViewPoint(viewOrigin, ViewRotation);

	PlayerForward = ViewRotation.Quaternion().GetForwardVector();

	if(player && grenadeTemplate)
	{
		FVector spawnPos = viewOrigin + PlayerForward * 300;
		AGrenade* grenade = GetWorld()->SpawnActor<AGrenade>(grenadeTemplate, spawnPos, ViewRotation);
		grenade->GrenadeCollision->AddImpulse(PlayerForward * 1000, "None",true);
	}
	CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, true);
	EndAbility(Handle, ActorInfo, ActivationInfo,true,false);
	*/
}

void UGranadeAbility::OnPrimaryPress()
{


	FVector viewOrigin;
	FVector PlayerForward;
	FRotator ViewRotation;

	player->GetController()->GetPlayerViewPoint(viewOrigin, ViewRotation);

	PlayerForward = ViewRotation.Quaternion().GetForwardVector();

	if (player && grenadeTemplate)
	{
		FVector spawnPos = viewOrigin + PlayerForward * 300;
		AGrenade* grenade = GetWorld()->SpawnActor<AGrenade>(grenadeTemplate, spawnPos, ViewRotation);
		grenade->GrenadeCollision->AddImpulse(PlayerForward * 1000, "None", true);
	}
	NF_AbilityEnd();



}
