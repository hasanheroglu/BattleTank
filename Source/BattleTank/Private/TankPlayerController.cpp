// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play executed."));

    if(GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("Get controlled tank named %s."), *GetControlledTank()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot get controlled tank."));
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
