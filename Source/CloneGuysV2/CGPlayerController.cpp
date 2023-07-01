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

void ACGPlayerController::CreateMatchEndScreen()
{
	if (!IsValid(MatchEndWidget) || MatchEndWidget->GetName() == "None")
	{
		if(MatchEndWidgetClass)
		{

			UIHUDWidget->RemoveFromParent();
			
			MatchEndWidget = CreateWidget<UCGWidget>(this, MatchEndWidgetClass);
			MatchEndWidget->AddToViewport();
			MatchEndWidget->SetVisibility(ESlateVisibility::Visible);
	
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
		}
	}
}

void ACGPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(PlayerState)
	{
		CreateHUD();
	}
}

void ACGPlayerController::ServerSetPlayerGivenName_Implementation(const FText& NewName)
{
	if(ACGPlayerState* CGPState = GetPlayerState<ACGPlayerState>())
	{
		CGPState->GivenPlayerName;
		if(HasAuthority())
			CGPState->OnRep_PlayerCurrentName();
	}
}

bool ACGPlayerController::ServerSetPlayerGivenName_Validate(const FText& NewName)
{
	return true;
}

// void ACGPlayerController::ServerChangeName_Implementation(const FString& S)
// {
// 	Super::ServerChangeName_Implementation(S);
// }

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
	if (!IsValid(ScoreWidget) || ScoreWidget->GetName() == "None") //return if it becomes invalid for some reason
		return;
	
	if(IsValid(ScoreWidget)&& ScoreWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//ScoreWidget->AddToViewport();
		FInputModeGameAndUI InputMode;
		bShowMouseCursor = true;
		SetInputMode(InputMode);
		ScoreWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	if(IsValid(ScoreWidget)&& ScoreWidget->GetVisibility() != ESlateVisibility::Collapsed)
	{
		FInputModeGameOnly InputMode;
		bShowMouseCursor = false;
		SetInputMode(InputMode);
		ScoreWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
