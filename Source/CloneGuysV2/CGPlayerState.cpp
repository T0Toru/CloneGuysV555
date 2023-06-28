// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerState.h"

ACGPlayerState::ACGPlayerState()
{
}

void ACGPlayerState::SetPlayerScore(float NewPlayerScore)
{
	CurrentPlayerScore = NewPlayerScore;
}

float ACGPlayerState::GetPlayerScore()
{
	return CurrentPlayerScore;
}
