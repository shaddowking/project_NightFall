#include "NF_Buildable.h"
#include "../NF_GameInstance.h"
#include "NF_GridManager.h"

void ABuildable::BuildingPlaced(int X, int Y, int nodeID, FVector nodepos, FNode startNode)
{
	UNF_GameInstance* GI = Cast<UNF_GameInstance>(GetWorld()->GetFirstPlayerController()->GetGameInstance());
	GI->BuildGridManager->SetNodesOcupide(X, Y, nodeID, nodepos,startNode);

}
