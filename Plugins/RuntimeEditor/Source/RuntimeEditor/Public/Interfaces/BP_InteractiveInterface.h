// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BP_InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBP_InteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUNTIMEEDITOR_API IBP_InteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//select
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnSelected();

	//deselect
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDeselected();

	//deselected interactive component
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDeselectedInteractiveComponent();
	
};
