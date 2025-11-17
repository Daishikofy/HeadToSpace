// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "H2SHandController.generated.h"


class USphereComponent;

UCLASS(ClassGroup=(HandController), meta=(BlueprintSpawnableComponent), DefaultToInstanced)
class HEADTOSPACE_API UH2SHandController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UH2SHandController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UStaticMeshComponent* HandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UStaticMeshComponent* HandTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector MovementCenter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MaxRadius = 100.0;
	
	UFUNCTION(BlueprintCallable)
	void MoveTrigger(const FVector& Direction);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetupComponent(UStaticMeshComponent* Trigger);
};
