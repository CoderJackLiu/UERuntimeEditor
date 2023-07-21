// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/RE_InteractiveInterface.h"
#include "RE_ElementComponent.generated.h"


//FRE_Vector4D
USTRUCT(BlueprintType)
struct FRE_Vector4D
{
	GENERATED_USTRUCT_BODY()
	//左上角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor")
	FVector LeftTop;

	//右上角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor")
	FVector RightTop;

	//左下角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor")
	FVector LeftBottom;

	//右下角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor")
	FVector RightBottom;

	//是否合法
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor")
	bool IsValid;

	//constructor
	FRE_Vector4D()
	{
		IsValid = false;
	}

	//constructor
	FRE_Vector4D(const FVector& InLeftTop, const FVector& InRightTop, const FVector& InLeftBottom, const FVector& InRightBottom)
	{
		LeftTop     = InLeftTop;
		RightTop    = InRightTop;
		LeftBottom  = InLeftBottom;
		RightBottom = InRightBottom;
		IsValid     = true;
	}
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RUNTIMEEDITOR_API URE_ElementComponent : public UStaticMeshComponent, public IRE_InteractiveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URE_ElementComponent();

	//高亮stencil index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_ElementComponent")
	int32 HighlightStencilIndex = 2;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//获取正方向四个顶点世界位置 FRE_Vector4D
	UFUNCTION(BlueprintPure, Category = "RuntimeEditor|RE_ElementComponent")
	FRE_Vector4D GetEditVertexLocations();

	//get bounding box 3D half size
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_ElementComponent")
	bool GetBoundingBox3DHalfSize(FVector& OutSize) const;

	//get bounding box 2D half size
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_ElementComponent")
	bool GetBoundingBox2DHalfSize(FVector2D& OutSize) const;

	//calculate new scale
	FVector CalculateNewScale(const FVector& NewLocation) const;

	//Resize the Component
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_InteractiveComponent")
	void ResizeComponent(const FVector& NewLocation);

	//bIsRE_Selected setter
	void SetIsRe_Selected(bool bInIsRE_Selected);
	
private:
	virtual void OnHovered_Implementation() override;
	virtual void OnUnHovered_Implementation() override;
	//select
	virtual void OnSelected_Implementation() override;
	virtual void OnDeselected_Implementation() override;
	//move
	virtual void OnBeginMove_Implementation() override;
	virtual void OnEndMove_Implementation() override;

	//is selected
	bool bIsRE_Selected = false;

	//begin move location func
	void BeginMoveLocationFunc();
	void MoveComponent();
	APlayerController* GetPlayerController();
	bool GetMouseLocation(FVector& OutMouseLocation);

	//can move
	bool bCanMove = false;

	FVector LastFrameMouseLocation;

	UPROPERTY()
	class APlayerController* PlayerController;
	
	
};
