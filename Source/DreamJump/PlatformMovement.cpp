// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformMovement.h"

// Sets default values
APlatformMovement::APlatformMovement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Default values for some variables. Can be changed within the inspector window
	speed = 500.0f;
	distance = 1000.0f;
	direction = 1;
	xRotate = 0;
	yRotate = 0;
	zRotate = 0;
}

// Called when the game starts or when spawned
void APlatformMovement::BeginPlay()
{
	Super::BeginPlay();

	//Set the location of the platform on play
	startingLocation = this->GetActorLocation();
	currentLocation = this->GetActorLocation();
}

// Called every frame
void APlatformMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Update the universal DeltaTime's variable
	UDeltaTime = DeltaTime;

	//Check to see if the platform should be moving
	if (isMoving)
	{
		//Call the platform's move
		MovePlatform();
	}

	//Set the rotation with the three adjustable parameters
	rotation = FQuat(FRotator(xRotate, yRotate, zRotate));

	//Move the actor with the rotation
	AddActorLocalRotation(rotation, false, 0, ETeleportType::None);
}

//Switches the platform's direction
void APlatformMovement::SwitchDirection()
{
	direction *= -1;
}

void APlatformMovement::MovePlatform()
{
	//Check which axis is being manipulated first
	if (moveAxis == 1)
	{
		//Check to see if the location has moved past the distance defined in either direction
		if (currentLocation.X > startingLocation.X + distance || currentLocation.X < startingLocation.X - distance)
		{
			//Call custom event and not switch direction through C++ code
			SwitchDirection();
		}
		//Update location
		currentLocation.X += speed * direction * UDeltaTime;
	}
	else if (moveAxis == 2)
	{
		if (currentLocation.Y > startingLocation.Y + distance || currentLocation.Y < startingLocation.Y - distance)
		{
			SwitchDirection();
		}
		currentLocation.Y += speed * direction * UDeltaTime;
	}
	else if (moveAxis == 3)
	{
		if (currentLocation.Z > startingLocation.Z + distance || currentLocation.Z < startingLocation.Z - distance)
		{
			SwitchDirection();
		}
		currentLocation.Z += speed * direction * UDeltaTime;
	}
	//Set the new location after calculating
	SetActorLocation(currentLocation);
}