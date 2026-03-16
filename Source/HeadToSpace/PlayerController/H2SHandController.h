// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "H2SHandController.generated.h"

class USphereComponent;

USTRUCT(BlueprintType)
struct FH2SHandControllerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ShoulderLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmReachRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HandDetectionRadius = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalToShoulderMinAngle = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalToShoulderMaxAngle = 90.f;
};

UCLASS(ClassGroup=(HandController), meta=(BlueprintSpawnableComponent), DefaultToInstanced)
class HEADTOSPACE_API UH2SHandController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UH2SHandController();

	UFUNCTION(BlueprintCallable, Category="H2S.HandController")
	void SetupComponent(UStaticMeshComponent* HandTrigger);
	
//Hand Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FH2SHandControllerData HandControllerData;
	
	void MoveTrigger(const FVector& Direction);
	void ResetTriggerPosition() const;
	void PreserveHoldPosition() const;
	bool TrySetHandHold();
	bool ReleaseHold();
	
	AActor* GetHandHoldActor() const { return CurrentSelectedHold;};

	//Blueprint implementables for visual feedback
	UFUNCTION(BlueprintImplementableEvent, Category="H2S.HandController")
	void OnHandMove(FVector HoldPosition);
	UFUNCTION(BlueprintImplementableEvent, Category="H2S.HandController")
	void OnHandHold();
	UFUNCTION(BlueprintImplementableEvent, Category="H2S.HandController")
	void OnHandRelease();
	
protected:
	UPROPERTY()
	AActor* CurrentSelectedHold;

private:
	FVector DefaultTriggerPosition;
#pragma region //{Hand related functions and Properties}
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
