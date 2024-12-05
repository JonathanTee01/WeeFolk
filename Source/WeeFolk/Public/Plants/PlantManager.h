// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantParent.h"
#include "PlantManager.generated.h"

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

public:	
	///////////
	//Sorting//
	///////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Instancing|Limits", meta = (ClampMin = "100", UIMin = "100"))
	int32 PlotSize = 100;

	////////////
	//Spawning//
	////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancing|Limits")
	TMap< TSubclassOf<APlantParent>, int32 > SpreadingMax;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
