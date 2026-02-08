#pragma once
#include "UH2SImGuiSubsystem.generated.h"

UCLASS()
class UH2SImGuiSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual TStatId GetStatId() const override;
	
	virtual void Tick(float DeltaTime) override;
private:
	void DrawImGui();
};
