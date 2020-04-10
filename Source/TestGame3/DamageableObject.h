// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamageable.h"
#include "DamageableObject.generated.h"

UCLASS()
class TESTGAME3_API ADamageableObject : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageableObject();

	UPROPERTY(Category = Damage, EditAnywhere)
		float MaxHealth;
	UPROPERTY(Category = Damage, EditAnywhere)
		float Health;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(Category = Damage, EditAnywhere, BlueprintReadWrite)
	float SpDefense;




	
protected:

	float Health2;

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
	UFUNCTION(BlueprintCallable, Category = "Damage")
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Damage")
		float GetMaxHealth();

	/* Attack */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void TakeAttack(UBasicAttack* attack);
	virtual void TakeAttack_Implementation(UBasicAttack* attack);

	/* Death */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void Die();
	virtual void Die_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void InstantRespawn();
	virtual void InstantRespawn_Implementation();

	/* Callbacks */
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnAttacked(const TScriptInterface<IIDamageable>& inflictor, UBasicAttack* attack);
	virtual void OnAttacked_Implementation(IIDamageable* inflictor, UBasicAttack* attack);
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnDeath(class AActor* killer);
	virtual void OnDeath_Implementation(class AActor* killer);


};
