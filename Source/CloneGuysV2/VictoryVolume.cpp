// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryVolume.h"

#include "CGGameMode.h"
#include "CGGameState.h"
#include "CloneGuysV2Character.h"
#include "Chaos/GeometryParticlesfwd.h"
#include "Kismet/GameplayStatics.h"

AVictoryVolume::AVictoryVolume()
{
	
	OnActorBeginOverlap.AddDynamic(this, &AVictoryVolume::OnOverlapBegin);
}

void AVictoryVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor && (OtherActor != this))
	{
		if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(OtherActor))
		{
			if(ACGGameState* CGGameState = GetWorld()->GetGameState<ACGGameState>())
			{
				if(HasAuthority())
					CGGameState->AddFinishedPlayer(PlayerCharacter);
			}
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Blue, *FString::Printf(TEXT("PLAYER DETECTED WOOOO")));
		}
	}
}

void AVictoryVolume::BeginPlay()
{
	Super::BeginPlay();
}
