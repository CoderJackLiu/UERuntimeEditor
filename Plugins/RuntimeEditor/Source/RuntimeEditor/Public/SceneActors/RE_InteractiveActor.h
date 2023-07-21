// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BP_InteractiveInterface.h"
#include "Components/RE_InteractiveComponent.h"
#include "RE_InteractiveActor.generated.h"

UCLASS()
class RUNTIMEEDITOR_API ARE_InteractiveActor : public AActor , public IBP_InteractiveInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARE_InteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//static mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|InteractiveActor")
	class URE_ElementComponent* ElementComponent;

	//arrow component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|InteractiveActor")
	class UArrowComponent* ArrowComponent;

	//蓝图实现，获取交互组件类
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|InteractiveActor")
	TSubclassOf<class URE_InteractiveComponent> GetInteractiveComponentClass();

	//get bounding box 3D half size
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|InteractiveActor")
	FVector GetBoundingBox3DHalfSize() const;

	//生成交互组件
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "RuntimeEditor|InteractiveActor")
	void CreateInteractiveComponents();

	//Scale ElementComponent
	void ScaleElementComponent(const FVector& Scale);
	
	//选中材质 test
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|InteractiveActor")
	UMaterialInterface* SelectedMaterial;

	//非选中材质 test
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|InteractiveActor")
	UMaterialInterface* UnSelectedMaterial;

	//keep interactive components scale func
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|InteractiveActor")
	void KeepInteractiveComponentsScale();

	//destroy interactive components
	void DestroyInteractiveComponents();
	
	//current frame mouse location
	FVector LastFrameMouseLocation;

	//move actor
	void MoveActor();
	
	//get mouse location
	bool GetMouseLocation(FVector& OutMouseLocation) ;
	
	
private:
	//can be moved
	bool bCanBeMoved;

	//get playercontroller
	class APlayerController* GetPlayerController() ;
	

	//player controller
	UPROPERTY()
	class APlayerController* PlayerController;

	UFUNCTION()
	void OnScaleComponentMoving(FVector NewLocation, URE_InteractiveComponent* InteractiveComponent);
	
	//Create Interactive Components
	void CreateInteractiveComponentsFunc();

	void CreateInteractiveComponent(URE_InteractiveComponent* OutInteractiveComponent,ERE_DirectionType DirectionType);

	//get element edge location
	FVector GetElementEdgeLocation(ERE_DirectionType DirectionType) const;
	//interactive components
	//left top
	UPROPERTY()
	URE_InteractiveComponent* LeftTopInteractiveComponent;

	//left bottom
	UPROPERTY()
	URE_InteractiveComponent* LeftBottomInteractiveComponent;

	//right top
	UPROPERTY()
	URE_InteractiveComponent* RightTopInteractiveComponent;

	//right bottom
	UPROPERTY()
	URE_InteractiveComponent* RightBottomInteractiveComponent;
	
	//交互组件数组
	UPROPERTY()
	TArray<URE_InteractiveComponent*> InteractiveComponents;

	
	//overrided function
	virtual void OnSelected_Implementation() override;
	virtual void OnDeselected_Implementation() override;
	virtual void OnDeselectedInteractiveComponent_Implementation() override;
};
