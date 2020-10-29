// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "SnakeBase.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::Interact(AActor* Interactor, bool bIsHead)
{
    auto Snake = Cast<ASnakeBase>(Interactor);
    if (IsValid(Snake))
    {
        Snake->Destroy();
    }
}
