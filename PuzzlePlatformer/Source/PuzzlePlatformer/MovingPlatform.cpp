// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include <GameFramework/Actor.h>

AMovingPlatform::AMovingPlatform()
{
	Move = true;
	Direction = FVector(1, 0, 0);
	Velocity = 1;
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(!HasAuthority()) return;

	SetReplicates(true);
	SetReplicateMovement(true);
	
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Move) return;
	if (!HasAuthority()) return;
	
	FVector Location = GetActorLocation();
	Location += FVector(Direction.X * Velocity, Direction.Y * Velocity, Direction.Z * Velocity);

	SetActorLocation(Location);
}
