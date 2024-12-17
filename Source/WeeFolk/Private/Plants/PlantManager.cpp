// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/PlantManager.h"

// Sets default values
APlantManager::APlantManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlantManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the already existing plants
	// THIS IS FOR DEBUG AND CAN BE DELETED
	TArray<AActor*> plants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantParent::StaticClass(), plants);

	// Find all plants present on start-up
	for (int i = 0; i < plants.Num(); i++)
	{
		if (plants[i] != nullptr)
			AddToManager((APlantParent*)plants[i]);
	}
}

// Function to increment plant timers
bool APlantManager::IncrementTimers(const float deltaTime)
{
	for (auto& Box : EntityGrid)
	{
		for (auto& Entities : Box.Value.containedEntities)
		{
			for (int i = 0; i < Entities.Value.Num(); i++)
			{
				if (Entities.Value[i]->ShouldGrow())
				{
					Entities.Value[i]->IncrementGrowthTimer(deltaTime);
					if (Entities.Value[i]->GetShouldSpread())
						if (AddToManager(Entities.Value[i]->Spread()))
							Entities.Value[i]->SetShouldSpread(false);
				}
			}
		}
	}
	return false;
}

// Called every frame
void APlantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to validate and add newly spawned actors
bool APlantManager::AddToManager(APlantParent* actorToAdd)
{
	if (actorToAdd == nullptr)
		return false;

	// Get actors location in world space
	FVector actorPos = actorToAdd->GetActorLocation();

	// Turn pos into correct format for key values
	FVector2f gridPos = { (float)actorPos.X, (float)actorPos.Y };
	gridPos = (gridPos / PlotSize).RoundToVector();

	EntityGrid.FindOrAdd(gridPos);
	EntityGrid.FindOrAdd(gridPos).containedEntities.FindOrAdd(actorToAdd->GetClass()->GetName());

	// Create the maps if needed and verify whether the new actor would exceed set limits within the grid space
	if (EntityGrid.FindOrAdd(gridPos).containedEntities.FindOrAdd(actorToAdd->GetClass()->GetName()).Num() >= SpreadingMax.FindOrAdd(actorToAdd->GetClass()))
	{
		actorToAdd->Destroy();
		return false;
	}

	// If the actor would not exceed limits then store a reference
	EntityGrid[gridPos].containedEntities[actorToAdd->GetClass()->GetName()].Add(actorToAdd);
	return true;
}
