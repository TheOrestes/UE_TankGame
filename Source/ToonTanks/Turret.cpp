// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Call CheckFireCondition() every "FireRate" seconds!
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition()
{
	if (InFireRange())
		Fire();
}

bool ATurret::InFireRange()
{
	// Find distance to the tank
	if (Tank)
	{
		float distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// check to see if tank is the range
		if (distance <= FireRange)
			return true;
	}

	return false;
}

ATurret::ATurret()
{
	
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
		RotateTowards(Tank->GetActorLocation());
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}


