// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// setup vr origin component
	VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));

	// Setup camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	

	// create a visible representation of hands
	HandMesh_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandLeft"));
	HandMesh_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandRight"));

	// create motion controllers and assign hands
	MotionController_L = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerL"));
	MotionController_R = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerR"));
	MotionController_L->Hand_DEPRECATED = EControllerHand::Left;
	MotionController_R->Hand_DEPRECATED = EControllerHand::Right;


	// attatchment heiararchy 
	VROriginComp->AttachTo(RootComponent);
	Camera->SetupAttachment(VROriginComp);
	MotionController_L->AttachTo(VROriginComp);
	MotionController_R->AttachTo(VROriginComp);
	HandMesh_L->AttachTo(MotionController_L);
	HandMesh_R->AttachTo(MotionController_R);
	
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forwards", this, &AVRCharacter::Move_Forwards);
	PlayerInputComponent->BindAxis("Strafe", this, &AVRCharacter::Strafe);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVRCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AVRCharacter::JumpStop);
	
}

void AVRCharacter::Move_Forwards(float AxisValue) 
{
	float ForwardsSpeed = 100;
	FVector camDir(Camera->GetForwardVector());
	camDir.Z = 0;
	camDir.Normalize();
	AddMovementInput(camDir, AxisValue * ForwardsSpeed);
}

void AVRCharacter::Strafe(float AxisValue)
{
	float StrafeSpeed = 100;
	FVector camDir(Camera->GetRightVector());
	camDir.Z = 0;
	camDir.Normalize();
	AddMovementInput(camDir, AxisValue*StrafeSpeed);
}

void AVRCharacter::JumpStart()
{
	bPressedJump = true;
}

void AVRCharacter::JumpStop()
{
	bPressedJump = false;
}