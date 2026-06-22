#pragma once

#include "../NF_WeaponBase.h"

#include "NF_FullAuto.generated.h"

UCLASS()
class AFullAuto : public AWeaponBase
{
GENERATED_BODY()

public:

	void GunFire() override;

private:
	

};