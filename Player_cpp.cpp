// Fill out your copyright notice in the Description page of Project Settings.



#include "Player_cpp.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InstanceGame_cpp.h"
#include "GameFramework/SaveGame.h"
#include "SaveOptions_cpp.h"
#include "Sound/SoundCue.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/AudioComponent.h"

#define FORCE_GRABHOOK FMath::Abs(250.f * 7.5f)
#define TRACELENGTH 1000


// Sets default values
APlayer_cpp::APlayer_cpp()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->bUsePawnControlRotation = false;
	Camera->PostProcessSettings.WhiteTemp = 6000.f;
	Camera->PostProcessSettings.BloomIntensity = 1.f;
	Camera->PostProcessSettings.LensFlareIntensity = 15.6f;
	Camera->PostProcessSettings.FilmSlope = 1.f;
	Camera->PostProcessSettings.DepthOfFieldFocalDistance = 100.f;
	
	GetCharacterMovement()->Mass = 400.f;

	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("CableActor"));
	Cable->CableLength = 0.f;
	Cable->NumSegments = 1;
	Cable->CastShadow = false;
	Cable->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);


	//SensitivityX = 1.5f; // 1.5f;
	//SensitivityY = 1.5f; // 1.5f;
	
	
	GetCharacterMovement()->AirControl = 0.85f;
	APawn::Tags.Add("player");
	APawn::AutoPossessPlayer = EAutoReceiveInput::Player0;


	static ConstructorHelpers::FObjectFinder<USoundCue> AudioStep(TEXT("SoundCue'/Game/sound/cue_Step_grass.cue_Step_grass'"));
	if (AudioStep.Succeeded())
		Step_cue = AudioStep.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> AudioFall(TEXT("SoundCue'/Game/sound/cue_Step_fall.cue_Step_fall'"));
	if (AudioFall.Succeeded())
		Fall_cue = AudioFall.Object;
	
	
	Fall = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Fall component"));
	Fall->SetupAttachment(RootComponent);

	Step = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Step component"));
	Step->SetupAttachment(RootComponent);
	

}



// Called when the game starts or when spawned
void APlayer_cpp::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();

	RestartSettings();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("SensetivityX: %f\nSensetivityY: %f"),SensitivityX, SensitivityY ));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);

	if (Step != nullptr && Step_cue != nullptr)
	{
		Step->SetSound(Step_cue);
	}

	if (Fall != nullptr && Fall_cue != nullptr)
	{
		Fall->SetSound(Fall_cue);
	}


}

void APlayer_cpp::MoveForward(float Value)
{
	if (Value != 0.0f && Controller != nullptr)
	{
		MovingValue = Value;

		AddMovementInput(GetCapsuleComponent()->GetForwardVector(), Value);

	}


	if ((Value != 0.0f && Controller != nullptr))
	{
		if (!GetMovementComponent()->IsFalling())
		{
			if (!Step->IsPlaying())
			{
				Step->Play();

			}
		}
	}
}

void APlayer_cpp::MoveRight(float Value)
{
	if (Value != 0.0f && Controller != nullptr)
	{
		MovingValue = Value;

		AddMovementInput((GetCapsuleComponent()->GetRightVector()), Value);

		

	}

	if ((Value != 0.0f && Controller != nullptr))
	{
		if (!GetMovementComponent()->IsFalling())
		{
			if (!Step->IsPlaying())
			{
				Step->Play();

			}
		}
	}
}

void APlayer_cpp::Turn(float Value)
{
	APawn::AddControllerPitchInput(SensitivityY * Value);
}

void APlayer_cpp::LookUp(float Value)
{
	APawn::AddControllerYawInput(SensitivityX * Value);
}

void APlayer_cpp::LeftMousePressed()
{
	LeftMouseClick = true;


	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	FHitResult OutHit;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * TRACELENGTH);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CQP);



	if (OutHit.bBlockingHit)
	{

		OutHit_ = OutHit;



		/*if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("%s"), *OutHit.Location.ToString()));
		}*/
	}

}

void APlayer_cpp::LeftMouseReleased()
{
	LeftMouseClick = false;
	OutHit_.bBlockingHit = false;
}

void APlayer_cpp::RightMousePressed()
{
	
}

void APlayer_cpp::RightMouseReleased()
{


	

	//FCollisionQueryParams CQP;
	//CQP.AddIgnoredActor(this);
	//FHitResult OutHit;

	//FVector Start = Camera->GetComponentLocation();
	//FVector End = Start + (Camera->GetForwardVector() * 5000);

	//GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CQP);
	//OutHit_ = OutHit;

}

void APlayer_cpp::Escape()
{
	bEscape = !bEscape;

	Pause();
}



void APlayer_cpp::Pause()
{
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetPause(true);

	if (IsValid(Widget))
	{
		Widget->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(PlayerController, Widget);
		PlayerController->bShowMouseCursor = true;
	}
	else
	{
		if (PauseMenu)
		{
			Widget = CreateWidget(PlayerController, PauseMenu);
			Widget->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnly(PlayerController, Widget);
			PlayerController->bShowMouseCursor = true;
		}
	}
	
}

void APlayer_cpp::UnPause()
{
	if (IsValid(Widget))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetPause(false);

		UWidgetLayoutLibrary::RemoveAllWidgets(Widget);



		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
	}
}

bool APlayer_cpp::RestartSettings()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);


	if (UGameplayStatics::DoesSaveGameExist("SaveGameName", 0))
	{
		class USaveOptions_cpp* Save = Cast<USaveOptions_cpp>(UGameplayStatics::LoadGameFromSlot("SaveGameName", 0));

		SensitivityX = Save->SensitivityX;
		SensitivityY = Save->SensitivityY;

		return true;
	}
	else if(!UGameplayStatics::DoesSaveGameExist("SaveGameName", 0))
	{
		class USaveOptions_cpp* Save = Cast<USaveOptions_cpp>(UGameplayStatics::CreateSaveGameObject(USaveOptions_cpp::StaticClass()));

		SensitivityX = Save->SensitivityX;
		SensitivityY = Save->SensitivityY;
		return true;
	}

	return false;
}

// Called every frame
void APlayer_cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FVector sum_ = GetVelocity();
		sum_.Z = FMath::Abs((sum_.Z / 100.f) * 1.5f);
		
		Camera->FieldOfView = FMath::Lerp(Camera->FieldOfView, 90.f + sum_.Z, DeltaTime);
	}
	Camera->FieldOfView = FMath::Clamp(Camera->FieldOfView, 90.f, 120.f);

	
	{

		FCollisionQueryParams CQP;
		CQP.AddIgnoredActor(this);
		FHitResult OutHit;

		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + (Camera->GetForwardVector() * TRACELENGTH);

		GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CQP);

		if (OutHit.bBlockingHit)
		{
			bCrosshair = true;
		}
		else
		{
			bCrosshair = false;
		}

	}


	if (LeftMouseClick)
	{
		if (OutHit_.bBlockingHit)
		{
			GetCharacterMovement()->AddForce((OutHit_.Location - GetCapsuleComponent()->GetComponentLocation()) * FORCE_GRABHOOK);
			Cable->SetWorldLocation(OutHit_.Location);
		}
	}
	else
		Cable->SetRelativeLocation(FVector::ZeroVector);

	if (!bFall)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			bFall = true;
			Fall->Play();
		}
	}
	
	if (GetCharacterMovement()->IsFalling())
	{
		bFall = false;
	}
}

void APlayer_cpp::Respawn()
{
	SetActorLocation(SpawnLocation);
	LeftMouseClick = false;
	GetCharacterMovement()->Velocity = { 0.f,0.f,0.f };
}



// Called to bind functionality to input
void APlayer_cpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APlayer_cpp::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_cpp::LookUp);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_cpp::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_cpp::MoveForward);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_cpp::Jump);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &APlayer_cpp::LeftMousePressed);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Released, this, &APlayer_cpp::LeftMouseReleased);


	PlayerInputComponent->BindAction("RightMouseButton", IE_Pressed, this, &APlayer_cpp::RightMousePressed);
	PlayerInputComponent->BindAction("RightMouseButton", IE_Released, this, &APlayer_cpp::RightMouseReleased);

	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &APlayer_cpp::Escape);
	

}

