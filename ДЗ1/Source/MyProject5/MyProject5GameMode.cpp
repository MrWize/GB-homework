// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject5GameMode.h"
#include "MyProject5Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject5GameMode::AMyProject5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
