// Fill out your copyright notice in the Description page of Project Settings.


#include "Damageable.h"

// Sets default values
ADamageable::ADamageable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	InitialHealth = 100;
	MaxHealth = 100;
	Health = 100;

	Defense = 0;
	SpDefense = 0;
}

// Called when the game starts or when spawned
void ADamageable::BeginPlay()
{
	Super::BeginPlay();
	

	InitialSpawnPosition = RootComponent->GetRelativeLocation();
}

// Called every frame
void ADamageable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageable::TakeAttack() {
	SubtractHealth(12);

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(Health));


	OnAttacked();
}
void ADamageable::AddHealth(float pts) {
	Health += pts;
}
void ADamageable::SubtractHealth(float pts) {
	Health -= pts;

	if (Health <= 0)
		InstantRespawn();
}

void ADamageable::InstantRespawn() {
	
	Health = MaxHealth;
	RootComponent->SetWorldLocation(InitialSpawnPosition);
}
void ADamageable::Die() {

}


void ADamageable::OnAttacked_Implementation() {

}


