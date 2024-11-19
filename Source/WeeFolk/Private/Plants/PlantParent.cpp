// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/PlantParent.h"

// Sets default values
APlantParent::APlantParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Default Mesh"));

	if (VisualComponent)
	{
		SetRootComponent(VisualComponent);
	}

	
}

// Called when the game starts or when spawned
void APlantParent::BeginPlay()
{
	Super::BeginPlay();

	// Generate randome scale based on planet
	scaleMultiplier = FMath::FRandRange(scaleBetween.X, scaleBetween.Y);

	// TODO: IF SET INHERIT UP FROM LAND NORMAL
	FHitResult Hit;

	// Apply the Z offset
	VisualComponent->AddRelativeLocation({ 0.0, 0.0, ZOffset });

	// Get the current default rotator
	FRotator rotator = VisualComponent->K2_GetComponentRotation();

	// Get a random tilt within range
	float randomTilt = FMath::FRandRange(tiltRange.X, tiltRange.Y);
	rotator.Pitch += randomTilt;

	// If enabled find a Z rotation and apply it
	if (ZRotationEnabled)
	{
		ZRotation = FMath::FRandRange(0.0, 360.0);

		// Increase and apply the new yaw
		rotator.Yaw += ZRotation;
	}

	// Apply tilt and z rotation
	VisualComponent->SetRelativeRotation(rotator);
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
	if (!isFullyGrown)
	{
		currentScale += (deltaTime / GrowthCycleLength) * scaleMultiplier;

		if (!scaleOnlyInZ) 
		{
			VisualComponent->SetRelativeScale3D(FVector(currentScale, currentScale, currentScale));
		}
		else
		{
			VisualComponent->SetRelativeScale3D(FVector(scaleMultiplier, scaleMultiplier, currentScale));
		}
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
	isFullyGrown = true;

	// TODO : Add if for spreading
}

void APlantParent::Spread()
{
}
