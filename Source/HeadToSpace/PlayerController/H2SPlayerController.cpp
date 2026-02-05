// Copyright Epic Games, Inc. All Rights Reserved.


#include "H2SPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void AH2SPlayerController::SwapGameplayMappingContext() 
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bIsClimbing)
		{
			Subsystem->AddMappingContext(GroundMappingContext, 0);
			Subsystem->RemoveMappingContext(ClimbingMappingContext);
		}
		else
		{
			Subsystem->AddMappingContext(ClimbingMappingContext , 0);
			Subsystem->RemoveMappingContext(GroundMappingContext);
		}
		bIsClimbing = !bIsClimbing;
	}
}

void AH2SPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}

		Subsystem->AddMappingContext(GroundMappingContext, 0);
	}
}
