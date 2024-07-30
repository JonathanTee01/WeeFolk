// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantParent.generated.h"

class WEEFOLK_API AEater
{
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 RequiredSoilLevel;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	int32 SatietyWhenEaten;
};


UCLASS()
class WEEFOLK_API APlantParent : public AActor, public AEater
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	float GrowthTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	float GrowthCycleLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
	bool isFullyGrown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	int32 MiniumCyclesPerSpread;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
	int32 PointsAwardedPerGrowth;

	int32 cycleCounter;

	// Functions
	void Growth();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	UStaticMesh* VisualComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic")
	FString Name;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Timers")
	void IncrementGrowthTimer(const float DeltaTime, float& timer);
};
