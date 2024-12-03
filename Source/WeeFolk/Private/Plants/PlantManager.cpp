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
	
}

// Called every frame
void APlantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

