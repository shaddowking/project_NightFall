#pragma once
#include "Engine/GameInstance.h"
#include "NF_GameInstance.generated.h"


class ANF_GridManager;

UCLASS()
class UNF_GameInstance : public UGameInstance
{
GENERATED_BODY()

public:

	UPROPERTY();
	ANF_GridManager* BuildGridManager = nullptr;

};