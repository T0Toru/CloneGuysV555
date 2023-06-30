// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerController.h"

#include <thread>

#include "CGPlayerState.h"
#include "CGUWGameHUD.h"

ACGPlayerController::ACGPlayerController()
{
}

void ACGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
		CreateHUD();
}

void ACGPlayerController::CreateHUD()
{
	if(UIHUDWidget)
		return;

	if(!UIHUDWidgetClass)
		return;

	if(!IsLocalPlayerController())
		return;
	
	ACGPlayerState* CGPState = GetPlayerState<ACGPlayerState>(); //In case we need something frofm the player state.
	if(!CGPState)
		return;

	if(UIHUDWidgetClass)
	{
		UIHUDWidget = CreateWidget<UCGUWGameHUD>(this, UIHUDWidgetClass);
		UIHUDWidget->AddToViewport();
	}
}

void ACGPlayerController::CreateScoreTab()
{
}

void ACGPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(PlayerState)
	{
		CreateHUD();
	}
}

void ACGPlayerController::ToggleScoreTab()
{
	if (!IsValid(ScoreWidget) || ScoreWidget->GetName() == "None")
	{
		if(ScoreWidgetClass)
		{
			ScoreWidget = CreateWidget<UCGWidget>(this, ScoreWidgetClass);
			ScoreWidget->AddToViewport();
			ScoreWidget->SetVisibility(ESlateVisibility::Visible);
			return;
		}
	}
	if (!IsValid(ScoreWidget) || ScoreWidget->GetName() == "None")
		return;
	
	if(IsValid(ScoreWidget)&& ScoreWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//ScoreWidget->AddToViewport();
		ScoreWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	if(IsValid(ScoreWidget)&& ScoreWidget->GetVisibility() != ESlateVisibility::Collapsed)
	{
		ScoreWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
