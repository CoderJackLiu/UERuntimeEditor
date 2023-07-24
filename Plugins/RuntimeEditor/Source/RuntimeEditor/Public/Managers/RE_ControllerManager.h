// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RuntimeEditorSettings.h"

#include "RE_ControllerManager.generated.h"

/**
 * 
 */
UCLASS()
class RUNTIMEEDITOR_API URE_ControllerManager : public UObject
{
	GENERATED_BODY()

public:
	//singleton

	//controller index
	UPROPERTY()
	int32 ControllerIndex = 0;

	//get singleton
	static URE_ControllerManager* Get()
	{
		if (Instance == nullptr)
		{
			Instance = NewObject<URE_ControllerManager>();
			Instance->AddToRoot();
		}
		return Instance;
	}

	//destroy singleton
	static void DestroyInstance()
	{
		if (Instance != nullptr)
		{
			Instance->RemoveFromRoot();
			Instance = nullptr;
		}
	}

	int32 GetControllerIndex();

	//get settings
	class URuntimeEditorSettings* GetSettings()
	{
		if (Settings == nullptr)
		{
			Settings = GetMutableDefault<URuntimeEditorSettings>();
		}
		return Settings;
	}
	
private:
	static URE_ControllerManager* Instance;

	UPROPERTY()
	class URuntimeEditorSettings* Settings;
};
