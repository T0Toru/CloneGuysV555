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
	void CreateMatchEndScreen();
	virtual void OnRep_PlayerState() override;


	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void ServerSetPlayerGivenName(const FText& NewName);
	
	//virtual void ServerChangeName_Implementation(const FString& S) override;

	void ToggleScoreTab();

	UPROPERTY()
	bool bIsScoreShown = false;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UCGUWGameHUD> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UCGUWGameHUD* UIHUDWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UCGWidget> ScoreWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UCGWidget* ScoreWidget;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UCGWidget> MatchEndWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class UCGWidget* MatchEndWidget;
	
};
