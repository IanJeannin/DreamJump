// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointTrigger.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
ACheckpointTrigger::ACheckpointTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACheckpointTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACheckpointTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Overlap begin function called");
}

void ACheckpointTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Overlap end function called");
}

