// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H2SCharacter.generated.h"

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
	AH2SCharacter();
protected:
	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* ChangeContextAction;
	
	/**Movement**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float ArmReachRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float HandSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float HandDetectionRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float BodySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float LeftBodyOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float RightBodyOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float HorizontalToShoulderMinAngle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float HorizontalToShoulderMaxAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MinWallDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MaxWallDistance;
	
	/**Physics**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement Physics")
	float MaxFallSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement Physics")
	float GravityAppliedToPlayer;
	
	/**Character state**/
	bool bIsClimbing = false;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Called for input */
	void Move(const FInputActionValue& Value);
	void MoveLeftHand(const FInputActionValue& Value);
	void LeftHandHold(const FInputActionValue& Value);
	void MoveRightHand(const FInputActionValue& Value);
	void RightHandHold(const FInputActionValue& Value);
	void ChangeContext(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DoMove(float Right, float Forward);
	void DoLook(float Yaw, float Pitch);
	void DoMoveHandTrigger(UH2SHandController* Hand, float HorizontalAxis, float VerticalAxis);
	void DoHandHold(UH2SHandController* Hand, bool bIsHandActivated);

	friend UH2SPlayerControllerImGui;
};
