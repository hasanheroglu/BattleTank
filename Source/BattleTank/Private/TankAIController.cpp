// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

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

    if(GetPlayerTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("Get player tank named %s."), *GetPlayerTank()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot get player tank."));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    if(GetControlledTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


