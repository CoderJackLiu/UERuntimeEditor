// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeEditorSubsystem.h"

bool URuntimeEditorSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
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

AActor* URuntimeEditorSubsystem::SpawnNewInteractiveActor(ERE_ElementType ObjectType, FVector2D Location, FVector2D Size)
{
	// switch (ObjectType)
	// {
	// case ERE_ElementType::Background:
	// 	
	// 	return SpawnNewBackgroundActor(Location, Size);
	// case ERE_ElementType::Image:
	// 	return SpawnNewImageActor(Location, Size);
	// case ERE_ElementType::Character:
	// 	return SpawnNewCharacterActor(Location, Size);
	// case ERE_ElementType::Text:
	// 	return SpawnNewTextActor(Location, Size);
	// }
	return nullptr;
}

void URuntimeEditorSubsystem::ClearAllInteractiveActor()
{
}
