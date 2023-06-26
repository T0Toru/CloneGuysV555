// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelObstacle.generated.h"

UCLASS()
class CLONEGUYSV2_API ALevelObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelObstacle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotating Movement")
	class URotatingMovementComponent* RotatingMovementComponent; 


};
