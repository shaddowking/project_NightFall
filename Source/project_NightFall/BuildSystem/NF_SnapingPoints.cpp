#include "NF_SnapingPoints.h"
#include "Components/SphereComponent.h"

ASnapingPoint::ASnapingPoint()
{
	SnapingPointRange = CreateDefaultSubobject<USphereComponent>("blastRange");
	SnapingPointRange->SetupAttachment(GetRootComponent());
}
