// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamageable.h"
#include "Damageable.generated.h"

UCLASS()
class TESTGAME3_API ADamageable : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageable();

	UPROPERTY(Category = Damage, EditAnywhere)
		float MaxHealth;
	UPROPERTY(Category = Damage, EditAnywhere)
		float Health;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float SpDefense;




	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector InitialSpawnPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	/* Health Operations */
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void AddHealth(float pts);
	virtual void AddHealth_Implementation(float pts);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void SubtractHealth(float pts);
	virtual void SubtractHealth_Implementation(float pts);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		float GetHealth();
	virtual float GetHealth_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		float GetMaxHealth();
	virtual float GetMaxHealth_Implementation();

	/* Attack */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void TakeAttack();
	virtual void TakeAttack_Implementation();

	/* Death */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void Die();
	virtual void Die_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void InstantRespawn();
	virtual void InstantRespawn_Implementation();

	/* Callbacks */
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnAttacked();
	virtual void OnAttacked_Implementation();
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnDeath();
	virtual void OnDeath_Implementation();


};
