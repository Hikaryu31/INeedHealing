// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "INeedHealingGameMode.generated.h"

UCLASS(minimalapi)
class AINeedHealingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AINeedHealingGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		int enemiesCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		int alliesCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		int waveNumber = 0;
};



