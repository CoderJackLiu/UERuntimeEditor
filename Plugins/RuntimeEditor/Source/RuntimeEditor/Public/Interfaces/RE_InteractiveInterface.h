// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RE_InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URE_InteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUNTIMEEDITOR_API IRE_InteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Select
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnSelected();

	//Deselect
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDeselected();

	//Hover
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnHovered();

	//UnHover
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnUnHovered();

	//Click
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnClicked();

	//Double Click
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDoubleClicked();

	//Drag
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDragged();

	//Drop
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnDropped();

	//Begin Drag
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnBeginDrag();

	//End Drag
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnEndDrag();

	//on Move
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnMove(FVector MouseLocation);

	//on begin move
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnBeginMove();

	//on end move
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnEndMove();

	//on end interact
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|Interactive")
	void OnEndInteract();
	
};
