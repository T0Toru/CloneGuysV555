// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameMode.h"

#include "CGGameState.h"
#include "CGPlayerController.h"
#include "CGPlayerState.h"
#include "CloneGuysV2Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	StartGame();
	
}

void ACGGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
}

void ACGGameMode::StartGame()
{
	if(HasGameStarted())
		return;

	SetGamePhase(ECurrentGamePhase::PreGame);
	
}

void ACGGameMode::OnGamePhaseSet()
{
	if(CurrentGamePhase == ECurrentGamePhase::PreGame)
	{
		GetWorldTimerManager().SetTimer(WaitForGameStartTimerHandle, this, &ACGGameMode::StartPlayTime, 5.0f,false, 3.0f);
		if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
		{
			for (FConstPlayerControllerIterator PControllerIterator = GetWorld()->GetPlayerControllerIterator(); PControllerIterator; PControllerIterator++ )
			{
				APlayerController* pController = PControllerIterator->Get();
				if(pController && (pController->GetPawn() != nullptr))
				{
					if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(pController->GetPawn()))
					{
						PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
					}
				}
			}
		}
	}
	else if(CurrentGamePhase == ECurrentGamePhase::OngoingGame)
	{
		if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
		{
			for (FConstPlayerControllerIterator PControllerIterator = GetWorld()->GetPlayerControllerIterator(); PControllerIterator; PControllerIterator++ )
			{
				APlayerController* pController = PControllerIterator->Get();
				if(pController && (pController->GetPawn() != nullptr))
				{
					if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(pController->GetPawn()))
					{
						PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
					}
				}
			}
			CGGameState->StartGameTimer();
		}
	}
	else if(CurrentGamePhase == ECurrentGamePhase::EndGame)
	{
		if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
		{
			for (FConstPlayerControllerIterator PControllerIterator = GetWorld()->GetPlayerControllerIterator(); PControllerIterator; PControllerIterator++ )
			{
				APlayerController* pController = PControllerIterator->Get();
				if(pController && (pController->GetPawn() != nullptr))
				{
					if(ACloneGuysV2Character* PlayerCharacter = Cast<ACloneGuysV2Character>(pController->GetPawn()))
					{
						PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
					}
				}
			}
		}
		FinishMatch();
	}
}

void ACGGameMode::SetGamePhase(ECurrentGamePhase GamePhase)
{
	CurrentGamePhase = GamePhase;
	OnGamePhaseSet();
}

bool ACGGameMode::HasGameStarted()
{
	return bHasGameStarted;
}

void ACGGameMode::StartPlayTime()
{
	GetWorldTimerManager().ClearTimer(WaitForGameStartTimerHandle);
	SetGamePhase(ECurrentGamePhase::OngoingGame);
}

void ACGGameMode::GetHighestScoringPlayer()
{
	if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
	{
		for (APlayerState * pState : CGGameState->PlayerArray)
		{
			if(ACGPlayerState* CGpState = Cast<ACGPlayerState>(pState))
			{
				if(CGpState->GetPlayerScore() > HighestScore)
				{
					HighestScore = CGpState->GetPlayerScore();
					WinnerPlayerState = CGpState;
				}
			}
		}
	}
}

void ACGGameMode::CheckForWinnerByScore()
{
	// if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
	// {
	// 	for (APlayerState * pState : CGGameState->PlayerArray)
	// 	{
	// 		if(ACGPlayerState* CGpState = Cast<ACGPlayerState>(pState))
	// 		{
	// 			if(CGpState->GetPlayerScore() > HighestScore)
	// 			{
	// 				HighestScore = CGpState->GetPlayerScore();
	// 				WinnerPlayerState = CGpState;
	// 			}
	// 		}
	// 	}
	// 	SetGamePhase(ECurrentGamePhase::EndGame);
	// }
	GetHighestScoringPlayer();
	SetGamePhase(ECurrentGamePhase::EndGame);
}

void ACGGameMode::CheckForWinnerByPosition()
{
	if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
	{
		if(!CGGameState->FinishedPlayers.IsEmpty())
		{
			if(CGGameState->PlayerArray.Num() == CGGameState->FinishedPlayers.Num())
			{
				WinnerPlayerState = CGGameState->FinishedPlayers[0];
				SetGamePhase(ECurrentGamePhase::EndGame);
			}
		}
	}
}


void ACGGameMode::FinishMatch()
{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Blue, *FString::Printf(TEXT("Finish match called!")));
		if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
		{
			//CGGameState->SetWinningPlayer(WinnerPlayerState);
			CGGameState->MultiDisplayMatchEnd(WinnerPlayerState);
		}
	
}
