// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingSpike.h"
#include "TimerManager.h"
#include "Engine.h"

// Sets default values
AMovingSpike::AMovingSpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting default values
	peakheight = 110.0f;
	speed = 600.0f;
	delaySeconds = 1.5f;
	direction = 1;
	canFire = true;
}

// Called when the game starts or when spawned
void AMovingSpike::BeginPlay()
{
	Super::BeginPlay();
	
	//Log the positions on play
	startingPosition = this->GetActorLocation();
	currentPosition = this->GetActorLocation();
}

// Called every frame
void AMovingSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Update the universal float each frame
	UDeltaTime = DeltaTime;

	//As long as it can move, move it
	if (canFire == true)
	{
		MoveSpike();
	}
}

//Reset the fire modifier and clear the timer
void AMovingSpike::ResetFire()
{
	canFire = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
}

//Function that handles the movement commands
void AMovingSpike::MoveSpike()
{
	//Moving DOWN
	if (direction == 1)
	{
		//If it hasn't reached its bottom peak yet, move it
		if (currentPosition.Z >= startingPosition.Z - peakheight)
		{
			currentPosition.Z -= speed * UDeltaTime;
			SetActorLocation(currentPosition);
		}
		//Runs once it reaches its bottom peak
		else
		{
			//Disable moving and switch directions
			canFire = false;
			direction *= -1;

			//Start a timer to be able to move again
			GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AMovingSpike::ResetFire, delaySeconds, false);
		}
	}
	//Moving UP
	else if (direction == -1)
	{
		//If it hasn't reached its top peak yet, move it
		if (currentPosition.Z < startingPosition.Z)
		{
			currentPosition.Z += speed * UDeltaTime;
			SetActorLocation(currentPosition);
		}
		//Runs once it reaches its top peak
		else
		{
			//Disable moving and switch directions
			canFire = false;
			direction *= -1;

			//Start a timer to be able to move again
			GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AMovingSpike::ResetFire, delaySeconds, false);
		}
	}
}

