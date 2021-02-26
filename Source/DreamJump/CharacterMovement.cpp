// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMovement.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values
ACharacterMovement::ACharacterMovement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;

	/*
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2;
	CameraBoom->CameraLagMaxDistance = 1.5f;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 4;
	CameraBoom->CameraLagMaxTimeStep = 1;
	*/

	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CanDash = true;
	DashDistance = 6000.0f;
	DashCooldown = 1.0f;
	GravMultiplier = 0.1f;
	BaseCustomGravScale = 1.0f;
	FallingGravityScale;
	WalkSpeed = 600.f;
	RunSpeed = 1000.f;




}

// Called when the game starts or when spawned
void ACharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FallCheckHandle, this, &ACharacterMovement::FallCheckTimer, 0.1f, true, 0.f);
	
}

// Called every frame
void ACharacterMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterMovement::CustomJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterMovement::StopCustomJump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterMovement::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacterMovement::Walk);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &ACharacterMovement::Walk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &ACharacterMovement::Sprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterMovement::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterMovement::MoveRight);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACharacterMovement::Dash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &ACharacterMovement::StopDashing);


}

void ACharacterMovement::MoveForward(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
}

void ACharacterMovement::MoveRight(float Axis)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void ACharacterMovement::DoubleJump()
{
	if (DoubleJumpCounter <= 0)
	{
		ACharacterMovement::LaunchCharacter(FVector(0, 0, GetCharacterMovement()->JumpZVelocity), false, true);
		DoubleJumpCounter++;
	}
}
void ACharacterMovement::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void ACharacterMovement::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
void ACharacterMovement::Landed(const FHitResult& Hit)
{
	GetCharacterMovement()->GravityScale = BaseCustomGravScale;
	GetWorld()->GetTimerManager().ClearTimer(GravMultiplierHandle);
	bJumping = false;
	GravMultiplier = 0.1f;
	DoubleJumpCounter = 0;
}
void ACharacterMovement::GravityMultiplierTimer()
{
	if (GetCharacterMovement()->GravityScale < FallingGravityScale && bJumping)
	{
		GetCharacterMovement()->GravityScale += GravMultiplier;
		GravMultiplier += 0.4f;
	}
	if (GetCharacterMovement()->GravityScale >= FallingGravityScale && bJumping)
	{
		GetCharacterMovement()->GravityScale = FallingGravityScale;
	}
}
void ACharacterMovement::FallCheckTimer()
{
	if (GetCharacterMovement()->IsFalling() && !bJumping)
	{
		GetCharacterMovement()->GravityScale = FallingGravityScale;
	}
}
void ACharacterMovement::CustomJump()
{
	Jump();

	GetWorld()->GetTimerManager().SetTimer(GravMultiplierHandle , this, &ACharacterMovement::GravityMultiplierTimer, 0.1f, true, 0.f);
	bJumping = true;
}
void ACharacterMovement::StopCustomJump()
{
	GetCharacterMovement()->GravityScale = FallingGravityScale;
}
void ACharacterMovement::Dash()
{
	if (CanDash)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal() * DashDistance, true, true);

		CanDash = false;

		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACharacterMovement::StopDashing, DashStop, false);

	}
}

void ACharacterMovement::StopDashing()
{
	GetCharacterMovement()->StopActiveMovement();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACharacterMovement::ResetDash, DashCooldown, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;

}
void ACharacterMovement::ResetDash()
{
	CanDash = true;
}

