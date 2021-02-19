// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CharacterMovement.generated.h"

UCLASS()
class DREAMJUMP_API ACharacterMovement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterMovement();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera; 

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	void CustomJump();
	void StopCustomJump();

	

	void GravityMultiplierTimer();
	void FallCheckTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float GravMultiplier = 0.1f;
	UPROPERTY(EditAnywhere)
	bool bJumping;
	UPROPERTY(EditAnywhere)
		float BaseCustomGravScale;
	UPROPERTY(EditAnywhere)
		float MaxCustomGravityScale;
	//UPROPERTY(EditAnywhere)
		//float CustomJumpHeight;

	UFUNCTION()
		void DoubleJump();

	UPROPERTY()
		int DoubleJumpCounter;

	UFUNCTION()
		void Walk();

	UFUNCTION()
		void Dash();

	UPROPERTY(EditAnywhere)
		float DashDistance;
	UPROPERTY(EditAnywhere)
		float DashCooldown;
	UPROPERTY(EditAnywhere)
		bool CanDash;
	UPROPERTY(EditAnywhere)
		float DashStop = 0.1f;

	UFUNCTION()
		void StopDashing();
	UFUNCTION()
		void ResetDash();
	UPROPERTY()
		FTimerHandle UnusedHandle;
	UPROPERTY()
		FTimerHandle GravMultiplierHandle;
	UPROPERTY()
		FTimerHandle FallCheckHandle;
		


};
