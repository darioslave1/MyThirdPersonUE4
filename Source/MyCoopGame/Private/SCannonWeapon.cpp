// Fill out your copyright notice in the Description page of Project Settings.

#include "SCannonWeapon.h"
#include "FPSProjectile.h"
#include "Components/SkeletalMeshComponent.h"

void ASCannonWeapon::Fire()
{
	//crea un projectil
	if (ProjectileClass)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			FVector EyeLocation;
			FRotator EyeRotation;
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MeshComp->GetSocketLocation(MuzzleFireSocketName),
				EyeRotation, ActorSpawnParams);
		}
	}
	
}


