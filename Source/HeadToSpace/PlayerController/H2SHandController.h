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
	float ArmReachRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HandSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HandDetectionRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalToShoulderMinAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalToShoulderMaxAngle;
};

UCLASS(ClassGroup=(HandController), meta=(BlueprintSpawnableComponent), DefaultToInstanced)
class HEADTOSPACE_API UH2SHandController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UH2SHandController();

	UFUNCTION(BlueprintCallable, Category="Hand")
	void SetupComponent(FH2SHandControllerData InHandControllerData);
	
//Hand Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FH2SHandControllerData HandControllerData;
	
	void MoveTrigger(const FVector& Direction);
	bool TryHandHold(bool bIsHandActivated);
	
	AActor* GetHandHoldActor();

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
