// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLONEGUYSV2_API ACGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACGPlayerController();
	virtual void BeginPlay() override;
	void CreateHUD();
	void CreateScoreTab();
	virtual void OnRep_PlayerState() override;

	void ToggleScoreTab();
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UCGUWGameHUD> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UCGUWGameHUD* UIHUDWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UCGWidget> ScoreWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UCGWidget* ScoreWidget;
	
};
