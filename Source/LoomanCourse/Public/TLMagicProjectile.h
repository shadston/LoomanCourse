// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLMagicProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class LOOMANCOURSE_API ATLMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATLMagicProjectile();

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere)
	float ProjectileLifetime = 5.0f;

	FTimerHandle TimerHandle_Lifetime;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
