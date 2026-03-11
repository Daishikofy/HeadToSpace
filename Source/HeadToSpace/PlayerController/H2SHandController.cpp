// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/H2SHandController.h"

#include "H2SCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UH2SHandController::UH2SHandController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UH2SHandController::SetupComponent(UStaticMeshComponent* HandTrigger)
{
	HandControllerData.Trigger = HandTrigger;

	HandControllerData.Trigger->OnComponentBeginOverlap.AddDynamic(this, &UH2SHandController::OnTriggerBeginOverlap);
	HandControllerData.Trigger->OnComponentEndOverlap.AddDynamic(this, &UH2SHandController::OnTriggerEndOverlap);
}

void UH2SHandController::MoveTrigger(const FVector& Direction)
{
	if (HandControllerData.Trigger == nullptr ||
		CurrentSelectedHold != nullptr)
	{
		UE_LOG(H2SCharacter, Log, TEXT("HandController Trigger is null or hand is holding"));
		return;
	}

	UE::Math::TVector<double> FutureLocation = HandControllerData.Trigger->GetRelativeLocation() + Direction;
	if (FVector::Distance(HandControllerData.ShoulderLocation, FutureLocation) <= HandControllerData.ArmReachRadius)
	{
		HandControllerData.Trigger->AddLocalOffset(Direction);
	}
}

void UH2SHandController::PreserveHoldPosition()
{
	if (CurrentSelectedHold != nullptr)
	{
		HandControllerData.Trigger->SetWorldLocation(GetHandHoldActor()->GetActorLocation());
	}
}

bool UH2SHandController::TrySetHandHold()
{
	if (CurrentSelectedHold == nullptr and CurrentHoveredHold != nullptr)
	{
		CurrentSelectedHold = CurrentHoveredHold;
		return true;
	}
	return false;
}

bool UH2SHandController::ReleaseHold()
{
	if (CurrentSelectedHold != nullptr)
	{
		CurrentSelectedHold = nullptr;
		return true;
	}
	return false;
}

void UH2SHandController::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentHoveredHold = OtherActor;
	MoveHand();
}

void UH2SHandController::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (CurrentHoveredHold == OtherActor)
	{
		CurrentHoveredHold = nullptr;
	}
}

void UH2SHandController::MoveHand()
{
	if (CurrentHoveredHold != nullptr)
	{
		OnHandMove(CurrentHoveredHold->GetActorLocation());
	}
}
