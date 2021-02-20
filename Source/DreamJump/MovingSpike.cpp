// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManager.h"
#include "Engine.h"
#include "MovingSpike.h"

// Sets default values
AMovingSpike::AMovingSpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	peakheight = 110.0f;
	speed = 50.0f;
	direction = 1;

	canFire = true;
}

// Called when the game starts or when spawned
void AMovingSpike::BeginPlay()
{
	Super::BeginPlay();
	
	startingPosition = this->GetActorLocation();
	currentPosition = this->GetActorLocation();
}

// Called every frame
void AMovingSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UDeltaTime = DeltaTime;

	if (canFire == true)
	{
		MoveSpike();
	}
}

void AMovingSpike::ResetFire()
{
	canFire = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
}

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
			canFire = false;
			direction *= -1;

			GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AMovingSpike::ResetFire, 3.0f, false);
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
			canFire = false;
			direction *= -1;

			GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &AMovingSpike::ResetFire, 3.0f, false);
		}
	}
}

