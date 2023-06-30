// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameMode.h"

#include "CGGameState.h"
#include "CloneGuysV2Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();

	//SetMatchState(CurrentMatchState::PreGame);
	//GetWorldTimerManager().SetTimer(WaitForGameStartTimerHandle, this, &ACGGameMode::StartPlayTime, 5.0f,false, 3.0f);
	
}

void ACGGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	//Hacky way of starting the match
	// if(HasAuthority())
	// {
	// 	if(!HasMatchStarted())
	// 	{
	// 		StartMatch();
	// 	}
	// }
}

void ACGGameMode::StartMatch()
{
	Super::StartMatch();
	 if(HasMatchStarted())
	 	return;

	SetMatchState(CurrentMatchState::PreGame);
}

void ACGGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();
	if(MatchState == CurrentMatchState::PreGame)
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
						//PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
					}
				}
			}
		}
	}
	else if(MatchState == CurrentMatchState::OngoingGame)
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
	else if(MatchState == CurrentMatchState::EndGame)
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

void ACGGameMode::SetMatchState(FName NewState)
{
	Super::SetMatchState(NewState);
}

void ACGGameMode::StartPlayTime()
{
	GetWorldTimerManager().ClearTimer(WaitForGameStartTimerHandle);
	SetMatchState(CurrentMatchState::OngoingGame);
}

void ACGGameMode::CheckForWinner()
{
	if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
	{
		if(!CGGameState->FinishedPlayers.IsEmpty())
		{
			if(CGGameState->PlayerArray.Num() == CGGameState->FinishedPlayers.Num())
			{
				float Pos = 1.0f;
				for (ACloneGuysV2Character* Player : CGGameState->FinishedPlayers)
				{
					UE_LOG(LogTemp, Warning, TEXT("Player %s, finished in position %f"), *Player->GetName(), Pos);
					Pos++;
				}
				FinishMatch();
			}
		}
	}
	
	// if(!FinishedPlayers.IsEmpty())
	// {
	// 	if(ACGGameState* CGGameState = Cast<ACGGameState>(GameState))
	// 	{
	// 		if(CGGameState->PlayerArray.Num() == FinishedPlayers.Num())
	// 		{
	// 			for (ACloneGuysV2Character* Player : FinishedPlayers )
	// 			{
	// 				float Pos = 0;
	// 				UE_LOG(LogTemp, Warning, TEXT("Player %s, finished in position %f"), *Player->GetName(), Pos);
	// 				Pos++;
	// 			}
	// 			FinishMatch();
	// 		}
	// 	}
	// }
}

void ACGGameMode::FinishMatch()
{
	if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Blue, *FString::Printf(TEXT("Finish match called!")));
	}
}
