// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get moving platform's location
	FVector	CurrentLocation = GetActorLocation();
	// Move the platform by platform velocity
	CurrentLocation += PlatformVelocity * DeltaTime;
	// Update platform position
	SetActorLocation(CurrentLocation);

	// Calculate distance traveled by platform
	float DistanceTraveled = FVector::Dist(StartingLocation, CurrentLocation);

	// If the distance moved is beyond our clamp...
	if (DistanceTraveled > DistanceClamp)
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartingLocation += MoveDirection * DistanceClamp;
		SetActorLocation(StartingLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}
