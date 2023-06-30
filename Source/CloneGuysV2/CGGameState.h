// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CGGameState.generated.h"

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
	void AddFinishedPlayer(ACloneGuysV2Character* PlayerCharacter);
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
	void DisplayMatchEnd(const FString& Winner);
	UFUNCTION(Reliable, NetMulticast)
	void MultiDisplayMatchEnd(const FString& Winner);
	
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle GameTimerHandle;
	
	UPROPERTY(BlueprintReadOnly)
	int32 MaxGameTime = 180;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_RoundSeconds)
	int32 CurrentGameSeconds = 180;
	UPROPERTY()
	bool bIsTimeOver = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)	
	TArray<ACloneGuysV2Character*> FinishedPlayers;
	
};
