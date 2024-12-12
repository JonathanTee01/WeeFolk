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
		VisualComponent->SetRelativeScale3D(FVector::Zero()); 
		SetRootComponent(VisualComponent); 
	}

}

// Called when the game starts or when spawned
void APlantParent::BeginPlay()
{
	Super::BeginPlay();

	initPlacement();
	
}

// Called every frame
void APlantParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlantParent::IncrementGrowthTimer(const float deltaTime)
{
	// Incremtent the timer and output new value
	GrowthTimer += deltaTime;

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

bool APlantParent::ShouldGrow()
{
	return (!isFullyGrown || CanSpread);
}

bool APlantParent::GetShouldSpread()
{
	return ShouldSpread;
}

void APlantParent::SetShouldSpread(bool val)
{
	ShouldSpread = val;
}

void APlantParent::Growth()
{
	// TODO : Add if for using soil quality

	// Reduce the growth timer and increment the number of cycles
	GrowthTimer -= GrowthCycleLength * FMath::FRandRange(0.8, 1.2);
	CycleCounter++;

	// Set isGrown to be true
	isFullyGrown = true;

	if (CycleCounter >= MiniumCyclesPerSpread)
	{
		if (FMath::RandRange(0, 100) < SpreadChance)
		{
			ShouldSpread = true;
			CycleCounter = 0;
		}
	}
}

APlantParent* APlantParent::Spread()
{
	// Create a 2D vector for the direction to spread in
	FVector spreadDirection{ FMath::FRandRange(-1.0,1.0), FMath::FRandRange(-1.0,1.0), 0.0f};
	spreadDirection.Normalize();

	// Raycast down to find a valid placement
	FHitResult HitResult;

	// Create positions to raycast along from a little above origin to a little below at a set radius away
	FVector DownVector = FVector::DownVector * 5000;
	FVector Start = GetActorLocation() + (FVector::UpVector * 1000) + (spreadDirection * (FMath::FRandRange(0.0, FMath::FRandRange(SpreadRadius.X, SpreadRadius.Y))));
	FVector End = Start + DownVector;

	// Cast a ray to check for spawn location
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams); 

	// From trace if viable create new plant of the given type
	if (!HitResult.GetActor()->ActorHasTag("Non-spreadable"))
	{
		FActorSpawnParameters SpawnInfo;
		FRotator myRot(0, 0, 0);
		FVector myLoc = HitResult.Location;

		ShouldSpread = false;

		return GetWorld()->SpawnActor<APlantParent>(ClassToSpread, myLoc, myRot, SpawnInfo);
	}

	// TODO : Make condition more complex for not spreading
	ShouldSpread = false;
	return nullptr;
}


void APlantParent::initPlacement() 
{
	// Generate randome scale based on planet
	scaleMultiplier = FMath::FRandRange(scaleBetween.X, scaleBetween.Y);

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

	if (inheritUpFromLand)
	{
		FHitResult HitResult;

		// Create positions to raycast along from a little above origin to a little below
		FVector DownVector = FVector::DownVector * 1000;
		FVector Start = GetActorLocation() + (FVector::UpVector * 500);
		FVector End = Start + DownVector;

		// Ignore this actor in raycast
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

		// Get vector between normal and up. This is what we rotate with
		FVector LandNormal = (HitResult.ImpactNormal * lerpTowardsNormal) + (FVector::UpVector * (1 - lerpTowardsNormal));
		LandNormal.Normalize();

		// Make a rotator from normal and right vector
		FRotator LandNormalRotation = FRotationMatrix::MakeFromZY(LandNormal, FVector::RightVector).Rotator();

		// Set world rotation
		VisualComponent->AddWorldRotation(LandNormalRotation);
	}
}