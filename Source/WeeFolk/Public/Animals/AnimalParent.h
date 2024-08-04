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

	// How long a feeding cycle lasts
	// If it hasn't eaten it will try to find food within this cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	float FeedingCycleLength;

	// Timer for how long the cycle has lasted so far
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	float CycleTimer;

	// Has the animal eaten this cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	bool HasFed;

	// Current satiety level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 SatietyLevel;

	// Satiety threshold to start hunting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Food")
	int32 DesiredSatiety;

	// Current texture for the sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	UTexture2D* CurrentTexture;

	// List of possible idle textures
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> IdleTextures;

	// List of possible textures for moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> MovingTextures;

	// List of textures for eating
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TArray<UTexture2D*> EatingTextures;

	/** Function to find and pathfind to food
	* @param FoundFood Bool output as to whether food was found
	*/
	UFUNCTION(BlueprintCallable, Category = "Food")
	virtual void FindFood(bool& FoundFood);

	// Function to eat found food
	void Eat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Satiety given when eaten by another
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 SatietyWhenEaten;
};
