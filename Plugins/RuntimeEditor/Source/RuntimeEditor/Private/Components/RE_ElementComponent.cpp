// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RE_ElementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/BP_InteractiveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RE_ControllerManager.h"


// Sets default values for this component's properties
URE_ElementComponent::URE_ElementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URE_ElementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URE_ElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bCanMove)
	{
		MoveComponent();
	}
}

FRE_Vector4D URE_ElementComponent::GetEditVertexLocations()
{
	const FVector ComponentLocation      = GetComponentLocation();
	const FVector ComponentForwardVector = GetForwardVector();
	const FVector ComponentRightVector   = GetRightVector();
	const FVector ComponentUpVector      = GetUpVector();
	const FVector Scale                  = GetComponentScale();

	const float TargetX      = ComponentForwardVector.X * GetStaticMesh()->GetBoundingBox().GetSize().X * Scale.X / 2 + ComponentLocation.X;
	const FVector PlanCenter = FVector(TargetX, ComponentLocation.Y, ComponentLocation.Z);

	//获取四个顶点
	const FVector LeftTop     = PlanCenter + ComponentRightVector * GetStaticMesh()->GetBoundingBox().GetSize().Y * Scale.Y / 2 + ComponentUpVector * GetStaticMesh()->GetBoundingBox().GetSize().Z * Scale.Z / 2;
	const FVector RightTop    = PlanCenter + ComponentRightVector * GetStaticMesh()->GetBoundingBox().GetSize().Y * Scale.Y / 2 - ComponentUpVector * GetStaticMesh()->GetBoundingBox().GetSize().Z * Scale.Z / 2;
	const FVector LeftBottom  = PlanCenter - ComponentRightVector * GetStaticMesh()->GetBoundingBox().GetSize().Y * Scale.Y / 2 + ComponentUpVector * GetStaticMesh()->GetBoundingBox().GetSize().Z * Scale.Z / 2;
	const FVector RightBottom = PlanCenter - ComponentRightVector * GetStaticMesh()->GetBoundingBox().GetSize().Y * Scale.Y / 2 - ComponentUpVector * GetStaticMesh()->GetBoundingBox().GetSize().Z * Scale.Z / 2;

	return FRE_Vector4D(LeftTop, RightTop, LeftBottom, RightBottom);
}

bool URE_ElementComponent::GetBoundingBox3DHalfSize(FVector& OutSize) const
{
	//get static mesh
	if (const UStaticMesh* TheStaticMesh = GetStaticMesh())
	{
		//get scale
		const FVector Scale = GetComponentScale();
		OutSize.X           = Scale.X * TheStaticMesh->GetBoundingBox().GetSize().X / 2;
		OutSize.Y           = Scale.Y * TheStaticMesh->GetBoundingBox().GetSize().Y / 2;
		OutSize.Z           = Scale.Z * TheStaticMesh->GetBoundingBox().GetSize().Z / 2;
		return true;
	}
	return false;
}

bool URE_ElementComponent::GetBoundingBox2DHalfSize(FVector2D& OutSize) const
{
	//get static mesh
	if (const UStaticMesh* TheStaticMesh = GetStaticMesh())
	{
		//get scale
		const FVector Scale = GetComponentScale();
		OutSize.X           = Scale.Y * TheStaticMesh->GetBoundingBox().GetSize().Y / 2;
		OutSize.Y           = Scale.Z * TheStaticMesh->GetBoundingBox().GetSize().Z / 2;
		//log Bounding box OutSize
		return true;
	}
	return false;
}

FVector URE_ElementComponent::CalculateNewScale(const FVector& NewLocation) const
{
	FVector OutVector;
	//获取this component的位置
	const FVector ComponentLocation = GetComponentLocation();
	FVector2D Size2D;
	if (GetBoundingBox2DHalfSize(Size2D))
	{
		//计算新的缩放
		OutVector.X = 1;
		OutVector.Y = FMath::Abs(NewLocation.Y - ComponentLocation.Y) / Size2D.X;
		OutVector.Z = FMath::Abs(NewLocation.Z - ComponentLocation.Z) / Size2D.Y;
	}
	//log OutVector
	return OutVector;
}

void URE_ElementComponent::ResizeComponent(const FVector& NewLocation)
{
	//计算新的缩放
	const FVector NewScale = CalculateNewScale(NewLocation);
	//获取当前缩放
	const FVector CurrentScale = GetRelativeScale3D();
	//设置新的缩放
	SetRelativeScale3D(FVector(NewScale.X * CurrentScale.X, NewScale.Y * CurrentScale.Y, NewScale.Z * CurrentScale.Z));
}

void URE_ElementComponent::SetIsRe_Selected(bool bInIsRE_Selected)
{
	bIsRE_Selected = bInIsRE_Selected;
}

void URE_ElementComponent::OnHovered_Implementation()
{
	if (!bIsRE_Selected)
	{
		SetCustomDepthStencilValue(HighlightStencilIndex);
		SetRenderCustomDepth(true);
	}
}

void URE_ElementComponent::OnUnHovered_Implementation()
{
	if (!bIsRE_Selected)
	{
		SetRenderCustomDepth(false);
	}
}

void URE_ElementComponent::OnSelected_Implementation()
{
	bIsRE_Selected = true;
	//C++ 动态生成的Components无法显示， 先在Actor实现， todo C++
	if (GetOwner()->GetClass()->ImplementsInterface(UBP_InteractiveInterface::StaticClass()))
	{
		//select
		IBP_InteractiveInterface::Execute_OnSelected(GetOwner());
	}
	SetCustomDepthStencilValue(HighlightStencilIndex);
	SetRenderCustomDepth(true);
}

void URE_ElementComponent::OnDeselected_Implementation()
{
	bIsRE_Selected = false;
	SetRenderCustomDepth(false);
	if (GetOwner()->GetClass()->ImplementsInterface(UBP_InteractiveInterface::StaticClass()))
	{
		//deselect
		IBP_InteractiveInterface::Execute_OnDeselected(GetOwner());
	}
}

void URE_ElementComponent::OnBeginMove_Implementation()
{
	OnSelected_Implementation();
	bCanMove = true;
	GetMouseLocation(LastFrameMouseLocation);
}

void URE_ElementComponent::OnEndMove_Implementation()
{
	//end move
	bCanMove = false;
}

void URE_ElementComponent::BeginMoveLocationFunc()
{
}

void URE_ElementComponent::MoveComponent()
{
	// OnMoveEvent.Broadcast(NewLocation, this);
	FVector MouseLocation;
	if (GetMouseLocation(MouseLocation))
	{
		const FVector Offset = MouseLocation - LastFrameMouseLocation;
		GetOwner()->AddActorWorldOffset(Offset);
		LastFrameMouseLocation = MouseLocation;
	}
}

APlayerController* URE_ElementComponent::GetPlayerController()
{
	if (!PlayerController)
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

bool URE_ElementComponent::GetMouseLocation(FVector& OutMouseLocation)
{
	FVector WorldLocation;
	FVector WorldDirection;
	if (GetPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) //获取鼠标世界位置
	{
		OutMouseLocation = WorldLocation;
		return true;
	}
	return false;
}
