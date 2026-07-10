#include "NF_GravityProjector.h"
#include "../NF_Player.h"
#include "NF_ItemBox.h"
#include "NF_CargoGrid.h"
void AGravityProjector::BickupBox(AItemBox* box)
{
}

void AGravityProjector::ProjectorTick()
{
	owningplayer->GetController()->GetPlayerViewPoint(viewOrigin, ViewRotation);

	PlayerForward = ViewRotation.Quaternion().GetForwardVector();

	if (currentBox == nullptr)
	{
		params.ClearIgnoredActors();
		GetWorld()->LineTraceSingleByChannel(AimHit, viewOrigin, viewOrigin + PlayerForward * TetherMaxDistance, ECollisionChannel::ECC_Visibility);

		if (AimHit.GetActor())
		{
			currentBox = Cast<AItemBox>(AimHit.GetActor());
			if (currentBox)
			{
				params.AddIgnoredActor(currentBox);
				params.AddIgnoredActor(owningplayer);
			}
		}
		
	}
	else
	{
	

		// Fix Tether End calculation

		GetWorld()->LineTraceSingleByChannel(AimHit, viewOrigin, viewOrigin + PlayerForward * TetherDistance, ECollisionChannel::ECC_Visibility, params);


		if (AimHit.bBlockingHit)
		{
			TetherEnd = AimHit.Location + FVector{ AimHit.ImpactNormal.X,AimHit.ImpactNormal.Y,AimHit.ImpactNormal.Z + 50};
		}
		else
		{
			TetherEnd = viewOrigin + PlayerForward * TetherDistance;
		}

		//move box tuwards trace end
		if (currentBox)
		{
			currentBox->SetActorLocation(TetherEnd);
		}

		DebugEndpoint(TetherEnd);
	}
	
}

void AGravityProjector::ReleaseBox()
{
	if (currentBox)
	{
		if (currentBox->currentCargoGrid)
		{
			currentBox->currentCargoGrid->PlaceBox();
			currentBox = nullptr;
		}
	}
}

void AGravityProjector::ChangeTetherDistance(float Value)
{
	TetherDistance += Value * DistanceIncreaseMultiplier;
	if (TetherDistance < TetherMinDistance)
	{
		TetherDistance = TetherMinDistance;
	}
	else if (TetherDistance > TetherMaxDistance)
	{
		TetherDistance = TetherMaxDistance;
	}
}

bool AGravityProjector::IsInSight()
{
	return false;
}
