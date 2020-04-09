// Fill out your copyright notice in the Description page of Project Settings.


#include "Damageable.h"

// Sets default values
ADamageable::ADamageable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


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

float ADamageable::GetMaxHealth_Implementation()
{
	return MaxHealth;
}

void ADamageable::TakeAttack_Implementation() {
	SubtractHealth(12);

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(Health));


	OnAttacked();
}
void ADamageable::AddHealth_Implementation(float pts) {
	Health += pts;
}
void ADamageable::SubtractHealth_Implementation(float pts) {
	Health -= pts;

	if (Health <= 0)
		Die();
}

float ADamageable::GetHealth_Implementation()
{
	return Health;
}

void ADamageable::InstantRespawn_Implementation() {
	
	Health = MaxHealth;


	RootComponent->SetWorldLocation(InitialSpawnPosition);
}
void ADamageable::Die_Implementation() {
	OnDeath();
}


void ADamageable::OnAttacked_Implementation() {

}

void ADamageable::OnDeath_Implementation() {

}
