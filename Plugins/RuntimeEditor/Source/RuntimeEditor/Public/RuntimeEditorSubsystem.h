// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RuntimeEditorSubsystem.generated.h"

/**
 * 
 */

//物体类型:背景/图片/人物/文字

UENUM(BlueprintType)
enum class ERE_ElementType : uint8
{
	Background,
	Image,
	Character,
	Text
};


UCLASS()
class RUNTIMEEDITOR_API URuntimeEditorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Called once all UWorldSubsystems have been initialized */
	virtual void PostInitialize() override;
	
	/** Called when world is ready to start gameplay before the game mode transitions to the correct state and call BeginPlay on all actors */
	virtual void OnWorldBeginPlay(UWorld& InWorld) override ;


protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;



private:
	//图层管理

	//整个思路是有地方根据图层值获取对应的X轴的值，图层越大，X轴越大，物体越靠前，图层越小，X轴越小，物体越靠后
	//存放当前所有物体的最大的图层值，每次创建物体的时候，图层值+1，这样就可以保证每次创建的物体都是在最前面的
	//当删除物体的时候，重新计算当前最大的图层值
	//当修改物体的图层值的时候，重新计算当前最大的图层值
	//物体本身记录图层值，修改物体图层需要修改物体本身的图层值，且其自动修改X轴的值
	
	
	
	//物体管理
	//选中删除
	//选中粘贴

	
	//添加物体 func
	AActor* SpawnNewInteractiveActor(ERE_ElementType ObjectType, FVector2D Location, FVector2D Size);

	//清空所有物体
	void ClearAllInteractiveActor();

	//删除物体
	// void DeleteInteractiveActor(AActor* Actor);
	

	
	
};
