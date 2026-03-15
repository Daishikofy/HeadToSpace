// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/H2SCharacter.h"

#include "EnhancedInputComponent.h"
#include "H2SCharacterMovementComponent.h"
#include "H2SHandController.h"
#include "H2SPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Elements/Framework/TypedElementSorter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
DEFINE_LOG_CATEGORY(H2SCharacter);
// Sets default values
AH2SCharacter::AH2SCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UH2SCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Create the hands
	
	RightHandController = CreateDefaultSubobject<UH2SHandController>(TEXT("RightHandController"));
	LeftHandController = CreateDefaultSubobject<UH2SHandController>(TEXT("LeftHandController"));

	CustomMovementComponent = Cast<UH2SCharacterMovementComponent>(GetCharacterMovement());
}

// Called to bind functionality to input
void AH2SCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AH2SCharacter::Move);
		EnhancedInputComponent->BindAction(MoveLeftHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::MoveLeftHand);
		EnhancedInputComponent->BindAction(MoveLeftHandAction, ETriggerEvent::Completed, this, &AH2SCharacter::MoveLeftHand);
		EnhancedInputComponent->BindAction(MoveRightHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::MoveRightHand);
		EnhancedInputComponent->BindAction(MoveRightHandAction, ETriggerEvent::Completed, this, &AH2SCharacter::MoveRightHand);
		
		EnhancedInputComponent->BindAction(HoldLeftHandAction, ETriggerEvent::Ongoing, this, &AH2SCharacter::LeftHandHold);
		EnhancedInputComponent->BindAction(HoldLeftHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::LeftHandHold);
		EnhancedInputComponent->BindAction(HoldRightHandAction, ETriggerEvent::Ongoing, this, &AH2SCharacter::RightHandHold);
		EnhancedInputComponent->BindAction(HoldRightHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::RightHandHold);

		EnhancedInputComponent->BindAction(ChangeContextAction, ETriggerEvent::Triggered, this, &AH2SCharacter::ChangeContext);
	}
}

// Called every frame
void AH2SCharacter::Tick(float DeltaTime)
{
	//If Hand input is not null, move hands
	if (RightHandMoveInput != FVector::Zero())
	{
		DoMoveHandTrigger(RightHandController, RightHandMoveInput, DeltaTime);
	}
	if (LeftHandMoveInput != FVector::Zero())
	{
		DoMoveHandTrigger(LeftHandController, LeftHandMoveInput, DeltaTime);
	}

	//If body position must be updated, update body position
	if (GravityCenterTarget != FVector::ZeroVector)
	{
		// add movement
		FVector GravityCenterDirection = GravityCenterTarget - GetActorLocation();
		GravityCenterDirection.X = 0.0f;
		if (GravityCenterDirection.Length() < 5.f)
		{
			GravityCenterTarget = FVector::ZeroVector;
		}
		else
		{
			GravityCenterDirection.Normalize();
		
			AddMovementInput(GravityCenterDirection, 1.0f);
			UE_LOG(H2SCharacter, Log, TEXT("DoHandHold : Move Body"));
		}

	}

	if (CustomMovementComponent->Velocity.Length() > 0.0f)
	{
		LeftHandController->PreserveHoldPosition();
		RightHandController->PreserveHoldPosition();
	}
	
	Super::Tick(DeltaTime);
}

void AH2SCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AH2SCharacter::MoveLeftHand(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	LeftHandMoveInput.Y = MovementVector.X;
	LeftHandMoveInput.Z = MovementVector.Y;
}

void AH2SCharacter::LeftHandHold(const FInputActionValue& Value)
{
	bool bIsHolding = Value.Get<bool>();
	bIsPressingLeft_DEBUG = bIsHolding;
	
	DoHandHold(LeftHandController, bIsHolding);
}

void AH2SCharacter::MoveRightHand(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	RightHandMoveInput.Y = MovementVector.X;
	RightHandMoveInput.Z = MovementVector.Y;
}

void AH2SCharacter::RightHandHold(const FInputActionValue& Value)
{
	bool bIsHolding = Value.Get<bool>();
	bIsPressingRight_DEBUG = bIsHolding;
	
	DoHandHold(RightHandController, bIsHolding);
}

void AH2SCharacter::ChangeContext(const FInputActionValue& Value)
{
	AH2SPlayerController* PlayerController = Cast<AH2SPlayerController>(GetController());
	PlayerController->SwapGameplayMappingContext();
	if (PlayerController->IsInClimbingMode())
	{
		CustomMovementComponent->SetMovementMode(MOVE_Walking);
		LeftHandController->ReleaseHold();
		RightHandController->ReleaseHold();
	}
	else
	{
		CustomMovementComponent->SetMovementMode(MOVE_Custom, EH2SMovementMode::H2S_MOVE_Climb);
	}
}

void AH2SCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AH2SCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AH2SCharacter::DoMoveHandTrigger(UH2SHandController* Hand, const FVector& Direction, float DeltaTime)
{
	if (Hand)
	{
		Hand->MoveTrigger(HandSpeed * DeltaTime * Direction);
	}
}

void AH2SCharacter::DoHandHold(UH2SHandController* Hand, bool bIsTryingToHold)
{
	if (Hand)
	{
		UE_LOG(H2SCharacter, Log, TEXT("AH2SCharacter::DoHandHold bIsHandHolding: %d"), bIsTryingToHold);
		if (bIsTryingToHold)
		{
			if (Hand->TrySetHandHold())
			{
				UE_LOG(H2SCharacter, Log, TEXT("Hand STARTS holding"));
				GravityCenterTarget = ComputeGravityCenterPosition();
				GravityCenterMoveDirection = GravityCenterTarget - CustomMovementComponent->GetLocation();
			}
		}
		else if (Hand->ReleaseHold())
		{
			UE_LOG(H2SCharacter, Log, TEXT("Hand STOPS holding"));
			//Release this hand, computation should be done each time a release / hold is done
			if (RightHandController->GetHandHoldActor() == nullptr && LeftHandController->GetHandHoldActor() == nullptr)
			{
				//Falling
				GravityCenterTarget = FVector::ZeroVector;
				CustomMovementComponent->SetMovementMode(MOVE_Falling);
				
				AH2SPlayerController* PlayerController = Cast<AH2SPlayerController>(GetController());
				PlayerController->SwapGameplayMappingContext();
			}
			else
			{
				GravityCenterTarget = ComputeGravityCenterPosition();
				GravityCenterMoveDirection = GravityCenterTarget - CustomMovementComponent->GetLocation();
			}
		}
	}
}

FVector AH2SCharacter::ComputeGravityCenterPosition() const
{
	AActor* RightHand = RightHandController->GetHandHoldActor();
	AActor* LeftHand = LeftHandController->GetHandHoldActor();
	FVector NewCenter;
	if (RightHand != nullptr && LeftHand != nullptr)
	{
		NewCenter = (RightHand->GetActorLocation() + LeftHand->GetActorLocation()) / 2.0f;
	}
	else if (RightHand != nullptr)
	{
		const FVector MirrorY = FVector(1, -1, 1);
		NewCenter = RightHand->GetActorLocation() + (NeutralBodyOffset * MirrorY);
	}
	else
	{
		NewCenter = LeftHand->GetActorLocation() + NeutralBodyOffset;
	}
	
	// _ _DEBUG End _ _
	DrawDebugSphere(GetWorld(), NewCenter, 10, 30, FColor::Yellow, false, 10);
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(),NewCenter, 20, FColor::Blue, false, 10);
	//_ _ DEBUG Begin _ _
		
	return NewCenter;
}