// Fill out your copyright notice in the Description page of Project Settings.


#include "Worker/WorkerParent.h"

// Sets default values
AWorkerParent::AWorkerParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWorkerParent::FindWork(AActor*& FoundWorkplace)
{
}

// Called when the game starts or when spawned
void AWorkerParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorkerParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

