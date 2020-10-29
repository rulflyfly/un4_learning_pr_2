// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "Food.h"
// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ElementSize = 50.f;
    MovementSpeed = 0.5f;
    LastMovementDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
    SetActorTickInterval(MovementSpeed);
    AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
    for (int i = 0; i < ElementsNum; i++)
    {
        FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
        FTransform NewTransform(NewLocation);
        
        ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);

        NewSnakeElem->SetActorHiddenInGame(true);
        NewSnakeElem->SnakeOwner = this;
        int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
        
        if (ElemIndex == 0)
        {
            NewSnakeElem->SetFirstElementType();
            
        }
    }
    
}

void ASnakeBase::RemoveSnakeElement()
{
    int32 ElementsLoss = FMath::RandRange(1, 3);
    for (int32 i = 0; i < ElementsLoss; i++) {
        SnakeElements.Pop();
    }
}

void ASnakeBase::Move()
{
    FVector MovementVector(0.f, 0.f, 0.f);
    
    switch(LastMovementDirection)
    {
        case EMovementDirection::UP:
            MovementVector.X += ElementSize;
            break;
        case EMovementDirection::DOWN:
            MovementVector.X -= ElementSize;
            break;
        case EMovementDirection::LEFT:
            MovementVector.Y += ElementSize;
            break;
        case EMovementDirection::RIGHT:
            MovementVector.Y -= ElementSize;
            break;
    }
    //AddActorWorldOffset(MovementVector);
    SnakeElements[0]->ToggleCollision();
    
    for (int i = SnakeElements.Num() - 1; i > 0; i--)
    {
        auto CurrentElement = SnakeElements[i];
        CurrentElement->SetActorHiddenInGame(false);
        auto PrevElement = SnakeElements[i - 1];
        FVector PrevLocation = PrevElement->GetActorLocation();
        CurrentElement->SetActorLocation(PrevLocation);
    }
    
    SnakeElements[0]->SetActorHiddenInGame(false);
    
    SnakeElements[0]->AddActorWorldOffset(MovementVector);
    
    SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
    if (IsValid(OverlappedElement))
    {
        int32 ElemIndex;
        SnakeElements.Find(OverlappedElement, ElemIndex);
        bool bIsFirst = ElemIndex == 0;
        IInteractable* InteractableInterface = Cast<IInteractable>(Other);
        if (InteractableInterface)
        {
            InteractableInterface->Interact(this, bIsFirst);
        }
    }
}
