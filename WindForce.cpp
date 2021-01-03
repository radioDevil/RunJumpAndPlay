// Fill out your copyright notice in the Description page of Project Settings.


#include "WindForce.h"
///----------Engine
#include "Engine/Engine.h"
///----------Game frameworks
#include "GameFramework/CharacterMovementComponent.h"
///----------Components
#include "Components/ShapeComponent.h"
#include "Components/ArrowComponent.h"
///----------Kismet
#include "Kismet/GameplayStatics.h"
///----------Other
#include "Player_cpp.h"



AWindForce::AWindForce()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = GetCollisionComponent();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWindForce::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AWindForce::OnOverlapEnd);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow component"));
	Arrow->SetupAttachment(CollisionComponent);


}

void AWindForce::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* _OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor = _OtherActor;
	isForce = true;
}

void AWindForce::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* _OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isForce = false;
}

void AWindForce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isForce)
	{
		if (OtherActor)
		{
			if (OtherActor->ActorHasTag("player"))
			{
				class APlayer_cpp* plr = Cast<APlayer_cpp>(OtherActor);
				plr->GetCharacterMovement()->AddForce((Arrow->GetForwardVector() * Force) * 10000);

			}

		}
	}
}

