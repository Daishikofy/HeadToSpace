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

public:
	// Sets default values for this character's properties
	AH2SCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveLeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveRightAction;
	
	/** Called for movement input */
	void MoveLeft(const FInputActionValue& Value);
	
	void MoveRight(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintImplementableEvent, Category="Input")
	void DoMoveLeft(float HorizontalAxis, float VerticalAxis);

	UFUNCTION(BlueprintImplementableEvent, Category="Input")
	void DoMoveRight(float HorizontalAxis, float VerticalAxis);
};
