#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector2D.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

#include "MyActor.generated.h"

UCLASS()
class ASSIGNMENT5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void move();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	int32 step();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SuccessSound;

	float distance(FVector2D first, FVector2D second);
	int32 createEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 Custom_Input; 

private:

	FVector2D start;
	int32 evCnt;
	float totDist;
	void PlaySuccessSound();
};
