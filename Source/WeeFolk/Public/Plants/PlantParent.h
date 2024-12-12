// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
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

	//////////
	//GROWTH//
	//////////
	
	// Timer to increment to track growth cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Growth")
	float GrowthTimer{ 0.0 };

	// Length of a growth cycle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancing|Timers|Growth", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float GrowthCycleLength{ 10 };

	// Bool to track whether the plant has grown
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instancing|Timers|Growth")
	bool isFullyGrown{ false };

	// Non-blueprinted function to grow the plant
	void Growth();

	/////////
	//SCALE//
	/////////

	// Values to scale between at max growth
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Scale", meta = (ClampMin = "0.1", UIMin = "0.0"))
	FVector2f scaleBetween{ 1.0,1.0 };

	// Value chosen for scale
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Scale")
	float scaleMultiplier;

	// Bool to scale in only Z
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Scale")
	bool scaleOnlyInZ;

	// Float of current actor scale
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Scale")
	float currentScale{ 0 };

	/////////////
	//PLACEMENT//
	/////////////

	// Z rotation enabled boolean
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Placement")
	bool ZRotationEnabled{ true };

	// Z rotation generated
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instancing|Placement")
	float ZRotation;

	// Z offset of actor upon placement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Placement")
	float ZOffset{ 0 };

	// Tilt range on placement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Placement", meta = (ClampMin = "0.0", UIMin="0.0"))
	FVector2f tiltRange{ 0.0,0.0 };

	// Bool to inherit normal from landscape
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Placement")
	bool inheritUpFromLand{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Placement", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float lerpTowardsNormal{ 0.5 };

	void initPlacement();

	//////////
	//SPREAD//
	//////////

	// Number of cycles required before a plant can try to spread
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Spread")
	int32 MiniumCyclesPerSpread;

	// Radius to spread within
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Spread", meta = (ClampMin = "0", UIMin = "0"))
	FVector2f SpreadRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Spread", meta = (ClampMin = "0", ClampMax = "100", UIMin="0", UIMax="100"))
	int32 SpreadChance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancing|Timers|Spread")
	bool CanSpread;

	// Class to spawn on spread
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Timers|Spread")
	TSubclassOf<APlantParent> ClassToSpread;

	// Counter for number of cycles passed since last growth/spread
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Instancing|Timers|Spread")
	int32 CycleCounter;

	// Function to spread a plant to adjacent spaces
	virtual APlantParent* Spread();

	//////////
	//Visual//
	//////////

	// StaticMesh for the plant to use
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Visual Component")
	UStaticMeshComponent* VisualComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**Increments the timer tracking growth
	* @param DeltaTime The time passed since last incremented
	*/
	UFUNCTION(BlueprintCallable, Category = "Timers")
	void IncrementGrowthTimer(const float DeltaTime);

	// Boolean function to check whether the plant shoudl be grown
	bool ShouldGrow();
};
