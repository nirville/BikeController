// Fill out your copyright notice in the Description page of Project Settings.


#include "Bike.h"
#include "BikeAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABike::ABike() :
	MaxSpeed(2000.0f),
	CurrentSpeed(0.0f),
	MaxSteeringAngle(45.f),
	CurrentSteeringAngle(0.0f),
	CurrentLeanAngle(0.0f),
	SpeedToRotationFactor(0.001f),
	ThrottleValue(0.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BikeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BikeMesh"));
	RootComponent = BikeMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	BikeEngineSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	BikeEngineSound->SetupAttachment(RootComponent);

	Speed = 10.0f;
	TurnSpeed = 100.0f;

	// Bind input functions
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set up bike physics
	BikeMesh->SetSimulatePhysics(true);
	BikeMesh->SetMassOverrideInKg(NAME_None, 500.0f, true);
	BikeMesh->SetLinearDamping(0.1f);
	BikeMesh->SetAngularDamping(0.1f);
}

// Called when the game starts or when spawned
void ABike::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(CurrentSpeed * GetActorForwardVector() * DeltaTime);
	
	float speedCheckYaw = CurrentSpeed * CurrentSteeringAngle * SpeedToRotationFactor * GetWorld()->GetDeltaSeconds();
	float CurrentValue = CurrentLeanAngle; 
	float TargetValue = (CurrentSpeed / MaxSpeed) * CurrentSteeringAngle;  

	// Perform interpolation and save the result in a variable
	float speedCheckRoll = FMath::FInterpTo(CurrentValue, TargetValue, GetWorld()->GetDeltaSeconds(), 0.0f);
	FRotator IncrementalRotation = FRotator(0.0f, GetActorRotation().Yaw + speedCheckYaw, speedCheckRoll);
	SetActorRelativeRotation(IncrementalRotation);
	CurrentLeanAngle = speedCheckRoll;

	EngineSound();
}

// Called to bind functionality to input
void ABike::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind functions to input events
	PlayerInputComponent->BindAxis("Throttle", this, &ABike::Throttle);
	PlayerInputComponent->BindAxis("Steer", this, &ABike::Steer);
}

float ABike::MyFloatSteering()
{
	// Usage of MapRangeClamped
	float OriginalValue = CurrentSpeed;  // The original value you want to map
	float OriginalMin = 0.0f;     // The minimum value of the original range
	float OriginalMax = MaxSpeed;    // The maximum value of the original range

	float NewMin = 1.0f;          // The minimum value of the target range
	float NewMax = 0.8f;          // The maximum value of the target range

	float MappedValue = FMath::GetMappedRangeValueClamped(
		FVector2D(OriginalMin, OriginalMax), 
		FVector2D(NewMin, NewMax), 
		OriginalValue);

	return MappedValue * CurrentSteeringAngle;
}

void ABike::Throttle(float Value)
{
	// Move the bike forward

	ThrottleValue = Value;
	float CurrentValue = CurrentSpeed;
	float TargetValue = MaxSpeed * Value;
	float InterpolationSpeed = 4.0f;

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Perform interpolation and save the result in a variable
	float InterpolatedValue = FMath::FInterpTo(CurrentValue, TargetValue, DeltaTime, InterpolationSpeed);
	CurrentSpeed = InterpolatedValue;
}

void ABike::Steer(float Value)
{
	// Rotate the bike based on input
	/*FRotator TurnRotation = FRotator(0.0f, Value * TurnSpeed * GetWorld()->GetDeltaSeconds(), 0.0f);
	AddActorWorldRotation(TurnRotation);*/
	float CurrentValue = CurrentSteeringAngle;  
	float TargetValue = MaxSteeringAngle * Value;  
	float InterpolationSpeed = 4.0f; 

	float DeltaTime = GetWorld()->GetDeltaSeconds(); 

	// Perform interpolation and save the result in a variable
	float InterpolatedValue = FMath::FInterpTo(CurrentValue, TargetValue, DeltaTime, InterpolationSpeed);
	CurrentSteeringAngle = InterpolatedValue;
}

void ABike::EngineSound()
{
	if (BikeEngineSound) {
		float OriginalValue = CurrentSpeed;  // The original value you want to map
		float OriginalMin = 0.0f;     // The minimum value of the original range
		float OriginalMax = MaxSpeed;    // The maximum value of the original range

		float NewMin = 0.3f;          // The minimum value of the target range
		float NewMax = 1.0f;          // The maximum value of the target range

		float MappedVolumeValue = FMath::GetMappedRangeValueClamped(
			FVector2D(OriginalMin, OriginalMax),
			FVector2D(NewMin, NewMax),
			OriginalValue);
		BikeEngineSound->SetVolumeMultiplier(MappedVolumeValue);

		float MappedPitchValue = FMath::GetMappedRangeValueClamped(
			FVector2D(OriginalMin, OriginalMax),
			FVector2D(0.4f, 1.2f),
			OriginalValue);
		BikeEngineSound->SetPitchMultiplier(MappedPitchValue);
	}
}