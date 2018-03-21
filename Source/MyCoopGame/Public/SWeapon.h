// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;

UCLASS()
class MYCOOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* MuzzleFireEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* DamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* SmokeTracerEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	FName MuzzleFireSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	FName TracerEffectTargetName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
