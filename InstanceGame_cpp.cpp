// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceGame_cpp.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "SaveOptions_cpp.h"
#include "Player_cpp.h"


UInstanceGame_cpp::UInstanceGame_cpp()
{

	SaveName = "SaveGameName";

}

void UInstanceGame_cpp::Init()
{
	


	UE_LOG(LogTemp, Warning, TEXT("Created by Ilyin Vadim Romanovich"));
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		UGameplayStatics::CreateSaveGameObject(USaveOptions_cpp::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Create save instance"));
	}

}
