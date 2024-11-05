// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantParent.generated.h"

UCLASS()
class WEEFOLK_API APlantParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Timer to increment to track growth cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	float GrowthTimer;

	// Length of a growth cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	float GrowthCycleLength;

	// Bool to track whether the plant has grown
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	bool isFullyGrown;

	// Number of cycles required before a plant can try to spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	int32 MiniumCyclesPerSpread;

	// Bool to track growth of plant
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	bool isGrown = false;

	// Float of current actor scale
	float currentScale = 0;

	// Counter for number of cycles passed since last growth/spread
	int32 cycleCounter;

	// Non-blueprinted function to grow the plant
	void Growth();

	// Function to spread a plant to adjacent spaces
	virtual void Spread();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// StaticMesh for the plant to use
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Visual Component")
	UStaticMeshComponent* VisualComponent;

	/**Increments the timer tracking growth
	* @param DeltaTime The time passed since last incremented
	* @param timer The GrowthTimer's value after being updated
	*/
	UFUNCTION(BlueprintCallable, Category = "Timers")
	void IncrementGrowthTimer(const float DeltaTime, float& timer);
};
