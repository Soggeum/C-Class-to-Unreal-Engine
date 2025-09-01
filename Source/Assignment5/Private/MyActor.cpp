// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	start.X = 0;
	start.Y = 0;
	evCnt = 0;
	totDist = 0.0f;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Assignment5 Start!"));
	UE_LOG(LogTemp, Warning, TEXT("Start Position: (%f, %f)"), start.X, start.Y);
	move();
	UE_LOG(LogTemp, Warning, TEXT("Total Move Distance: %f"), totDist);
	UE_LOG(LogTemp, Warning, TEXT("Total Event Count: %d"), evCnt);
	PlaySuccessSound();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::move()
{
	for (int i = 0; i < 10; i++) {
		FVector2D dest = start;
		dest.X += step();
		dest.Y += step();
		float move_distance = distance(start, dest);

		UE_LOG(LogTemp, Warning, TEXT("%dth position : (%f, %f) / move distance: %f"), i + 1, dest.X, dest.Y, move_distance);
		start = dest;
		totDist += move_distance;
	}
}

int32 AMyActor::step()
{
	int32 RandomValue1 = FMath::RandRange(0, 1);
	int32 RandomValue2 = FMath::RandRange(0, 1);
	if (RandomValue2) {
		evCnt++;
		createEvent();
	}

	return RandomValue1;
}

float AMyActor::distance(FVector2D first, FVector2D second)
{
	float x = FMath::Square(first.X - second.X);
	float y = FMath::Square(first.Y - second.Y);
	
	return FMath::Sqrt(x + y);
}

int32 AMyActor::createEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Event Created!"));
	return 0;
}

void AMyActor::PlaySuccessSound()
{
	if (SuccessSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, SuccessSound, GetActorLocation());
	}
}