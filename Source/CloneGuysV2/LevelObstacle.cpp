// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObstacle.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ALevelObstacle::ALevelObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true); //Default replicated movement will suffice for this demonstration
	bAlwaysRelevant = true; //We want to keep relevancy for late joiners
	bReplicates = true;

	//Initialize Root Component
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootScene;

	//Initialize Capsule Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CapsuleComponent->InitCapsuleSize(50.0f, 50.0f);
	CapsuleComponent->SetupAttachment(RootComponent);

	//Initialize Static Mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetupAttachment(RootComponent);

	//Initialize Rotating Movement Component
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate = FRotator(0.f, 0.f, 0.f); //Not everything has to rotate, but some obstacles will

}

// Called when the game starts or when spawned
void ALevelObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelObstacle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

