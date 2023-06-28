// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPickup.h"

#include "CGGameState.h"
#include "CloneGuysV2Character.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ACoinPickup::ACoinPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAlwaysRelevant = true;
	bReplicates = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	//CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnOverlapBegin);
	RootComponent = CollisionSphere;

	//Initialize Static Mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetupAttachment(RootComponent);

}

void ACoinPickup::Server_SetPickupVisibility_Implementation(bool bIsVisible)
{
	SetPickupVisibility(bIsVisible);
}

void ACoinPickup::SetPickupVisibility_Implementation(bool bIsVisible)
{
	if(!bIsVisible)
	{
		StaticMeshComponent->SetVisibility(bIsVisible);
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		StaticMeshComponent->SetVisibility(bIsVisible);
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACoinPickup::ResetPickupVisibility()
{
	GetWorld()->GetTimerManager().ClearTimer(ReAppearTimerHandle);
	Server_SetPickupVisibility(true);
}

void ACoinPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		SetPickupVisibility(false);
		GetWorld()->GetTimerManager().SetTimer(ReAppearTimerHandle, this, &ACoinPickup::ResetPickupVisibility, 3.0f, false);
		
		if(OtherActor && (OtherActor != this))
		{
			if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(OtherActor))
			{
				if(ACGGameState* CGGameState = GetWorld()->GetGameState<ACGGameState>())
				{
					CGGameState->AddPlayerScore(PlayerCharacter->GetPlayerState()->GetPlayerId(), 1);
				}
				//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Blue, *FString::Printf(TEXT("PLAYER DETECTED WOOOO")));
			}
		}
	}
	
}

// Called when the game starts or when spawned
void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

