#include "NF_SnapingPoints.h"
#include "Components/SphereComponent.h"

ASnapingPoint::ASnapingPoint()
{

	Root = CreateDefaultSubobject<USceneComponent>("root");
	RootComponent = Root;

	SnapingPoint = CreateDefaultSubobject<USceneComponent>("snapingpoint");
	SnapingPoint->SetupAttachment(Root);

	SnapingPointRange = CreateDefaultSubobject<USphereComponent>("snaprange");
	SnapingPointRange->SetupAttachment(Root);
}
