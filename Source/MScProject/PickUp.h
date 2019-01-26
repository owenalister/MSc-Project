// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "PickUp.generated.h"

UCLASS()
class MSCPROJECT_API APickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent *CollisionSphere;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
