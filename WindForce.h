// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WindForce.generated.h"

/**
 * 
 */
UCLASS()
class RUNJUMPANDPLAY_API AWindForce : public ATriggerBox
{
	AWindForce();

	GENERATED_BODY()



	UShapeComponent* CollisionComponent;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* _OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* _OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void Tick(float DeltaTime) override;

	class AActor* OtherActor;
	bool isForce;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* Arrow;

};
