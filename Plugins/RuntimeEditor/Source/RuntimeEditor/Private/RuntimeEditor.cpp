// Copyright Epic Games, Inc. All Rights Reserved.

#include "RuntimeEditor.h"

#include "ISettingsModule.h"
#include "RuntimeEditorSettings.h"

#define LOCTEXT_NAMESPACE "FRuntimeEditorModule"

void FRuntimeEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	const FName ProjectName = "Project";
	if (SettingsModule)
	{
		SettingsModule->RegisterSettings(ProjectName, ProjectName, "RuntimeEditorSettings",
			LOCTEXT("RuntimeEditorSettings", "RuntimeEditorSettings"),
			LOCTEXT("RuntimeEditorSettingssDescription", "Settings for RuntimeEditorSettings"),
			GetMutableDefault<URuntimeEditorSettings>()
		);
	}
}

void FRuntimeEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRuntimeEditorModule, RuntimeEditor)
