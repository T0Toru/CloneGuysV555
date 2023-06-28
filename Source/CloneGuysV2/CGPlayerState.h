// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CLONEGUYSV2_API ACGPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	ACGPlayerState();
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 CurrentPlayerScore;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 PlayerFinishPosition;

	void SetPlayerScore(float NewPlayerScore);
	float GetPlayerScore();
	
	
};
