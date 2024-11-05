// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/PlantParent.h"

// Sets default values
APlantParent::APlantParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlantParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantParent::IncrementGrowthTimer(const float deltaTime, float& timer)
{
	// Incremtent the timer and output new value
	GrowthTimer += deltaTime;
	timer = GrowthTimer;

	// If not fully grown
	if (!isGrown)
	{
		currentScale += deltaTime / GrowthCycleLength;
		VisualComponent->SetWorldScale3D(FVector(currentScale, currentScale, currentScale));
	}

	// If due growth grow
	if (GrowthTimer >= GrowthCycleLength)
		Growth();
}

void APlantParent::Growth()
{
	// TODO : Add if for using soil quality

	// Reduce the growth timer and increment the number of cycles
	GrowthTimer -= GrowthCycleLength;
	cycleCounter++;

	// Set isGrown to be true
	isGrown = true;

	// TODO : Add if for spreading
}

void APlantParent::Spread()
{
}
