// Fill out your copyright notice in the Description page of Project Settings.


#include "H2SPlayerControllerImGui.h"

#include <imgui.h>
#include <string>

#include "H2SCharacter.h"
#include "H2SCharacterMovementComponent.h"
#include "H2SPlayerController.h"
#include "Kismet/GameplayStatics.h"

const FString& UH2SPlayerControllerImGui::GetToolName() const
{
	return TEXT("Player Controller");
}

void UH2SPlayerControllerImGui::DrawTool()
{
	if (bIsVisible)
	{
		ImGui::Begin("Player Controller");
		if (Character == nullptr)
		{
			Character = Cast<AH2SCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			ImGui::End();
			return;
		}
		ImGui::Text("Movement Vector");
		ImGui::Text("Right Input (%lf; %lf)", Character->RightHandMoveInput.Y, Character->RightHandMoveInput.Z);
		ImGui::Text("Left Input (%lf; %lf)", Character->LeftHandMoveInput.Y, Character->LeftHandMoveInput.Z);
		ImGui::Checkbox("Holding Left", &Character->bIsPressingLeft_DEBUG);
		ImGui::Checkbox("Holding Right", &Character->bIsPressingRight_DEBUG);
		ImGui::Text("");
		ImGui::Text("Player Controller");
		ImGui::Checkbox("Is Climbing: %", &Character->PlayerController->bIsInClimbingMode);
		ImGui::Text("Movement Component");
		ImGui::Text("Movement Mode: %d", Character->CustomMovementComponent->MovementMode.GetIntValue());
		if (Character->CustomMovementComponent->MovementMode == MOVE_Custom)
		{
			ImGui::Text("Custom Movement Mode: %d", Character->CustomMovementComponent->CustomMovementMode);
		}
		ImGui::End();
	}
}
