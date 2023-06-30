// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryVolume.h"

#include "CGGameMode.h"
#include "CGGameState.h"
#include "CGPlayerController.h"
#include "CGPlayerState.h"
#include "CloneGuysV2Character.h"
#include "Chaos/GeometryParticlesfwd.h"
#include "Kismet/GameplayStatics.h"

AVictoryVolume::AVictoryVolume()
{
	
	OnActorBeginOverlap.AddDynamic(this, &AVictoryVolume::OnOverlapBegin);
}

void AVictoryVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	if(HasAuthority())
	{
		if(OtherActor && (OtherActor != this))
		{
			if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(OtherActor))
			{
				if(ACGPlayerState* PlayerState = Cast<ACGPlayerState>(PlayerCharacter->GetPlayerState()))
				{
					if(ACGGameState* CGGameState = GetWorld()->GetGameState<ACGGameState>())
					{
					
						CGGameState->AddFinishedPlayer(PlayerState);
					}
					
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Blue, *FString::Printf(TEXT("PLAYER DETECTED WOOOO")));	
				}
				// if(ACGPlayerController* PlayerController = Cast<ACGPlayerController>(PlayerCharacter->GetController()))
				// {
				// }
			}
		}
	}
	
}

void AVictoryVolume::BeginPlay()
{
	Super::BeginPlay();
}
