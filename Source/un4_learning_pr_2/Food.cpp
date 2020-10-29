// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "DietFood.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    
    StepSize = 50.f;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
    if (bIsHead)
    {
        auto Snake = Cast<ASnakeBase>(Interactor);
        if (IsValid(Snake))
        {
            Snake->AddSnakeElement();
            Destroy();
            
            /* 8 is a magic number for the amount of quares of StepSize there are in the field
              up, down, left and right of the 0.0 coordinate */
            
            GetWorld()->SpawnActor<AFood>(FoodClass, GetRandomTransform());
            
            if (IsDietTime())
            {
                GetWorld()->SpawnActor<ADietFood>(DietFoodClass, GetRandomTransform());
            }
            
 
        }
    }
}


bool AFood::IsDietTime()
{
    int32 RandNum = FMath::RandRange(1, 4);
    
    if (RandNum == 2) { return true; }
    return false;
}


FTransform AFood::GetRandomTransform()
{
    float RandnX = FMath::RandRange(-8.f, 8.f) * StepSize;
    float RandnY = FMath::RandRange(-8.f, 8.f) * StepSize;
    FVector NewLocation(RandnX, RandnY, 0);
    FTransform NewTransform(NewLocation);
    
    return NewTransform;
}
