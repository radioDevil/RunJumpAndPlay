// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ventilator.generated.h"

UCLASS()
class RUNJUMPANDPLAY_API AVentilator : public AActor
{
	GENERATED_BODY()
	



public:	
	// Sets default values for this actor's properties
	AVentilator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* VentilatorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpeedRotation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
