#pragma once
#include "UH2SImGuiSubsystem.generated.h"

class UH2SImGuiToolBase;

UCLASS()
class UH2SImGuiSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	

	// FTickableGameObject implementation Begin
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual ETickableTickType GetTickableTickType() const override { return IsTemplate() ? ETickableTickType::Never : ETickableTickType::Always; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	// FTickableGameObject implementation End

	UFUNCTION(BlueprintCallable)
	static void ToggleImGuiInput();
private:
	UPROPERTY()
	TArray<UH2SImGuiToolBase*> Tools;
};
