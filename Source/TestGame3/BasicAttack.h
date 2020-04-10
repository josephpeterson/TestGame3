// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "BasicAttack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class TESTGAME3_API UBasicAttack: public UObject
{
	GENERATED_BODY()

public:
	UBasicAttack();
	~UBasicAttack();


	UPROPERTY(Category = Damage, EditAnywhere)
		float DirectDamage;
	UPROPERTY(Category = Damage, EditAnywhere)
		float SpDamage;

	UPROPERTY(Category = Damage, EditAnywhere)
		FString Name;


	class IIDamageable* Owner;


};
