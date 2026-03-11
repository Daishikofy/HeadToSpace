// Fill out your copyright notice in the Description page of Project Settings.


#include "H2SCharacterMovementComponent.h"

#include "GameFramework/Character.h"


// Sets default values for this component's properties
UH2SCharacterMovementComponent::UH2SCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UH2SCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UH2SCharacterMovementComponent::IsCustomMovementMode(EH2SMovementMode InMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InMovementMode;
}

void UH2SCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	if (IsCustomMovementMode(H2S_MOVE_Climb))
	{
		//EnterClimb(PreviousMovementMode, static_cast<EH2SMovementMode>(PreviousCustomMode));
	}

	if (PreviousMovementMode == MOVE_Custom)
	{
		switch (static_cast<EH2SMovementMode>(PreviousCustomMode))
		{
		case H2S_MOVE_Climb:
			StopMovementImmediately();
			break;
		default: ;
		}
	}
	
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UH2SCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	switch (CustomMovementMode)
	{
	case H2S_MOVE_Climb:
		PhysClimb(deltaTime, Iterations);
		break;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"))
	}
	Super::PhysCustom(deltaTime, Iterations);
}

void UH2SCharacterMovementComponent::PhysClimb(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}
	//Compute climbing Velocity
	RestorePreAdditiveRootMotionVelocity();
	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		constexpr float Friction = 0.0f;
		constexpr bool bFluid = false;

		if( Acceleration.IsZero() )
		{
			Velocity = FVector::ZeroVector;
		}
		
		CalcVelocity(deltaTime, Friction, bFluid, BreakingDeceleration);
	}
	
	ApplyRootMotionToVelocity(deltaTime);
	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	
	//Move along climbing surface
	const FVector AdjustedVelocity = Velocity * deltaTime;
	const FQuat CurrentRotation = UpdatedComponent->GetComponentQuat();
	FHitResult Hit(1.f);
	SafeMoveUpdatedComponent(AdjustedVelocity, CurrentRotation, true, Hit);
	if (Hit.Time < 1.f)
	{
		HandleImpact(Hit, deltaTime, AdjustedVelocity);
		SlideAlongSurface(AdjustedVelocity, (1.f - Hit.Time), Hit.Normal, Hit, true);
	}

	//Set velocity
	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
	}
}

float UH2SCharacterMovementComponent::GetMaxSpeed() const
{
	return IsCustomMovementMode(H2S_MOVE_Climb) ? MaxClimbingSpeed : Super::GetMaxSpeed();
}

float UH2SCharacterMovementComponent::GetMaxAcceleration() const
{
	return IsCustomMovementMode(H2S_MOVE_Climb) ? MaxClimbingAcceleration : Super::GetMaxAcceleration();
}

// Called every frame
void UH2SCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

