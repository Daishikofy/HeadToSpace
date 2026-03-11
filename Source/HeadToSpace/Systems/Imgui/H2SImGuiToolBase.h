// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "H2SImGuiToolBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HEADTOSPACE_API UH2SImGuiToolBase : public UObject
{
	GENERATED_BODY()
public:
	virtual const FString& GetToolName() const PURE_VIRTUAL(,return "";);
	virtual void DrawTool() PURE_VIRTUAL();
	
	bool bIsVisible = false;
protected:
	FString ToolName = "Default Name";
};
