// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

UCLASS()
class ACamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACamera();

protected:
	// Boolean to track whether right mouse is held
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ButtonTracking")
	bool RClick_Held;

	// Boolean to track whether middle mouse is held
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ButtonTracking")
	bool MClick_Held;

	// Float of the rotation around Y axis
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	float YRot_Value;

	// Float of the rotation around Z axis
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	float ZRot_Value;

	// Rotator of forward used for panning relevant to Z rotation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	FRotator ZForward;

	// Int value of forward axis
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	int32 Forward_Axis;

	// Int value of right axis
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	int32 Right_Axis;

	// Int value of rotation change
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rotations")
	int32 Rot_Change;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Poink and click functionality with mouse
	UFUNCTION(BlueprintCallable, Category = "Input")
	void PointAndClick(FHitResult& HitResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
