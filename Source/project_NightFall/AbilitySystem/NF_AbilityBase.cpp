#include "NF_AbilityBase.h"
#include "GameFramework/Character.h"
#include "../NF_Player.h"

void UNF_AbilityBase::OnPrimaryPress()
{
}

void UNF_AbilityBase::OnSecondaryPress()
{
}

void UNF_AbilityBase::NF_AbilityEnd()
{
	player->bCanShoot = false;
	player->CurrentActiveAbility = nullptr;
	player->EquipType = EPlayerEquipTyper::Gun;
	bColldownActive = true;
	
	player->StartResetShoot(1);
	CommitAbilityCooldown(handle, actorInfo, activationInfo, true);
	EndAbility(handle, actorInfo, activationInfo, true, false);
}


