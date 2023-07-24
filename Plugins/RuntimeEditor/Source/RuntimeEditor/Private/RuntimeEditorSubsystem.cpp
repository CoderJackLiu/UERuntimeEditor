// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeEditorSubsystem.h"

#include "Managers/RE_ControllerManager.h"

bool URuntimeEditorSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	//world name
	FString WorldName = Outer->GetWorld()->GetName();
	//log world name
	UE_LOG(LogTemp, Warning, TEXT("WorldName:%s"), *WorldName);
	const FString TargetWorldName = URE_ControllerManager::Get()->GetSettings()->GetWorldName();
	//log TargetWorldName
	UE_LOG(LogTemp, Warning, TEXT("TargetWorldName:%s"), *TargetWorldName);
	return DoesSupportWorldType(Outer->GetWorld()->WorldType);
}

void URuntimeEditorSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void URuntimeEditorSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void URuntimeEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool URuntimeEditorSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::PIE || WorldType == EWorldType::Game;
}

void URuntimeEditorSubsystem::Deinitialize()
{
	URE_ControllerManager::Get()->DestroyInstance();
	Super::Deinitialize();
}

AActor* URuntimeEditorSubsystem::SpawnNewInteractiveActor(ERE_ElementType ObjectType, FVector2D Location, FVector2D Size)
{
	return nullptr;
}

void URuntimeEditorSubsystem::ClearAllInteractiveActor()
{
}
