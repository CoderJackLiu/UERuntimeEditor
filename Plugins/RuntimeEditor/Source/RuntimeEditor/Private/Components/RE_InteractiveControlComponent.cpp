// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RE_InteractiveControlComponent.h"
#include "Components/RE_ElementComponent.h"
#include "Components/RE_InteractiveComponent.h"
#include "Interfaces/BP_InteractiveInterface.h"
#include "Interfaces/RE_InteractiveInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SceneActors/RE_InteractiveActor.h"


// Sets default values for this component's properties
URE_InteractiveControlComponent::URE_InteractiveControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URE_InteractiveControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URE_InteractiveControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	LineTrace();
}

bool URE_InteractiveControlComponent::LineTrace()
{
	//mouse world space location
	FVector WorldLocation;
	FVector WorldDirection;
	if (GetPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		//ray trace start location
		FVector StartLocation = WorldLocation;
		//ray trace end location
		FVector EndLocation = WorldLocation + WorldDirection * 10000.f;

		// TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes = TArray<TEnumAsByte<EObjectTypeQuery> >();
		const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic)};
		const TArray<AActor*> ActorsToIgnore{GetOwner()};
		FHitResult HitResult;
		if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true))
		{
			if (AActor* HitActor = HitResult.GetActor())
			{
				//check hover element component
				if (CurrentHoverElementComponent != HitResult.Component.Get())
				{
					UnHoverElementComponent(CurrentHoverElementComponent);
					//hover element component
					HoverElementComponent(HitResult.Component.Get());
					return true;
				}
				return true;
			}
		}
	}
	UnHoverElementComponent(CurrentHoverElementComponent);
	return false;
}

void URE_InteractiveControlComponent::LineTraceDetect(FHitResult& OutHitResult, bool& Hit, ERE_InteractType& InteractType)
{
	//mouse world space location
	FVector WorldLocation;
	FVector WorldDirection;
	if (GetPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector StartLocation = WorldLocation;
		FVector EndLocation = WorldLocation + WorldDirection * 10000.f;
		const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic)};
		const TArray<AActor*> ActorsToIgnore{GetOwner()};
		FHitResult HitResult;
		if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true))
		{
			if (HitResult.GetActor())
			{
				OutHitResult = HitResult;
				Hit          = true;
				return;
			}
		}
	}
	Hit = false;
}


bool URE_InteractiveControlComponent::Click(ERE_InteractType& InteractType)
{
	//declare hit result
	FHitResult HitResult;
	//declare hit
	bool bHit = false;
	LineTraceDetect(HitResult, bHit, InteractType);
	if (bHit)
	{
		if (GetInteractType(InteractType, HitResult))
		{
			if (InteractType == ERE_InteractType::Scale)
			{
				if (CurrentInteractComponent != HitResult.GetComponent())
				{
					// if (CurrentInteractComponent) { Deselect(); }
					CurrentInteractComponent = HitResult.GetComponent();
					bCanInteract             = true;
					if (HasComponentInteractiveInterface(HitResult.GetComponent()))
					{
						IRE_InteractiveInterface::Execute_OnBeginMove(CurrentInteractComponent);
					}
					CurrentInteractActor = HitResult.GetActor();
				}
				return true;
			}
			//move
			if (InteractType == ERE_InteractType::Move)
			{
				if (CurrentInteractComponent != HitResult.GetComponent())
				{
					if (CurrentInteractComponent) { Deselect(); }
					CurrentInteractComponent = HitResult.GetComponent();
					bCanInteract             = true;
				}
				if (HasComponentInteractiveInterface(CurrentInteractComponent))
				{
					IRE_InteractiveInterface::Execute_OnBeginMove(CurrentInteractComponent);
				}
				CurrentInteractActor = HitResult.GetActor();
				return true;
			}
			//rotate
		}
	}
	DeselectOwner();
	return false;
}

bool URE_InteractiveControlComponent::GetInteractType(ERE_InteractType& InteractType, FHitResult HitResult)
{
	//get hit actor
	AActor* HitActor = HitResult.GetActor();
	//hit actor is interactive actor
	if (Cast<ARE_InteractiveActor>(HitActor))
	{
		//get interactive component
		if (URE_InteractiveComponent* InteractiveComponent = Cast<URE_InteractiveComponent>(HitResult.Component.Get()))
		{
			InteractType = ERE_InteractType::Scale;
			return true;
		}
		//get main element
		if (URE_ElementComponent* MainElement = Cast<URE_ElementComponent>(HitResult.Component.Get()))
		{
			InteractType = ERE_InteractType::Move;
			return true;
		}
	}
	return false;
}

void URE_InteractiveControlComponent::ReleaseClick()
{
	bCanInteract = false;
	if (HasComponentInteractiveInterface(CurrentInteractComponent))
	{
		IRE_InteractiveInterface::Execute_OnEndMove(CurrentInteractComponent);
	}
}

void URE_InteractiveControlComponent::Select(AActor* InActor) const
{
	
}

void URE_InteractiveControlComponent::Deselect()
{
	//deselected element component
	if (CurrentInteractComponent)
	{
		if (HasComponentInteractiveInterface(CurrentInteractComponent))
		{
			IRE_InteractiveInterface::Execute_OnDeselected(CurrentInteractComponent);
		}
		CurrentInteractComponent = nullptr;
	}
}

void URE_InteractiveControlComponent::DeselectOwner()
{
	if (CurrentInteractComponent)
	{
		if (HasInteractiveInterface(CurrentInteractComponent->GetOwner()))
		{
			IBP_InteractiveInterface::Execute_OnDeselectedInteractiveComponent(CurrentInteractComponent->GetOwner());
		}
		CurrentInteractComponent = nullptr;
	}
}

APlayerController* URE_InteractiveControlComponent::GetPlayerController()
{
	if (PlayerController == nullptr)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
	}
	return PlayerController;
}

void URE_InteractiveControlComponent::HoverElementComponent(UPrimitiveComponent* InComponent)
{
	if (InComponent)
	{
		if (InComponent->GetClass()->ImplementsInterface(URE_InteractiveInterface::StaticClass()))
		{
			IRE_InteractiveInterface::Execute_OnHovered(InComponent);
			CurrentHoverElementComponent = InComponent;
		}
	}
}

void URE_InteractiveControlComponent::UnHoverElementComponent(UPrimitiveComponent* InComponent)
{
	if (InComponent)
	{
		if (InComponent->GetClass()->ImplementsInterface(URE_InteractiveInterface::StaticClass()))
		{
			IRE_InteractiveInterface::Execute_OnUnHovered(InComponent);
			CurrentHoverElementComponent = nullptr;
		}
	}
}

bool URE_InteractiveControlComponent::HasInteractiveInterface(const AActor* InActor)
{
	if (InActor)
	{
		return InActor->GetClass()->ImplementsInterface(UBP_InteractiveInterface::StaticClass());
	}
	return false;
}

bool URE_InteractiveControlComponent::HasComponentInteractiveInterface(UPrimitiveComponent* InComponent)
{
	if (InComponent)
	{
		CurrentInteractComponent = InComponent;
		return InComponent->GetClass()->ImplementsInterface(URE_InteractiveInterface::StaticClass());
	}
	return false;
}
