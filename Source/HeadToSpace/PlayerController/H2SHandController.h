// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "H2SHandController.generated.h"

class USphereComponent;
UCLASS(ClassGroup=(HandController), meta=(BlueprintSpawnableComponent), DefaultToInstanced)
class HEADTOSPACE_API UH2SHandController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UH2SHandController();

//Hand Controller 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UStaticMeshComponent* HandMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector MovementCenter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MaxRadius = 100.0;

	UFUNCTION(BlueprintCallable, Category="Hand")
	void SetupComponent(UStaticMeshComponent* Trigger, UStaticMeshComponent* Mesh);
	
	void MoveTrigger(const FVector& Direction);
	bool TryHandHold(bool bIsHandActivated);

	//Blueprint implementables for visual feedback
	UFUNCTION(BlueprintImplementableEvent, Category="HandController")
	void OnHandMove(FVector HoldPosition);
	UFUNCTION(BlueprintImplementableEvent, Category="HandController")
	void OnHandHold();
	UFUNCTION(BlueprintImplementableEvent, Category="HandController")
	void OnHandRelease();
	
protected:
	UPROPERTY()
	AActor* CurrentSelectedHold;

#pragma region //{Hand related functions and Properties}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UStaticMeshComponent* HandTrigger;
	
protected:
	UPROPERTY()
	AActor* CurrentHoveredHold;
	
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void MoveHand();
#pragma endregion

};
