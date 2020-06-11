// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Begin Play executed."));

    if(GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("Get controlled tank by AI Controller is named %s."), *GetControlledTank()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot get controlled tank by AI Controller."));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


