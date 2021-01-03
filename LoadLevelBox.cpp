// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadLevelBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player_cpp.h"
#include "Engine/Engine.h"
#include "Components/ShapeComponent.h"

ALoadLevelBox::ALoadLevelBox()
{
	CollisionComponent = GetCollisionComponent();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALoadLevelBox::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ALoadLevelBox::OnOverlapEnd);
}

void ALoadLevelBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FLatentActionInfo LatentInfo;
	if (LevelName != "")
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}

}

void ALoadLevelBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

