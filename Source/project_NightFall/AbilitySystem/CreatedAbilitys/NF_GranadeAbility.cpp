#include "NF_GranadeAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "../AbilityProjectiles/NF_Granade.h"
#include "Components/SphereComponent.h"

void UGranadeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* player = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

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
}
