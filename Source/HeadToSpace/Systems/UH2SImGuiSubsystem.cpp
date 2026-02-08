#include "UH2SImGuiSubsystem.h"
#include <imgui.h>

TStatId UH2SImGuiSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UH2SImGuiSubsystem, STATGROUP_Tickables);
}

void UH2SImGuiSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawImGui();
}

void UH2SImGuiSubsystem::DrawImGui()
{
	ImGui::Begin("H2S");
	ImGui::Text("Testing window");
	ImGui::End();
}
