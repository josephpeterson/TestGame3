// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableObject.h"

// Sets default values
ADamageableObject::ADamageableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MaxHealth = 100;
	Health = 100;

	Health2 = 21321;

	Defense = 0;
	SpDefense = 0;
}

// Called when the game starts or when spawned
void ADamageableObject::BeginPlay()
{
	Super::BeginPlay();
	

	InitialSpawnPosition = RootComponent->GetRelativeLocation();
}

// Called every frame
void ADamageableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADamageableObject::TakeAttack_Implementation(UBasicAttack* attack) {
	
	
	AActor* infl = Cast<AActor>(attack->Owner);
	if (infl)
	{

	}


	Health -= attack->DirectDamage;
	if (Health <= 0)
	{
		if(infl)
			OnDeath(infl);
	}



	OnAttacked(nullptr,attack);
}
void ADamageableObject::AddHealth_Implementation(float pts) {
	Health += pts;
}
void ADamageableObject::SubtractHealth_Implementation(float pts) {
	Health -= pts;

	if (Health <= 0)
		Die();
}



void ADamageableObject::InstantRespawn_Implementation() {
	
	Health = MaxHealth;


	RootComponent->SetWorldLocation(InitialSpawnPosition);
}
void ADamageableObject::Die_Implementation() {
	OnDeath(nullptr);
}


void ADamageableObject::OnAttacked_Implementation(IIDamageable* inflictor, UBasicAttack* attack) {

}

void ADamageableObject::OnDeath_Implementation(class AActor* killer) {

}








float ADamageableObject::GetMaxHealth()
{
	return MaxHealth;
}



float ADamageableObject::GetHealth()
{

	return Health;
}