// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneActors/RE_InteractiveActor.h"
#include "Components/ArrowComponent.h"
#include "Components/RE_ElementComponent.h"
#include "Components/RE_InteractiveComponent.h"


// Sets default values
ARE_InteractiveActor::ARE_InteractiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementComponent              = CreateDefaultSubobject<URE_ElementComponent>(TEXT("ElementComponent"));
	ArrowComponent                = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	RootComponent                 = ArrowComponent;
	ElementComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARE_InteractiveActor::BeginPlay()
{
	DestroyInteractiveComponents();
	Super::BeginPlay();
}


void ARE_InteractiveActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyInteractiveComponents();
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ARE_InteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCanBeMoved)
	{
		MoveActor();
	}
}

FVector ARE_InteractiveActor::GetBoundingBox3DHalfSize() const
{
	return FVector();
}

void ARE_InteractiveActor::ScaleElementComponent(const FVector& Scale)
{
}

void ARE_InteractiveActor::KeepInteractiveComponentsScale()
{
	for (const auto InteractiveComponent : InteractiveComponents)
	{
		if (InteractiveComponent->IsValidLowLevel())
		{
			InteractiveComponent->ResetToDefaultScale();
		}
	}
}

void ARE_InteractiveActor::DestroyInteractiveComponents()
{
	for (const auto InteractiveComponent : InteractiveComponents)
	{
		if (InteractiveComponent)
		{
			InteractiveComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			InteractiveComponent->UnregisterComponent();
			InteractiveComponent->RemoveFromRoot();
		}
	}
	InteractiveComponents.Empty();
}

void ARE_InteractiveActor::MoveActor()
{
	FVector MouseLocation;
	if (GetMouseLocation(MouseLocation))
	{
		const FVector Offset = MouseLocation - LastFrameMouseLocation;
		AddActorWorldOffset(Offset);
		LastFrameMouseLocation = MouseLocation;
	}
}

bool ARE_InteractiveActor::GetMouseLocation(FVector& OutMouseLocation)
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

APlayerController* ARE_InteractiveActor::GetPlayerController()
{
	if (!PlayerController)
	{
		if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
		{
			PlayerController = Controller;
		}
	}
	return PlayerController;
}

void ARE_InteractiveActor::OnScaleComponentMoving(FVector NewLocation, URE_InteractiveComponent* InteractiveComponent)
{
	ElementComponent->ResizeComponent(NewLocation);
	KeepInteractiveComponentsScale();
}

void ARE_InteractiveActor::CreateInteractiveComponentsFunc()
{
	CreateInteractiveComponent(LeftTopInteractiveComponent, ERE_DirectionType::LeftTop);
	CreateInteractiveComponent(LeftBottomInteractiveComponent, ERE_DirectionType::LeftBottom);
	CreateInteractiveComponent(RightTopInteractiveComponent, ERE_DirectionType::RightTop);
	CreateInteractiveComponent(RightBottomInteractiveComponent, ERE_DirectionType::RightBottom);
}

void ARE_InteractiveActor::CreateInteractiveComponent(URE_InteractiveComponent* OutInteractiveComponent,ERE_DirectionType DirectionType)
{
	OutInteractiveComponent = NewObject<URE_InteractiveComponent>(this, GetInteractiveComponentClass());
	OutInteractiveComponent->RegisterComponent();
	OutInteractiveComponent->AddToRoot();
	OutInteractiveComponent->AttachToComponent(ElementComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), NAME_None);
	OutInteractiveComponent->SetWorldLocation(GetElementEdgeLocation(DirectionType));
	OutInteractiveComponent->OnMoveEvent.AddDynamic(this, &ARE_InteractiveActor::OnScaleComponentMoving);
	OutInteractiveComponent->InteractiveDirectionType = DirectionType;
	InteractiveComponents.Add(OutInteractiveComponent);
}

FVector ARE_InteractiveActor::GetElementEdgeLocation(ERE_DirectionType DirectionType) const
{
	switch (DirectionType)
	{
		case ERE_DirectionType::LeftTop:
			return ElementComponent->GetEditVertexLocations().LeftTop;
		case ERE_DirectionType::LeftBottom:
			return ElementComponent->GetEditVertexLocations().LeftBottom;
		case ERE_DirectionType::RightTop:
			return ElementComponent->GetEditVertexLocations().RightTop;
		case ERE_DirectionType::RightBottom:
			return ElementComponent->GetEditVertexLocations().RightBottom;
		default:
			return FVector::ZeroVector;
	}
	return FVector::ZeroVector;
}

void ARE_InteractiveActor::OnSelected_Implementation()
{
	CreateInteractiveComponentsFunc();
}

void ARE_InteractiveActor::OnDeselected_Implementation()
{
	DestroyInteractiveComponents();
}

void ARE_InteractiveActor::OnDeselectedInteractiveComponent_Implementation()
{
	DestroyInteractiveComponents();
	ElementComponent->SetRenderCustomDepth(false);
	ElementComponent->SetIsRe_Selected(false);
}


void ARE_InteractiveActor::CreateInteractiveComponents_Implementation()
{
}

TSubclassOf<URE_InteractiveComponent> ARE_InteractiveActor::GetInteractiveComponentClass_Implementation()
{
	//log
	UE_LOG(LogTemp, Warning, TEXT("ARE_InteractiveActor::GetInteractiveComponentClass_Implementation"));
	return URE_InteractiveComponent::StaticClass();
}
