// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/Camera.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACamera::PointAndClick(FHitResult& HitResult)
{
	// Variables
	FHitResult HitResult(ForceInit);
	FVector2D mousePos = FVector2D(0, 0);
	FVector worldPos = FVector(mousePos.X, mousePos.Y, 0);
	FVector dir = FVector(0, 0, 0);

	/** Set Variables to Positions **/
	GetMousePosition(mousePos.X, mousePos.Y);
	DeprojectMousePositionToWorld(worldPos, dir);

	FVector Start = worldPos;
	FVector End = Start + dir * 10000;

	/** Init Trace Params **/
	FCollisionQueryParams TraceParams(FName(TEXT("TestTrace")), true, GetPawn());
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

