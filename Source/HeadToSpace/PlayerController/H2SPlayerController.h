// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "H2SPlayerController.generated.h"

class UInputMappingContext;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AH2SPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SwapGameplayMappingContext();
	bool IsInClimbingMode() const {return bIsInClimbingMode;};
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ClimbingMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GroundMappingContext;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

private:
	bool bIsInClimbingMode = false;

};
