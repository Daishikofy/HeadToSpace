// Fill out your copyright notice in the Description page of Project Settings.


#include "H2SPlayerControllerImGui.h"

#include <imgui.h>

const FString& UH2SPlayerControllerImGui::GetToolName() const
{
	return TEXT("Player Controller");
}

void UH2SPlayerControllerImGui::DrawTool()
{
	if (bIsVisible)
	{
		ImGui::Begin("Player Controller");
		ImGui::Text("Player Controller");
		ImGui::End();
	}
}
