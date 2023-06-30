// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CGGameState.generated.h"

class ACGPlayerState;
class ACGPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWinnerSet, ACGPlayerState*, WinningPlayer);

/**
 * 
 */
UCLASS()
class CLONEGUYSV2_API ACGGameState : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void AddPlayerScore(int32 PlayerId, int32 PlayerScore);

	UFUNCTION()
	void AddFinishedPlayer(ACGPlayerState* FinishedPlayerState);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void StartGameTimer();
	UFUNCTION(Reliable,NetMulticast)
	void StartGameTimerMulti();
	UFUNCTION()
	void OnRep_RoundSeconds();
	UFUNCTION()
	void TimerCountdown();
	UFUNCTION()
	bool IsMatchTimeOver(){return bIsTimeOver;}

	UFUNCTION()
	void DisplayMatchEnd(ACGPlayerState* WinnerPlayerState);
	UFUNCTION(Reliable, NetMulticast)
	void MultiDisplayMatchEnd(ACGPlayerState* WinnerPlayerState);
	void SetWinningPlayer(ACGPlayerState* WinningPlayerState);
	void GetHighestScoringPlayer();
	
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle GameTimerHandle;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_RoundSeconds)
	int32 CurrentGameSeconds = 180;
	UPROPERTY()
	bool bIsTimeOver = false;
	UPROPERTY(BlueprintReadOnly, Replicated)	
	TArray<ACGPlayerState*> FinishedPlayers;
	UPROPERTY(BlueprintAssignable)
	FOnWinnerSet WinnerSetDelegate;
	UPROPERTY(BlueprintReadOnly, Replicated)	
	ACGPlayerState* WinningPlayer;
	
};
