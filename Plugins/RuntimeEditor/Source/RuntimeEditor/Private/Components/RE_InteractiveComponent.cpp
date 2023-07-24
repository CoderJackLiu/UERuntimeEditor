// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RE_InteractiveComponent.h"
#include "Interfaces/BP_InteractiveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RE_ControllerManager.h"


// Sets default values for this component's properties
URE_InteractiveComponent::URE_InteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URE_InteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
	DefaultScale = GetComponentScale();

	// ...
}


// Called every frame
void URE_InteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bCanMove)
	{
		MoveComponent();
	}
}

void URE_InteractiveComponent::OnBeginMove_Implementation()
{
	//开始移动
	UE_LOG(LogTemp, Warning, TEXT("URE_InteractiveComponent::OnBeginMove_Implementation"));
	bCanMove                                  = true;
	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = GetInteractiveDirectionType();
}

void URE_InteractiveComponent::OnEndMove_Implementation()
{
	bCanMove = false;

	GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Default;
}

void URE_InteractiveComponent::OnSelected_Implementation()
{
}

void URE_InteractiveComponent::OnDeselected_Implementation()
{
	//C++ 动态生成的Components无法显示， 先蓝图实现， todo C++
	if (GetOwner()->GetClass()->ImplementsInterface(UBP_InteractiveInterface::StaticClass()))
	{
		//deselect
		IBP_InteractiveInterface::Execute_OnDeselectedInteractiveComponent(GetOwner());
	}
}

void URE_InteractiveComponent::MoveComponent()
{
	//获取鼠标世界位置
	FVector WorldLocation;
	FVector WorldDirection;

	GetPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	//将this component的位置在Y轴和Z轴上设置为鼠标世界位置
	FVector NewLocation = GetComponentLocation();
	NewLocation.Y       = WorldLocation.Y;
	NewLocation.Z       = WorldLocation.Z;
	SetWorldLocation(NewLocation);
	OnMoveEvent.Broadcast(NewLocation, this);
}

void URE_InteractiveComponent::ResetToDefaultScale()
{
	SetWorldScale3D(DefaultScale);
}

EMouseCursor::Type URE_InteractiveComponent::GetInteractiveDirectionType() const
{
	switch (InteractiveDirectionType)
	{
	case ERE_DirectionType::LeftTop:
		return EMouseCursor::ResizeSouthEast;
	case ERE_DirectionType::RightTop:
		return EMouseCursor::ResizeSouthWest;
	case ERE_DirectionType::LeftBottom:
		return EMouseCursor::ResizeSouthWest;
	case ERE_DirectionType::RightBottom:
		return EMouseCursor::ResizeSouthEast;
	}
	return EMouseCursor::Default;
}

APlayerController* URE_InteractiveComponent::GetPlayerController()
{
	if (PlayerController == nullptr)
	{
		const int32 PlayerIndex = URE_ControllerManager::Get()->GetControllerIndex();
		if (PlayerIndex == 0)
		{
			PlayerController = GetWorld()->GetFirstPlayerController();
		}
		else
		{
			PlayerController = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), PlayerIndex);
		}
	}
	return PlayerController;
}
