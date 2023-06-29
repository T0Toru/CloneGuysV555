// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerState.h"

#include "Net/UnrealNetwork.h"

ACGPlayerState::ACGPlayerState()
{
}

void ACGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACGPlayerState, CurrentPlayerScore);
}

void ACGPlayerState::SetPlayerScore(float NewPlayerScore)
{
	CurrentPlayerScore = NewPlayerScore;
}

float ACGPlayerState::GetPlayerScore()
{
	return CurrentPlayerScore;
}
