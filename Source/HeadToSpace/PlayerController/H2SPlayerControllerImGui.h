// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Imgui/H2SImGuiToolBase.h"
#include "H2SPlayerControllerImGui.generated.h"

/**
 * 
 */
UCLASS()
class HEADTOSPACE_API UH2SPlayerControllerImGui : public UH2SImGuiToolBase
{
	GENERATED_BODY()
public:
	
	virtual const FString& GetToolName() const override;
	virtual void DrawTool() override;
};
