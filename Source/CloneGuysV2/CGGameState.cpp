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
	DOREPLIFETIME(ACGGameState, CurrentGameSeconds);
}

void ACGGameState::StartGameTimer()
{
	if(CurrentGameSeconds > 0)
	{
		GetWorldTimerManager().ClearTimer(GameTimerHandle);
		GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ACGGameState::TimerCountdown, 1.0f, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(GameTimerHandle);
	}
	if(HasAuthority())
	{
		StartGameTimerMulti();
	}
}

void ACGGameState::StartGameTimerMulti_Implementation()
{
	if(!HasAuthority())
	{
		StartGameTimer();
	}
}

void ACGGameState::OnRep_RoundSeconds()
{
	StartGameTimer();
}

void ACGGameState::TimerCountdown()
{
	if(CurrentGameSeconds > 0)
	{
		CurrentGameSeconds -= 1;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Yellow, *FString::Printf(TEXT("Current Round Time: %d"), CurrentGameSeconds));
	}
	else
	{
		if(HasAuthority())
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, *FString::Printf(TEXT("TIME'S UP!")));
		}
	}
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


