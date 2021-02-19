// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformMovementLinear.h"

// Sets default values
APlatformMovementLinear::APlatformMovementLinear()
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
void APlatformMovementLinear::BeginPlay()
{
	Super::BeginPlay();
	
	//Set the location of the platform on play
	startingLocation = this->GetActorLocation();
	currentLocation = this->GetActorLocation();
}

// Called every frame
void APlatformMovementLinear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Execute movement if checked
	if (isMoving)
	{
		//Forward on the X axis
		if (moveAxis == 1 && reverse == false)
		{
			//Check to see if it moved out of the distance bounds
			if (currentLocation.X > startingLocation.X + distance || currentLocation.X < startingLocation.X)
			{
				SwitchDirection();
			}
			//Update the new location
			currentLocation.X += speed * direction * DeltaTime;
		}
		//Backward on the X axis
		else if (moveAxis == 1 && reverse == true)
		{
			//Check to see if it moved out of the distance bounds
			if (currentLocation.X < startingLocation.X - distance || currentLocation.X > startingLocation.X)
			{
				SwitchDirection();
			}
			//Update the new location
			currentLocation.X -= speed * direction * DeltaTime;
		}
		//Forward on the Y axis
		else if (moveAxis == 2 && reverse == false)
		{
			if (currentLocation.Y > startingLocation.Y + distance || currentLocation.Y < startingLocation.Y)
			{
				SwitchDirection();
			}

			currentLocation.Y += speed * direction * DeltaTime;
		}
		//Backward on the Y axis
		else if (moveAxis == 2 && reverse == true)
		{
			if (currentLocation.Y < startingLocation.Y - distance || currentLocation.Y > startingLocation.Y)
			{
				SwitchDirection();
			}

			currentLocation.Y -= speed * direction * DeltaTime;
		}
		//Forward on the Z axis
		else if (moveAxis == 3 && reverse == false)
		{
			if (currentLocation.Z > startingLocation.Z + distance || currentLocation.Z < startingLocation.Z)
			{
				SwitchDirection();
			}

			currentLocation.Z += speed * direction * DeltaTime;
		}
		//Backward on the Z axis
		else if (moveAxis == 3 && reverse == true)
		{
			if (currentLocation.Z < startingLocation.Z - distance || currentLocation.Z > startingLocation.Z)
			{
				SwitchDirection();
			}

			currentLocation.Z -= speed * direction * DeltaTime;
		}

		//Move to new location
		SetActorLocation(currentLocation);

		//Set the rotation with the three adjustable parameters
		rotation = FQuat(FRotator(xRotate, yRotate, zRotate));

		//Move the actor with the rotation
		AddActorLocalRotation(rotation, false, 0, ETeleportType::None);
	}
}

void APlatformMovementLinear::SwitchDirection()
{
	direction *= -1;
}

