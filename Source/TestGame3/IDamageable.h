// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicAttack.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTGAME3_API IIDamageable
{
	GENERATED_BODY()


	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/* Callbacks */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Damage")
	void WatDid();


	/* Health Operations */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void AddHealth(float pts);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void SubtractHealth(float pts);
		float GetHealth();
		float GetMaxHealth();

	/* Attack */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void TakeAttack(UBasicAttack* attack);

	/* Death */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Damage")
		void Die();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void InstantRespawn();

	/* Events */
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnAttacked(const TScriptInterface<IIDamageable>& inflictor,UBasicAttack* attack);
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
		void OnDeath(const TScriptInterface<IIDamageable>& killer);

};
 