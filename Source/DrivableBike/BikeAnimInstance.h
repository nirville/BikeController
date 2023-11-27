// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BikeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRIVABLEBIKE_API UBikeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBikeAnimInstance();

	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Anim Properties", meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Anim Properties", meta = (AllowPrivateAccess = "true"))
		float Steering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Anim Properties", meta = (AllowPrivateAccess = "true"))
		float WheelRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bike Anim Properties", meta = (AllowPrivateAccess = "true"))
		float WheelRotAngle;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class ABike* Bike;
};
