// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
class AFood;

UENUM()
enum class EMovementDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

UCLASS()
class UN4_LEARNING_PR_2_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASnakeElementBase> SnakeElementClass;
    
    UPROPERTY()
    TArray<ASnakeElementBase*> SnakeElements;
    
    UPROPERTY(EditDefaultsOnly)
    float ElementSize;
    
    UPROPERTY()
    EMovementDirection LastMovementDirection;
    
    UPROPERTY(EditDefaultsOnly)
    float MovementSpeed;
    
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    void AddSnakeElement(int ElementsNum = 1);
    void RemoveSnakeElement();
    
    void Move();
    
    UFUNCTION()
    void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

};
