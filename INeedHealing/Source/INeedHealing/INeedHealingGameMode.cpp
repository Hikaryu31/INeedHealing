// Copyright Epic Games, Inc. All Rights Reserved.

#include "INeedHealingGameMode.h"
#include "INeedHealingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AINeedHealingGameMode::AINeedHealingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
