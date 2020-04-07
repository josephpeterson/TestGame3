// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TestGame3GameMode.h"
#include "TestGame3Pawn.h"

ATestGame3GameMode::ATestGame3GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ATestGame3Pawn::StaticClass();
}

