// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageableCharacter.generated.h"

UCLASS()
class TESTGAME3_API ADamageableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADamageableCharacter();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ShootAtPosition(FVector2D mousePosition);

	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadWrite)
	float FireRate;
	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadWrite)
	float SecondaryFireRate;
	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadWrite)
	float FireOffset;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;


	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();
	void ShotSecondaryTimerExpired();

	static const FName MainFireBinding;
	static const FName SecondaryFireBinding;

	UPROPERTY(Category = "Weapon", EditAnywhere)
	float BulletSpread;


	UPROPERTY(Category = "Weapon", EditAnywhere)
	TSubclassOf<class AProjectile> PrimaryWeaponClass;
	UPROPERTY(Category = "Weapon", EditAnywhere)
	TSubclassOf<class AProjectile> SecondaryWeaponClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Flag to control firing  */
	uint32 bCanFire : 1;
	uint32 bCanFireSecondary : 1;
	bool bIsFiringMainWeapon = 0;
	bool bIsFiringSecondaryWeapon = 0;


	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;
	FTimerHandle TimerHandle_ShotSecondaryTimerExpired;

	FVector GetWorldPositionFromCursor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartMainWeapon();
	void StopMainWeapon();
	void StartSecondaryWeapon();
	void StopSecondaryWeapon();
	void FireMainWeapon();
	void FireSecondaryWeapon();

};
