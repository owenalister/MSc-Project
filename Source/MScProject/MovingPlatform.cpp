// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create subobjects
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	start = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("start"));
	end = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("end"));
	root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("root"));

	//set heiararchy
	mesh->SetupAttachment(root);
	start->SetupAttachment(root);
	end->SetupAttachment(root);


	amplitude = 200;
	frequency = 1;
	horizontal = true;


}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	RunningTime = 0;

	FVector newLocation = GetActorLocation();
	if (horizontal)
	{
		newLocation.X += amplitude * GetActorForwardVector().X;
		newLocation.Y += amplitude * GetActorForwardVector().Y;
	}
	else
	{
		newLocation.Z += amplitude;
	}
	SetActorLocation(newLocation);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	FVector newLocation = GetActorLocation();
	Super::Tick(DeltaTime);
	float offset = DeltaTime * frequency;
	if (horizontal)
	{
		
		newLocation.X += (amplitude * (FMath::Sin(RunningTime + offset) - FMath::Sin(RunningTime))) * GetActorForwardVector().X;
		newLocation.Y += (amplitude * (FMath::Sin(RunningTime + offset) - FMath::Sin(RunningTime))) * GetActorForwardVector().Y;
	}
	else 
	{
		newLocation.Z += (amplitude * (FMath::Sin(RunningTime + offset) - FMath::Sin(RunningTime))) ;
	}
	
	RunningTime += DeltaTime;
	SetActorLocation(newLocation);
}

