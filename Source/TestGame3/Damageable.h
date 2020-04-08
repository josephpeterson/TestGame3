// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageable.generated.h"

UCLASS()
class TESTGAME3_API ADamageable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageable();



	/* Damage Properties */
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float InitialHealth;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float Health;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float SpDefense;




	/* Health Operations */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeAttack();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void AddHealth(float pts);
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SubtractHealth(float pts);

	/* Death */
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void Die();
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void InstantRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector InitialSpawnPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
