// Copyright Epic Games, Inc. All Rights Reserved.

#include "CloneGuysV2GameMode.h"
#include "CloneGuysV2Character.h"
#include "UObject/ConstructorHelpers.h"

ACloneGuysV2GameMode::ACloneGuysV2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
