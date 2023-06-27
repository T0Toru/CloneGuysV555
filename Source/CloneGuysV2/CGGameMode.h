// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CGGameMode.generated.h"
class ACGPlayerState;
class ACloneGuysV2Character;

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

	UFUNCTION(BlueprintCallable)
	void CheckForWinner();
	UFUNCTION(BlueprintCallable)
	void FinishMatch();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxNumPlayers = 3;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TArray<ACloneGuysV2Character*> FinishedPlayers;
	
	
};
