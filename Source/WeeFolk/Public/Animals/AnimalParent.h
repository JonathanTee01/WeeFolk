// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimalParent.generated.h"

UCLASS()
class WEEFOLK_API AAnimalParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	float FeedingCycleLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	float CycleTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	bool HasFed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 SatietyValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	UTexture2D* CurrentTexture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> IdleTextures;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> MovingTextures;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> EatingTextures;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Food")
	virtual void FindFood(bool& FoundFood);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 SatietyWhenEaten;
};
