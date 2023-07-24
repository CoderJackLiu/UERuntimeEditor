// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/RE_ControllerManager.h"

URE_ControllerManager* URE_ControllerManager::Instance = nullptr;

//get controller index by settings
int32 URE_ControllerManager::GetControllerIndex()
{
	if (Settings == nullptr)
	{
		Settings = GetMutableDefault<URuntimeEditorSettings>();
	}
	return Settings ? Settings->GetControllerIndex() : 0;
}
