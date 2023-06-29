// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CGGameMode.generated.h"
class ACGPlayerState;
class ACloneGuysV2Character;

namespace CurrentMatchState
{
	const FName PreGame = FName(TEXT("PreGame"));
	const FName OngoingGame = FName(TEXT("OngoingGame"));
	const FName EndGame = FName(TEXT("EndGame"));
}

/**
 * 
 */
UCLASS()
class CLONEGUYSV2_API ACGGameMode : public AGameMode
{
	GENERATED_BODY()

//Remember the game mode only runs on the server
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

	virtual void StartMatch() override;
	virtual void OnMatchStateSet() override;
	virtual void SetMatchState(FName NewState) override;

	void StartPlayTime();
	
	UFUNCTION(BlueprintCallable)
	void CheckForWinner();
	UFUNCTION(BlueprintCallable)
	void FinishMatch();

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle WaitForGameStartTimerHandle;

	ACGPlayerState* WinnerState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxNumPlayers = 3;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TArray<ACloneGuysV2Character*> FinishedPlayers;
	
	
};
