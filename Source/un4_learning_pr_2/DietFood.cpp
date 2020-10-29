// Fill out your copyright notice in the Description page of Project Settings.


#include "DietFood.h"
#include "Food.h"
#include "SnakeBase.h"

void ADietFood::Interact(AActor* Interactor, bool bIsHead)
{
   if (bIsHead)
   {
       auto Snake = Cast<ASnakeBase>(Interactor);
       if (IsValid(Snake))
       {
           Snake->RemoveSnakeElement();
           Destroy();
       }
   }
}
