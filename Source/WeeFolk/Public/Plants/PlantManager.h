// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantParent.h"
#include "PlantManager.generated.h"

USTRUCT(BlueprintType)
struct FGridBox
{
	GENERATED_USTRUCT_BODY()

	TMap< TSubclassOf<APlantParent>, TArray< TSubclassOf<APlantParent>* > > containedEntities; 
};

UCLASS()
class WEEFOLK_API APlantManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Map storing each grid box of entities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instancing")
	TMap<FVector2f, FGridBox> EntityGrid;

public:	
	///////////
	//Sorting//
	///////////

	// Size of each grid box
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Limits", meta = (ClampMin = "100", UIMin = "100"))
	int32 PlotSize = 500;

	////////////
	//Spawning//
	////////////

	// Max number of entity type allowed in each grid box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancing|Limits")
	TMap< TSubclassOf<APlantParent>, int32 > SpreadingMax;

	// Function to validate and add newly spawned actors
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	bool AddToManager(AActor* actorToAdd, FVector2f position);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
