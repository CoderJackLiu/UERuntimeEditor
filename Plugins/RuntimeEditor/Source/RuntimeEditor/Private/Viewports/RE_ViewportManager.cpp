// Fill out your copyright notice in the Description page of Project Settings.


#include "Viewports/RE_ViewportManager.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARE_ViewportManager::ARE_ViewportManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARE_ViewportManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARE_ViewportManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARE_ViewportManager::InitViewports()
{
	FSplitscreenData ScreenData;
	ScreenData.PlayerData.Add(FPerPlayerSplitscreenData(0.f, 0.f, 0.0f, 0.0f));
	ScreenData.PlayerData.Add(SplitScreenData.ConvertToPerPlayerSplitScreenData());
	UGameViewportClient* Viewport   = GetWorld()->GetGameViewport();
	Viewport->MaxSplitscreenPlayers = 2;
	Viewport->SetForceDisableSplitscreen(true);
	Viewport->SplitscreenInfo[ESplitScreenType::None] = ScreenData;
}
