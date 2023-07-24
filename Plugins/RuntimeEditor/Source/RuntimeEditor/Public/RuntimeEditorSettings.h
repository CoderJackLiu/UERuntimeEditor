// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RuntimeEditorSettings.generated.h"

/**
 * 
 */
UCLASS(Config= Game, BlueprintType, defaultconfig, meta=(DisplayName="Runtime Editor Settings"))
class RUNTIMEEDITOR_API URuntimeEditorSettings : public UObject
{
	GENERATED_BODY()

public:
	//get controller index
	int32 GetControllerIndex();

	//get world name
	FString GetWorldName() const
	{
		return ActiveLevel.GetAssetName();
	}

private:
	UPROPERTY(config, EditAnywhere, Category = "Controller", meta = (DisplayName = "Controller Index", AllowPrivateAccess = "true"))
	int32 ControllerIndex = 0;

	//level object
	UPROPERTY(config, EditAnywhere, Category=DefaultMaps, meta=(AllowedClasses="/Script/Engine.World"))
	FSoftObjectPath ActiveLevel;
};
