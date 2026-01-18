// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H2SCharacter.generated.h"

class UH2SHandController;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(H2SCharacter, Log, All);

UCLASS()
class HEADTOSPACE_API AH2SCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = H2SCharacter, meta = (AllowPrivateAccess = "true"))
	UH2SHandController* RightHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = H2SCharacter, meta = (AllowPrivateAccess = "true"))
	UH2SHandController* LeftHandController;

public:
	// Sets default values for this character's properties
	AH2SCharacter();
protected:
	/**Character state**/
	bool bIsClimbing = false;
	
	/**Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveLeftHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* HoldLeftHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveRightHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* HoldRightHandAction;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Called for input */
	void Move(const FInputActionValue& Value);
	void MoveLeftHand(const FInputActionValue& Value);
	void LeftHandHold(const FInputActionValue& Value);
	void MoveRightHand(const FInputActionValue& Value);
	void RightHandHold(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DoMove(float Right, float Forward);
	void DoLook(float Yaw, float Pitch);
	void DoMoveHandTrigger(UH2SHandController* Hand, float HorizontalAxis, float VerticalAxis);
	void DoHandHold(UH2SHandController* Hand, bool bIsHandActivated);

	/** Handles move inputs from either controls or UI interfaces */
// 	UFUNCTION(BlueprintImplementableEvent, Category="Input")
// 	void DoMoveLeftEvent(float HorizontalAxis, float VerticalAxis);
// 	UFUNCTION(BlueprintImplementableEvent, Category="Input")
// 	void DoLeftHandHoldEvent(bool bIsHolding);
// 	UFUNCTION(BlueprintImplementableEvent, Category="Input")
// 	void DoMoveRightEvent(float HorizontalAxis, float VerticalAxis);
// 	UFUNCTION(BlueprintImplementableEvent, Category="Input")
// 	void DoRightHandHoldEvent(bool bIsHolding);
};
