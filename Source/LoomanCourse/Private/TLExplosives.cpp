// Fill out your copyright notice in the Description page of Project Settings.


#include "TLExplosives.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ATLExplosives::ATLExplosives()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor");
	RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->Radius = 700.0f;
	RadialForceComp->ForceStrength = 10.0f;
	RadialForceComp->bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void ATLExplosives::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentHit.AddDynamic(this, &ATLExplosives::OnHit);
}

void ATLExplosives::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
	OtherActor->Destroy();
}

// Called every frame
void ATLExplosives::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
