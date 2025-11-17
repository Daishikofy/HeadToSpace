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


void UH2SHandController::MoveTrigger(const FVector& Direction)
{
	if (HandTrigger == nullptr)
	{
		return;
	}
	
	UE::Math::TVector<double> FutureLocation = HandTrigger->GetRelativeLocation() + Direction;
	if (FVector::Distance(MovementCenter, FutureLocation) <= MaxRadius)
	{
		HandTrigger->AddLocalOffset(Direction);
	}
}

// Called when the game starts
void UH2SHandController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UH2SHandController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UH2SHandController::SetupComponent(UStaticMeshComponent* Trigger)
{
	this->HandTrigger = Trigger;
}

