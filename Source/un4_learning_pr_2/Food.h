// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

class ADietFood;

UCLASS()
class UN4_LEARNING_PR_2_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* MeshComponent;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AFood> FoodClass;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ADietFood> DietFoodClass;
    
    float StepSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    virtual void Interact(AActor* Interactor, bool bIsHead) override;
    
    bool IsDietTime();
    FTransform GetRandomTransform();
};
