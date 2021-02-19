// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformMovementLinear.generated.h"

UCLASS()
class DREAMJUMP_API APlatformMovementLinear : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformMovementLinear();

	//The location of the platform when it begins and where it currently is in motion
	FVector currentLocation;
	FVector startingLocation;

	//Variable that does the rotation
	FQuat rotation;

	//Checkbox to determine moving or not
	UPROPERTY(EditAnywhere)
		bool isMoving;

	//Speed of the platform
	UPROPERTY(EditAnywhere)
		float speed;

	//The distance from the center that the platform will move
	UPROPERTY(EditAnywhere)
		float distance;

	//The axis the platform will move. 1 for X, 2 for Y, 3 for Z
	UPROPERTY(EditAnywhere)
		int moveAxis;

	//Either 1 or -1, changed automatically in code to reverse the platform direction
		int direction;

	//True for reverse movement, false for forward
	UPROPERTY(EditAnywhere)
		bool reverse;

	//Rotate the X axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float xRotate;
	//Rotate the Y axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float yRotate;
	//Rotate the Z axis a certain units per frame
	UPROPERTY(EditAnywhere)
		float zRotate;

	//Function to reverse the direction of travel
	void SwitchDirection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
