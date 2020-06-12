// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"


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

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
    if(!GetControlledTank()) { return; }

    FVector HitLocation;
    GetSightRayHitLocation(HitLocation);

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
    FVector LookDirection;

    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        if(GetLookVectorHitLocation(LookDirection, OutHitLocation))
        {
            GetControlledTank()->AimAt(OutHitLocation);
        }
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector WorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y,
        WorldLocation, 
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility)
    )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    
    return false;
}

