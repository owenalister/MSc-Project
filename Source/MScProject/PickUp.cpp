// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"


// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->AttachTo(mesh);
	CollisionSphere->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->SetGenerateOverlapEvents(true); CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnSphereBeginOverlap);
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FQuat(FRotator(6, 0, 0)), false, 0, ETeleportType::None);
}

void APickUp::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}