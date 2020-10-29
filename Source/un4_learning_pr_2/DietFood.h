// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "DietFood.generated.h"

/**
 * 
 */
UCLASS()
class UN4_LEARNING_PR_2_API ADietFood : public AFood
{
	GENERATED_BODY()
	
public:
    virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
