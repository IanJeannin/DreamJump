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

	FVector startingPosition;
	FVector currentPosition;

	float speed;
	float peakheight;
	int direction;
	float UDeltaTime;

	bool canFire;
	FTimerHandle FireDelayTimerHandle;
	void ResetFire();

	void MoveSpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
