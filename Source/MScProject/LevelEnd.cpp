// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelEnd.h"


// Sets default values
ALevelEnd::ALevelEnd()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	completionTime = 0;
	healthLost = 0;
	deathCount = 0;
	timerActive = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::OnMeshBeginOverlap);
	isEnded = false;
}

// Called when the game starts or when spawned
void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (timerActive)
		completionTime += DeltaTime;
}

void ALevelEnd::TimerStart()
{
	timerActive = true;
}

void ALevelEnd::LevelComplete()
{
	if (isEnded == false)
	{
		timerActive = false;
		AVRCharacter* playerRef = Cast<AVRCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		const char *path = "/gameplayResults.txt";
		std::ofstream txtfile(path);
		txtfile << "Completion time:" << completionTime << "\n";
		txtfile << "Health lost: " << playerRef->totalHealthLost << "\n";
		txtfile << "Death count: " << playerRef->deathCount << "\n";
		txtfile << "Fall count: " << playerRef->fallCount << "\n";
		txtfile.close();
	}
}

void ALevelEnd::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LevelComplete();
}