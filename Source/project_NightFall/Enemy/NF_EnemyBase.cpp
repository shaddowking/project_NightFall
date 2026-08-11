#include "NF_EnemyBase.h"
#include "../NF_HealthComponent.h"

ANF_EnemyBase::ANF_EnemyBase()
{
	HPComp = CreateDefaultSubobject<UHealthComponent>("HPComp");

	HPComp->OnDamage.AddDynamic(this, &ANF_EnemyBase::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &ANF_EnemyBase::OnDeath);
}

void ANF_EnemyBase::OnDamage()
{
}

void ANF_EnemyBase::OnDeath()
{
	DebugDeath();
}
