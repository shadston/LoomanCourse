// Fill out your copyright notice in the Description page of Project Settings.


#include "TLInteractionComponent.h"
#include "TLGameplayInterface.h"

// Sets default values for this component's properties
UTLInteractionComponent::UTLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTLInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	AActor* Owner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 350.0f);

	/*FHitResult Hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);*/

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float Radius = 30.0f;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor DebugColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, DebugColor, false, 2.0f);
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<UTLGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);
				ITLGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
		}
	}


	DrawDebugLine(GetWorld(), EyeLocation, End, DebugColor, false, 2.0f, 0, 2.0f);
}
