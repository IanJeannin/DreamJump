// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DreamJumpGameMode.h"
#include "DreamJumpCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADreamJumpGameMode::ADreamJumpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
