// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableCharacter.h"
#include "MyProject5Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "DrawDebugHelpers.h"
#include "GroundFloorActor.h"
#include "SecondaryAttackProjectile.h"
#include "Math/UnrealMathUtility.h"

const FName ADamageableCharacter::MainFireBinding("MainFire");
const FName ADamageableCharacter::SecondaryFireBinding("SecondaryFire");

// Sets default values
ADamageableCharacter::ADamageableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;
	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	FireRate = 0.1f;
	SecondaryFireRate = 5.f;
	FireOffset = 60.f;
	bCanFire = true;
	bCanFireSecondary = true;
	BulletSpread = 0;




	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ADamageableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bIsFiringMainWeapon && bCanFire)
	{
		FireMainWeapon();
	}
	if (bIsFiringSecondaryWeapon && bCanFireSecondary)
		FireSecondaryWeapon();
}

// Called to bind functionality to input
void ADamageableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	PlayerInputComponent->BindAction(MainFireBinding, IE_Pressed, this, &ADamageableCharacter::StartMainWeapon);
	PlayerInputComponent->BindAction(MainFireBinding, IE_Repeat, this, &ADamageableCharacter::StartMainWeapon);
	PlayerInputComponent->BindAction(MainFireBinding, IE_DoubleClick, this, &ADamageableCharacter::StartMainWeapon);

	PlayerInputComponent->BindAction(MainFireBinding, IE_Released, this, &ADamageableCharacter::StopMainWeapon);



	PlayerInputComponent->BindAction(SecondaryFireBinding, IE_Pressed, this, &ADamageableCharacter::StartSecondaryWeapon);
	PlayerInputComponent->BindAction(SecondaryFireBinding, IE_Released, this, &ADamageableCharacter::StopSecondaryWeapon);

}
void ADamageableCharacter::StartMainWeapon() {
	ADamageableCharacter::bIsFiringMainWeapon = 1;
}
void ADamageableCharacter::StopMainWeapon() {
	ADamageableCharacter::bIsFiringMainWeapon = 0;
}
void ADamageableCharacter::StartSecondaryWeapon() {
	ADamageableCharacter::bIsFiringSecondaryWeapon = 1;
}
void ADamageableCharacter::StopSecondaryWeapon() {
	ADamageableCharacter::bIsFiringSecondaryWeapon = 0;
}

void ADamageableCharacter::ShotTimerExpired()
{
	bCanFire = true;
}
void ADamageableCharacter::ShotSecondaryTimerExpired()
{
	bCanFireSecondary = true;
}
void ADamageableCharacter::FireMainWeapon() {

	UWorld* const World = GetWorld();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr && PrimaryWeaponClass && World != NULL)
	{
		FVector projectilePosition = GetActorLocation();

		FVector pos = GetWorldPositionFromCursor();


		FVector dir = pos - projectilePosition;
		dir.Normalize();
		dir.Z = 0;


		projectilePosition = projectilePosition + dir * FireOffset;

		FRotator FireRotation = dir.Rotation();


		if (BulletSpread > 0) {
			float pitch = FMath::RandRange(-BulletSpread, BulletSpread);
			float Yaw = FMath::RandRange(-BulletSpread, BulletSpread);
			FireRotation.Yaw += Yaw;
			//FireRotation.Pitch += pitch;
		}



		


		FActorSpawnParameters spawnParams;
		spawnParams.Owner = PlayerController;
		AProjectile* p = World->SpawnActor<AProjectile>(PrimaryWeaponClass , projectilePosition, FireRotation, spawnParams);

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, projectilePosition);
		}



		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ADamageableCharacter::ShotTimerExpired, FireRate);
	}
}
void ADamageableCharacter::FireSecondaryWeapon() {

	UWorld* const World = GetWorld();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr && SecondaryWeaponClass && World != NULL)
	{
		FVector pos = GetWorldPositionFromCursor();

		float count = 10.f;
		int maxAngle = 360;
		int radius = 20;
		

	
		for (int i = 0; i < count; i++) {
			double angle = i / count * 360;
			//FRotator rot = OutHit.TraceEnd.RotateAngleAxis(angle, Direction).Rotation();
			FVector dir = FVector(cos(angle), sin(angle), 0);
			FVector pos2 = pos + (dir * radius);
			FRotator rot = dir.Rotation();
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			AProjectile* p = World->SpawnActor<AProjectile>(SecondaryWeaponClass, pos2, rot, spawnParams);
		
			//p->SetActorEnableCollision(false);

		}
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, pos);
		}



		bCanFireSecondary = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotSecondaryTimerExpired, this, &ADamageableCharacter::ShotSecondaryTimerExpired, SecondaryFireRate);
	}

}

FVector ADamageableCharacter::GetWorldPositionFromCursor() {

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UWorld* const World = GetWorld();
	if (PlayerController != nullptr && World != NULL)
	{

		FVector Location, Direction;
		PlayerController->DeprojectMousePositionToWorld(Location, Direction);


		FHitResult OutHit;
		FVector Start = Location;

		FVector ForwardVector = Direction;
		FVector End = ((ForwardVector * 5000.f) + Start);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this->GetOwner());

		bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel3, CollisionParams);


		if (IsHit) {
			AActor* a = OutHit.GetActor();


			AGroundFloorActor* mapFloor = Cast<AGroundFloorActor>(OutHit.GetActor());
			if (mapFloor) {
				float count = 10.f;
				int maxAngle = 360;
				int radius = 50;

				const FVector newPos = Start + Direction * (OutHit.Distance - 100);


				return newPos;
			}
		}
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);
	}
	return FVector();
}











//Deprecated
void ADamageableCharacter::ShootAtPosition(FVector2D mousePosition) {

	// Create fire direction vector
	const float FireForwardValue = mousePosition.X;
	const float FireRightValue = mousePosition.Y;
	const FVector FireDirection = GetActorForwardVector();

	// Spawn projectile at an offset from this pawn
	FVector SpawnLocation = GetActorLocation();



	//Compute rotation
	FVector2D center = FVector2D(642, 446);

	FVector2D c = mousePosition - center;


	c.Normalize();

	FRotator FireRotation = FVector(c.X, c.Y, 0).Rotation() + FireDirection.Rotation();
	FireRotation.Add(0, 90.f, 0);



	SpawnLocation += FireRotation.Vector() * FireOffset;

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		// spawn the projectile
		AProjectile* p = World->SpawnActor<AProjectile>(PrimaryWeaponClass, SpawnLocation, FireRotation);
		//p->SetActorEnableCollision(false);
	}

	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ADamageableCharacter::ShotTimerExpired, FireRate);

	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	bCanFire = false;
}
