// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "PlatformMovement.generated.h"

UCLASS()
class DREAMJUMP_API APlatformMovement : public AActor
{
	GENERATED_BODY()
	
public:
	//The location of the platform when it begins and where it currently is in motion
	FVector currentLocation;
	FVector startingLocation;

	//Variable that does the rotation
	FQuat rotation;
	
	//A universal float to log DeltaTime when out of scope
	float UDeltaTime;

	//To be used later to set up a delay in platform directional switch
	FTimerHandle tempTimerHandle;

	//Checkbox to determine moving or not
	UPROPERTY(EditAnywhere)
		bool isMoving;

	//Checkbox to determine rotation or not
	UPROPERTY(EditAnywhere)
		bool isRotating;
	
	//Speed of the platform
	UPROPERTY(EditAnywhere)
		float speed;

	//The distance from the center that the platform will move
	UPROPERTY(EditAnywhere)
		float distance;

	//The axis the platform will move. 1 for X, 2 for Y, 3 for Z
	UPROPERTY(EditAnywhere)
		int moveAxis;

	//The axis the platform will rotate upon. 1 for X, 2 for Y, 3 for Z
	UPROPERTY(EditAnywhere)
		int rotateAxis;

	//Rotate the X axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float xRotate;
	//Rotate the Y axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float yRotate;
	//Rotate the Z axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float zRotate;

	//Either 1 or -1, changed automatically in code to reverse the platform direction
	int direction;

	// Sets default values for this actor's properties
	APlatformMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Switch the platform's direction. To be later used with a timer
	UFUNCTION(BlueprintCallable)
	void SwitchDirection();

public:
	//Function to move, later called within blueprints to adjust delay
	UFUNCTION(BlueprintCallable)
	void MovePlatform();
};
