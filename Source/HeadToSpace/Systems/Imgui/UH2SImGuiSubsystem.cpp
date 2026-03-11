#include "UH2SImGuiSubsystem.h"
#include <imgui.h>

#include "ImGuiModule.h"
#include "PlayerController/H2SPlayerControllerImGui.h"

void UH2SImGuiSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TArray<UClass*> ToolClasses;
	GetDerivedClasses(UH2SImGuiToolBase::StaticClass(), ToolClasses);
	for (UClass* ToolClass : ToolClasses)
	{
		if (UH2SImGuiToolBase* ToolInstance = NewObject<UH2SImGuiToolBase>(this, ToolClass))
		{
			Tools.Add(ToolInstance);
		}
	}
}

void UH2SImGuiSubsystem::Deinitialize()
{
	Tools.Empty();
	Super::Deinitialize();
}

TStatId UH2SImGuiSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UH2SImGuiSubsystem, STATGROUP_Tickables);
}

void UH2SImGuiSubsystem::Tick(float DeltaTime)
{
	if(FImGuiModule::Get().GetProperties().IsInputEnabled())
	{
		if(ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Tools"))
			{
				for (UH2SImGuiToolBase* Tool : Tools)
				{
					if (ImGui::MenuItem(TCHAR_TO_ANSI(*Tool->GetToolName())))
					{
						Tool->bIsVisible = !Tool->bIsVisible;
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	for (UH2SImGuiToolBase* Tool : Tools)
	{
		Tool->DrawTool();
	}
}
