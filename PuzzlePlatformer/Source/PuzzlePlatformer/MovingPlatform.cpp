// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include <GameFramework/Actor.h>

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	if (!HasAuthority()) return;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!ForceMove) return;

	if (!HasAuthority()) return;

	if (ActiveTrigger > 0 || ForceMove)
	{
		MovePlatform(DeltaSeconds);
	}
}

void AMovingPlatform::MovePlatform(float DeltaSeconds)
{
	FVector Location = GetActorLocation();

	const FVector FromLocation = ForwardTravel ? GlobalStartLocation : GlobalTargetLocation;

	const FVector ToLocation = ForwardTravel ? GlobalTargetLocation : GlobalStartLocation;

	if (FVector::Dist(Location, ToLocation) < DeadZone)
		ForwardTravel = !ForwardTravel;

	Direction = (ToLocation - FromLocation).GetSafeNormal();

	Location += Direction * Velocity * DeltaSeconds;

	SetActorLocation(Location);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTrigger++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTrigger <= 0) return;

	ActiveTrigger--;
}