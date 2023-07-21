// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RE_InteractiveControlComponent.generated.h"

UENUM(BlueprintType)
enum class ERE_InteractType : uint8
{
	//move
	Move,
	//rotate
	Rotate,
	//scale
	Scale,
};

//RE hit result
USTRUCT(BlueprintType)
struct RUNTIMEEDITOR_API FRE_HitResult
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY()
	FVector HitLocation;

public:
	//get hit actor
	AActor* GetHitActor() const;

	//get hit component
	UPrimitiveComponent* GetHitComponent() const;

private:
	//hit actor
	UPROPERTY()
	mutable TWeakObjectPtr<AActor> HitActor;

	//hit component
	UPROPERTY()
	mutable TWeakObjectPtr<UPrimitiveComponent> HitComponent;
};


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RUNTIMEEDITOR_API URE_InteractiveControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URE_InteractiveControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	bool LineTrace();

	void LineTraceDetect(FHitResult& OutHitResult, bool& Hit, ERE_InteractType& InteractType);

	//Click
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_InteractiveControlComp")
	bool Click(ERE_InteractType& InteractType);

	bool GetInteractType(ERE_InteractType& InteractType, FHitResult HitResult);

	//Release Click
	UFUNCTION(BlueprintCallable, Category = "RuntimeEditor|RE_InteractiveControlComp")
	void ReleaseClick();

private:
	//SELECT
	void Select(AActor* InActor) const;

	//DESELECT
	void Deselect();

	//deselect owner
	void DeselectOwner();

	//get playercontroller
	class APlayerController* GetPlayerController();


	//player controller
	UPROPERTY()
	class APlayerController* PlayerController;

	UPROPERTY()
	UPrimitiveComponent* CurrentInteractComponent;

	bool bCanInteract = false;

	//hover element component func
	void HoverElementComponent(UPrimitiveComponent* InComponent);

	//unhover element component func
	void UnHoverElementComponent(UPrimitiveComponent* InComponent);


	//current hover element component
	UPROPERTY()
	UPrimitiveComponent* CurrentHoverElementComponent;

	//current interact Actor
	UPROPERTY()
	AActor* CurrentInteractActor = nullptr;


	static bool HasInteractiveInterface(const AActor* InActor);
	//component has interactive interface
	bool HasComponentInteractiveInterface(UPrimitiveComponent* InComponent);
};
