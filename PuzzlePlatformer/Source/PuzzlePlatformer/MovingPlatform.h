// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Velocity = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (MakeEditWidget = true))
		FVector TargetLocation;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool ForceMove = false;

	UPROPERTY(EditAnywhere,  Category = "Movement")
		int ActiveTrigger = 0;

	bool ForwardTravel = true;

	float DeadZone = 5.f;

	FVector GlobalStartLocation;

	FVector GlobalTargetLocation;

	FVector Direction;

public:

	AMovingPlatform();

	void AddActiveTrigger();

	void RemoveActiveTrigger();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void MovePlatform(float DeltaSeconds);
};
