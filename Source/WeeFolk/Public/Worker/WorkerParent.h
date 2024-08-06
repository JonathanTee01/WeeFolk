// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkerParent.generated.h"

UCLASS()
class WEEFOLK_API AWorkerParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkerParent();

	// Boolean value of whether the worker is currently unassigned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Assignment")
	bool isIdle;

	/** Finds a workplace for the worker is they are unassigned
	* @param FoundWorkplace A reference to the workplace they find and are assigned to
	*/
	UFUNCTION(BlueprintCallable, Category="Assignment")
	void FindWork(AActor*& FoundWorkplace);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
