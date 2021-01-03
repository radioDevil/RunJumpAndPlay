// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LoadLevelBox.generated.h"

/**
 * 
 */
UCLASS()
class RUNJUMPANDPLAY_API ALoadLevelBox : public ATriggerBox
{
	GENERATED_BODY()

		ALoadLevelBox();

	UShapeComponent* CollisionComponent;

public:
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelName;
};
