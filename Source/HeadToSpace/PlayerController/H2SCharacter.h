// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H2SCharacter.generated.h"

class AH2SPlayerController;
class UH2SCharacterMovementComponent;
class UH2SPlayerControllerImGui;
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
	AH2SCharacter(const FObjectInitializer& ObjectInitializer);
protected:
	
	/**Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* MoveLeftHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* HoldLeftHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* MoveRightHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* HoldRightHandAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Input")
	UInputAction* ChangeContextAction;
	
	/**Movement**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float ArmReachRadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float HandSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float HandDetectionRadius = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float BodySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement", meta=(ToolTip="When body moves to target, at which distance can it starts deccelerating to reach the target."))
	float BodyMovementAcceptanceRadius = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	FVector NeutralBodyOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float HorizontalToShoulderMinAngle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float HorizontalToShoulderMaxAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float MinWallDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement")
	float MaxWallDistance;
	
	/**Physics**/
	/**Commented for now as we might use the movement component one instead**/
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement Physics")
	float MaxFallSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="H2S.Movement Physics")
	float GravityAppliedToPlayer;*/
	
	/** Called for input */
	void Move(const FInputActionValue& Value);
	void MoveLeftHand(const FInputActionValue& Value);
	void LeftHandHold(const FInputActionValue& Value);
	void MoveRightHand(const FInputActionValue& Value);
	void RightHandHold(const FInputActionValue& Value);
	void ChangeContext(const FInputActionValue& Value);
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DoMove(float Right, float Forward);
	void DoLook(float Yaw, float Pitch);
	void DoMoveHandTrigger(UH2SHandController* Hand, const FVector& Direction, float DeltaTime);
	void DoHandHold(UH2SHandController* Hand, bool bIsTryingToHold);

private:
	UPROPERTY()
	UH2SCharacterMovementComponent* CustomMovementComponent;
	UPROPERTY()
	AH2SPlayerController* PlayerController;

	FVector RightHandMoveInput;
	FVector LeftHandMoveInput;

	FVector GravityCenterTarget;
	FVector CurrentGravityCenterDirection;

	void ResetBodyMotion();
	FVector ComputeGravityCenterPosition() const;
	//IMGUI variables
	bool bIsPressingLeft_DEBUG, bIsPressingRight_DEBUG;
	
	friend UH2SPlayerControllerImGui;
};
