// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameState.h"

#include "CGGameMode.h"
#include "CGPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void ACGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACGGameState, FinishedPlayers);
}

void ACGGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ACGGameState::AddPlayerScore_Implementation(int32 PlayerId, int32 PlayerScore)
{
	if(PlayerScore == 0)
	{
		return;
	}

	for(APlayerState * PlayerState : PlayerArray)
	{
		if(ACGPlayerState* CGPlayerState = Cast<ACGPlayerState>(PlayerState))
		{
			if(CGPlayerState->GetPlayerId() == PlayerId)
			{
				CGPlayerState->SetPlayerScore(CGPlayerState->GetPlayerScore() + PlayerScore);
			}

			UE_LOG(LogTemp, Warning, TEXT("Player %d current score is %f "), CGPlayerState->GetPlayerId(), CGPlayerState->GetPlayerScore());
			
		}

			
		// if(PlayerState->GetPlayerId() == PlayerId)
		// {
		// 	PlayerState->SetScore(PlayerState->GetScore() + PlayerScore);
		// }
		//
		// UE_LOG(LogTemp, Warning, TEXT("Player %d current score is %d "), PlayerId, PlayerState->GetScore());
		
	}
}

bool ACGGameState::AddPlayerScore_Validate(int32 PlayerId, int32 PlayerScore)
{
	return true;
}

void ACGGameState::AddFinishedPlayer(ACloneGuysV2Character* PlayerCharacter)
{
	FinishedPlayers.AddUnique(PlayerCharacter);
	if(ACGGameMode* CGGameMode = Cast<ACGGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		CGGameMode->CheckForWinner();
	}
}


