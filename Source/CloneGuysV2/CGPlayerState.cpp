// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerState.h"

#include "CloneGuysV2Character.h"
#include "Net/UnrealNetwork.h"

ACGPlayerState::ACGPlayerState()
{
}

void ACGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACGPlayerState, CurrentPlayerScore);
	DOREPLIFETIME_CONDITION_NOTIFY(ACGPlayerState, GivenPlayerName, COND_None, REPNOTIFY_Always);
}

void ACGPlayerState::SetPlayerScore(float NewPlayerScore)
{
	CurrentPlayerScore = NewPlayerScore;
}

float ACGPlayerState::GetPlayerScore()
{
	return CurrentPlayerScore;
}

void ACGPlayerState::OnRep_PlayerCurrentName()
{
	if(GetPawn())
	{
		if(ACloneGuysV2Character* CloneGuysV2Character = Cast<ACloneGuysV2Character>(GetPawn()))
		{
			if(UTextRenderComponent* TRenderer = CloneGuysV2Character->FindComponentByClass<UTextRenderComponent>())
			{
			TRenderer->SetHiddenInGame(false);
			TRenderer->SetText(GivenPlayerName);
			}
			
		}
	}
}
