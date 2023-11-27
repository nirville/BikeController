// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/MovementComponent.h"
#include "BikeAnimInstance.h"
#include "Bike.generated.h"

UCLASS()
class DRIVABLEBIKE_API ABike : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "My Functions")
        float MyFloatSteering();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        USkeletalMeshComponent* BikeMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float TurnSpeed;

    // New function to handle input for movement
    void Throttle(float Value);
    void Steer(float Value);
    void EngineSound();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float MaxSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float CurrentSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float MaxSteeringAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float CurrentSteeringAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float CurrentLeanAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float SpeedToRotationFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        float ThrottleValue;

    UPROPERTY(VisibleAnywhere)
        UMovementComponent* BikeMovement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Properties", meta = (AllowPrivateAccess = "true"))
        UAnimInstance* AnimInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bike Sound", meta = (AllowPrivateAccess = "true"))
        UAudioComponent* BikeEngineSound;
};
