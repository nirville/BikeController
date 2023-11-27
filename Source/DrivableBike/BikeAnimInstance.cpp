// Fill out your copyright notice in the Description page of Project Settings.


#include "BikeAnimInstance.h"
#include "Bike.h"

UBikeAnimInstance::UBikeAnimInstance() :
	Speed(0.f),
	Steering(0.f),
	WheelRadius(30.f),
	WheelRotAngle(0.f)
{
}

void UBikeAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Bike == nullptr) {
		Bike = Cast<ABike>(TryGetPawnOwner());
	}
}

void UBikeAnimInstance::NativeInitializeAnimation()
{
	Bike = Cast<ABike>(TryGetPawnOwner());
}
