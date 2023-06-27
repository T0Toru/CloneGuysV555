// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameState.h"

#include "CGGameMode.h"
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

void ACGGameState::AddFinishedPlayer(ACloneGuysV2Character* PlayerCharacter)
{
	FinishedPlayers.AddUnique(PlayerCharacter);
	if(ACGGameMode* CGGameMode = Cast<ACGGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		CGGameMode->CheckForWinner();
	}
}


