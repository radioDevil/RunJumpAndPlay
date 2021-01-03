// Fill out your copyright notice in the Description page of Project Settings.


#include "Ventilator.h"
#include "Components/StaticMeshComponent.h"
#include "Player_cpp.h"
#include "Engine/Engine.h"


// Sets default values
AVentilator::AVentilator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VentilatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh ventilator"));
	VentilatorMesh->OnComponentBeginOverlap.AddDynamic(this, &AVentilator::OnOverlapBegin);
	VentilatorMesh->OnComponentEndOverlap.AddDynamic(this, &AVentilator::OnOverlapEnd);
	
	FCollisionResponseContainer collision;
	collision.Pawn = 1;
	
	VentilatorMesh->SetCollisionResponseToChannels(collision);

}

// Called when the game starts or when spawned
void AVentilator::BeginPlay()
{
	Super::BeginPlay();
	

}



void AVentilator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor != nullptr && isDamage)
	{
		if (OtherActor->ActorHasTag("player"))
		{
			class APlayer_cpp* plr = Cast<APlayer_cpp>(OtherActor);
			plr->Respawn();
		}
	}

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Cyan, FString::Printf(TEXT("Damage")));
	//}
}

void AVentilator::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AVentilator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult res;
	VentilatorMesh->K2_AddWorldRotation((SpeedRotation  * 100.f) * DeltaTime, true, res, true);
	

}

