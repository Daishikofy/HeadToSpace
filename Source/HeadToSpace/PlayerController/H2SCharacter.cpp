// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/H2SCharacter.h"

#include "EnhancedInputComponent.h"
#include "H2SHandController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
DEFINE_LOG_CATEGORY(H2SCharacter);
// Sets default values
AH2SCharacter::AH2SCharacter()
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
}

// Called when the game starts or when spawned
void AH2SCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	
	DoMoveHandTrigger(LeftHandController, MovementVector.X, MovementVector.Y);
}

void AH2SCharacter::LeftHandHold(const FInputActionValue& Value)
{
	bool bIsHolding = Value.Get<bool>();
	UE_LOG(H2SCharacter, Log, TEXT("Left Hand hold"));
	
	DoHandHold(LeftHandController, bIsHolding);
}

void AH2SCharacter::MoveRightHand(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMoveHandTrigger(RightHandController, MovementVector.X, MovementVector.Y);
}

void AH2SCharacter::RightHandHold(const FInputActionValue& Value)
{
	bool bIsHolding = Value.Get<bool>();
	UE_LOG(H2SCharacter, Log, TEXT("Right Hand hold"));
	
	DoHandHold(RightHandController, bIsHolding);
}

// Called every frame
void AH2SCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		EnhancedInputComponent->BindAction(MoveRightHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::MoveRightHand);
		
		EnhancedInputComponent->BindAction(HoldLeftHandAction, ETriggerEvent::Started, this, &AH2SCharacter::LeftHandHold);
		EnhancedInputComponent->BindAction(HoldLeftHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::LeftHandHold);
		EnhancedInputComponent->BindAction(HoldRightHandAction, ETriggerEvent::Started, this, &AH2SCharacter::RightHandHold);
		EnhancedInputComponent->BindAction(HoldRightHandAction, ETriggerEvent::Triggered, this, &AH2SCharacter::RightHandHold);
	}
}

void AH2SCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		//disable movement inputs if we're climbing
		if (!bIsClimbing)
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

void AH2SCharacter::DoMoveHandTrigger(UH2SHandController* Hand, float HorizontalAxis, float VerticalAxis)
{
	if (Hand)
	{
		Hand->MoveTrigger(FVector{0, HorizontalAxis, VerticalAxis});
	}
}

void AH2SCharacter::DoHandHold(UH2SHandController* Hand, bool bIsHandActivated)
{
	if (bIsHandActivated)
	{
		UE_LOG(H2SCharacter, Log, TEXT("Hand hold"));
	}
	else
	{
		UE_LOG(H2SCharacter, Log, TEXT("Hand release"));
	}
	
	if (Hand)
	{
		if (Hand->TryHandHold(bIsHandActivated))
		{
			DrawDebugSphere(GetWorld(), Hand->HandTrigger->GetComponentLocation(), 20, 30, FColor::Yellow, false, 10);
		}
	}
}