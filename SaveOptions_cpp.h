// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveOptions_cpp.generated.h"

/**
 * 
 */
UCLASS()
class RUNJUMPANDPLAY_API USaveOptions_cpp : public USaveGame
{
	GENERATED_BODY()


	
	USaveOptions_cpp();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SensitivityY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SensitivityX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AAQuality;

	
};
