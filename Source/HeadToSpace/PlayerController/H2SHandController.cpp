// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/H2SHandController.h"

#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UH2SHandController::UH2SHandController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UH2SHandController::SetupComponent(UStaticMeshComponent* Trigger, UStaticMeshComponent* Mesh)
{
	HandTrigger = Trigger;
	HandMesh = Mesh;

	HandTrigger->OnComponentBeginOverlap.AddDynamic(this, &UH2SHandController::OnTriggerBeginOverlap);
	HandTrigger->OnComponentEndOverlap.AddDynamic(this, &UH2SHandController::OnTriggerEndOverlap);
}

void UH2SHandController::MoveTrigger(const FVector& Direction)
{
	if (HandTrigger == nullptr ||
		CurrentSelectedHold != nullptr)
	{
		return;
	}
	
	UE::Math::TVector<double> FutureLocation = HandTrigger->GetRelativeLocation() + Direction;
	if (FVector::Distance(MovementCenter, FutureLocation) <= MaxRadius)
	{
		HandTrigger->AddLocalOffset(Direction);
	}
}

bool UH2SHandController::TryHandHold(bool bIsHandActivated)
{
	if (bIsHandActivated)
	{
		if (CurrentHoveredHold)
		{
			CurrentSelectedHold = CurrentHoveredHold;
			return true;
		}
	}
	else
	{
		CurrentSelectedHold = nullptr;
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
