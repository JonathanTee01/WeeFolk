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
	
	TArray<AActor*> plants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantParent::StaticClass(), plants);

	if (plants.Num() > 0) 
	{
		for (int i = 0; i < plants.Num(); i++)
		{
			if (plants[i] != nullptr)
				AddToManager(plants[i], plants[i]->GetActorLocation());
		}
	}
}

// Called every frame
void APlantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to validate and add newly spawned actors
bool APlantManager::AddToManager(AActor* actorToAdd, FVector position)
{
	FVector2f pos = { (float)position.X, (float)position.Y };
	pos = (pos / PlotSize).RoundToVector();

	if (EntityGrid.FindOrAdd(pos).containedEntities.FindOrAdd(actorToAdd->GetClass()->GetName()).Num() >= SpreadingMax[actorToAdd->GetClass()])
	{
		actorToAdd->Destroy();
		return false;
	}

	EntityGrid[pos].containedEntities[actorToAdd->GetClass()->GetName()].Add(actorToAdd);
	return true;
}
