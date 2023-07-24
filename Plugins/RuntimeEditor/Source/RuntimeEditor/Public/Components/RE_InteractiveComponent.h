// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/RE_InteractiveInterface.h"
#include "RE_InteractiveComponent.generated.h"


//Enum contains "left top","right top","left bottom","right bottom"
UENUM(BlueprintType)
enum class ERE_DirectionType : uint8
{
	//left top
	LeftTop,
	//right top
	RightTop,
	//left bottom
	LeftBottom,
	//right bottom
	RightBottom,
};


//delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRE_InteractiveComponentDelegate, FVector, NewLocation, URE_InteractiveComponent*, InteractiveComponent);

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RUNTIMEEDITOR_API URE_InteractiveComponent : public UStaticMeshComponent, public IRE_InteractiveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URE_InteractiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnBeginMove_Implementation() override;
	virtual void OnEndMove_Implementation() override;
	//selected
	virtual void OnSelected_Implementation() override;
	//deselected
	virtual void OnDeselected_Implementation() override;

	//move component func
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_InteractiveComponent")
	void MoveComponent();

	//can move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_InteractiveComponent")
	bool bCanMove;

	//on move
	UPROPERTY(BlueprintAssignable, Category = "RuntimeEditor|RE_InteractiveComponent")
	FRE_InteractiveComponentDelegate OnMoveEvent;

	//default scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_InteractiveComponent")
	FVector DefaultScale;


	//reset to default scale
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_InteractiveComponent")
	void ResetToDefaultScale();

	//get Interactive direction type
	EMouseCursor::Type GetInteractiveDirectionType() const;

	// Interactive direction type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_InteractiveComponent")
	ERE_DirectionType InteractiveDirectionType;

private:
	UPROPERTY()
	APlayerController* PlayerController;

	APlayerController* GetPlayerController();
};
