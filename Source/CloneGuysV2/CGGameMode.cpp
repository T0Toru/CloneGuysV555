// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameMode.h"

#include "CGGameState.h"
#include "CloneGuysV2Character.h"

void ACGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();
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
