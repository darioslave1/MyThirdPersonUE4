// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMEsh"));
	RootComponent = MeshComp;

	MuzzleFireSocketName = TEXT("MuzzleFlashSocket");
	TracerEffectTargetName = TEXT("TargetBeam");
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FHitResult HitResult;
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceDirection = EyeRotation.Vector();
		FVector EndTrace = EyeLocation + (TraceDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		//Smoke effect End Position
		FVector TracerEndPosition = EndTrace;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndTrace, ECollisionChannel::ECC_Visibility, QueryParams))
		{
			UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), 20.f, TraceDirection, HitResult,
				MyOwner->GetInstigatorController(), this, DamageType);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageEffect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			TracerEndPosition = HitResult.ImpactPoint;
		}

		DrawDebugLine(GetWorld(), EyeLocation, EndTrace, FColor::White, false, 1.f, 0, 1.f);

		if (MuzzleFireEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFireEffect, MeshComp, MuzzleFireSocketName);
		}
		
		if (SmokeTracerEffect)
		{
			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeTracerEffect, MeshComp->GetSocketLocation(MuzzleFireSocketName));
			if (TracerComp)
			{
				TracerComp->SetVectorParameter(TracerEffectTargetName, TracerEndPosition);
			}
		}
	}

}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

