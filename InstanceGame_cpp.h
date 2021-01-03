// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player_cpp.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InstanceGame_cpp.generated.h"

/**
 * 
 */
UCLASS()
class RUNJUMPANDPLAY_API UInstanceGame_cpp : public UGameInstance
{
	GENERATED_BODY()

		UInstanceGame_cpp();

	FString SaveName;

	virtual void Init() override;


	


	  
};
