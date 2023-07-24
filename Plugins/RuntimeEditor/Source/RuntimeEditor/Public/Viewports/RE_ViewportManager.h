// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Engine/Classes/Engine/ViewportSplitScreen.h"
#include "RE_ViewportManager.generated.h"

// struct FPerPlayerSplitscreenData;

//struct FRE_SplitScreenData

USTRUCT(BlueprintType)
struct FRE_SplitScreenData
{
	GENERATED_BODY()

	//size X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_SplitScreenData")
	float SizeX = 0;

	//size Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_SplitScreenData")
	float SizeY = 0;

	//origin X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_SplitScreenData")
	float OriginX = 0;

	//origin Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_SplitScreenData")
	float OriginY = 0;

	//constructor
	FRE_SplitScreenData()
		: SizeX(0), SizeY(0), OriginX(0), OriginY(0)
	{
	};

	FRE_SplitScreenData(float InSizeX, float InSizeY, float InOriginX, float InOriginY)
	{
		SizeX   = InSizeX;
		SizeY   = InSizeY;
		OriginX = InOriginX;
		OriginY = InOriginY;
	}

	//convert to FPerPlayerSplitScreenData
	FPerPlayerSplitscreenData ConvertToPerPlayerSplitScreenData() const
	{
		FPerPlayerSplitscreenData PerPlayerSplitScreenData;
		PerPlayerSplitScreenData.SizeX   = SizeX;
		PerPlayerSplitScreenData.SizeY   = SizeY;
		PerPlayerSplitScreenData.OriginX = OriginX;
		PerPlayerSplitScreenData.OriginY = OriginY;
		return PerPlayerSplitScreenData;
	}
};


UCLASS()
class RUNTIMEEDITOR_API ARE_ViewportManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARE_ViewportManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//init viewports
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor")
	void InitViewports();

	//PerPlayerSplitScreenData info

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuntimeEditor|RE_ViewportManager")
	FRE_SplitScreenData SplitScreenData = FRE_SplitScreenData(0.5, 1.0, 0.25, 0.0);
};
