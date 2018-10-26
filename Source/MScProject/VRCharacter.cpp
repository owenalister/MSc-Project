// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// setup vr origin component
	VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));


	//setup cameraoffset
	CameraOffset = CreateDefaultSubobject<USceneComponent>(TEXT("CameraOffset"));

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
	CameraOffset->AttachTo(VROriginComp);
	Camera->SetupAttachment(CameraOffset);
	MotionController_L->AttachTo(VROriginComp);
	MotionController_R->AttachTo(VROriginComp);
	HandMesh_L->AttachTo(MotionController_L);
	HandMesh_R->AttachTo(MotionController_R);
	
	// initialize variables
	movementInput = FVector(0,0,0);
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
	
	// get motion controller rotation
	FRotator controllerYaw =  FRotator(0, MotionController_L->GetComponentRotation().Yaw - 90.0f, 0);
	GetMesh()->SetWorldRotation(controllerYaw);
	FVector dir = MotionController_L->GetForwardVector();
			
	//AddMovementInput(dir.RotateAngleAxis(MotionController_L->GetComponentRotation().Yaw, FVector(0, 0, 1)));
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
	
	
	
	FVector camDir(MotionController_L->GetForwardVector());
	camDir.Z = 0;
	camDir.Normalize();
	FRotator rot(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector fwd = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
	//AddMovementInput(fwd, AxisValue * ForwardsSpeed);
//	movementInput.X = AxisValue;
	AddMovementInput(camDir, AxisValue * ForwardsSpeed);

	camDir=MotionController_L->GetRightVector();
	camDir.Z = 0;
	camDir.Normalize();
	
	fwd = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
	//AddMovementInput(fwd, AxisValue * ForwardsSpeed);
//	movementInput.X = AxisValue;
	AddMovementInput(camDir, InputComponent->GetAxisValue(TEXT("Strafe")) * ForwardsSpeed);

	movementInput.X = AxisValue;
	movementInput.Y = InputComponent->GetAxisValue(TEXT("Strafe"));
}

void AVRCharacter::Strafe(float AxisValue)
{	
	//float StrafeSpeed = 100;
	//movementInput->Y = AxisValue * StrafeSpeed;
	/*
	
	FVector camDir(Camera->GetRightVector());
	camDir = MotionController_R->GetForwardVector();
	camDir.Z = 0;
	camDir.Normalize();
	FRotator rot(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector fwd = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
	//AddMovementInput(fwd, AxisValue * StrafeSpeed);
	
	AddMovementInput(camDir, AxisValue*StrafeSpeed);*/
}

void AVRCharacter::JumpStart()
{
	bPressedJump = true;
}

void AVRCharacter::JumpStop()
{
	bPressedJump = false;
}