// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SCannonWeapon.generated.h"

class AFPSProjectile;

/**
 * 
 */
UCLASS()
class MYCOOPGAME_API ASCannonWeapon : public ASWeapon
{
	GENERATED_BODY()

public:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;
	
protected:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();
	
	
};
