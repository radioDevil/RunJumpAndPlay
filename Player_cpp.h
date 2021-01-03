// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_cpp.generated.h"

UCLASS()
class RUNJUMPANDPLAY_API APlayer_cpp : public ACharacter
{
	GENERATED_BODY()

	float SensitivityX;
	float SensitivityY;

	bool bCrosshair;
	

	float MovingValue;

public:
	// Sets default values for this character's properties
	APlayer_cpp();

	UFUNCTION(BlueprintCallable)
		bool GetCrosshair() { return bCrosshair; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Turn(float Value);
	void LookUp(float Value);

	void LeftMousePressed();
	void LeftMouseReleased();

	void RightMousePressed();
	void RightMouseReleased();

	void Escape();

	bool bEscape;

	bool LeftMouseClick;
	bool bFall = true;

	FHitResult OutHit_;


	UFUNCTION(BlueprintCallable)
		void Pause();

	UFUNCTION(BlueprintCallable)
		void UnPause();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCableComponent* Cable;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Bullet;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<class UUserWidget> PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	class UUserWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* Fall_cue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class UAudioComponent* Fall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* AirSound_cue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class UAudioComponent* AirSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class UAudioComponent* Step;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Sound")
		class USoundCue* Step_cue;

	UFUNCTION(BlueprintCallable)
		float GetSensitivityY() { return SensitivityY; };

	UFUNCTION(BlueprintCallable)
		float GetSensitivityX() { return SensitivityX; };

	UFUNCTION(BlueprintCallable)
		void SetSensitivityY(float value) { SensitivityY = value; };

	UFUNCTION(BlueprintCallable)
		void SetSensitivityX(float value) { SensitivityX = value; };

	UFUNCTION()
	void Respawn();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		bool RestartSettings();
};
