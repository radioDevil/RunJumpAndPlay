// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBox_cpp.h"
#include "Engine/Engine.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player_cpp.h"

ADeathBox_cpp::ADeathBox_cpp()
{

	CollisionComponent = GetCollisionComponent();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox_cpp::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADeathBox_cpp::OnOverlapEnd);
}


void ADeathBox_cpp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayer_cpp* p = (APlayer_cpp*)OtherActor;
	p->Respawn();
}

void ADeathBox_cpp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
