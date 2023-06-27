// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "VictoryVolume.generated.h"

/**
 * 
 */
UCLASS()
class CLONEGUYSV2_API AVictoryVolume : public ATriggerBox
{
	GENERATED_BODY()

public:
	AVictoryVolume();
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	// UFUNCTION()
	// void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;
	
};
