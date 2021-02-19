// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine.h"
#include "MovingSpike.generated.h"

UCLASS()
class DREAMJUMP_API AMovingSpike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingSpike();

	//Positions of the spikes to be used in the main
	FVector startingPosition;
	FVector currentPosition;

	//Speed in which the spike travels
	UPROPERTY(EditAnywhere)
		float speed;

	//The number of SECONDS the spike will stay at it's two peaks
	UPROPERTY(EditAnywhere)
		float delaySeconds;

	//Distance from the starting position in which travel ends
	float peakheight;
	//Direction the spike will travel
	int direction;
	//Universal storage float for DeltaTime
	float UDeltaTime;

	//Determines whether or not the spike is able to move again
	bool canFire;
	//Handle used with setting a timer
	FTimerHandle FireDelayTimerHandle;
	//Function to allow the spike to move again
	void ResetFire();

	//Move the spike
	void MoveSpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
