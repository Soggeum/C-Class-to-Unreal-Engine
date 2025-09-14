# C-Class-to-Unreal-Engine-BluePrint
basic practice for Unreal Engine Implementation

# Purpose
- 간단한 기능을 가진 액터클래스를 C++로 만들어 본 후, 언리얼 엔진에 블루프린터로 상속시켜보는 실습

# MyActor

- 10번 랜덤하게 이동하면서, 이동한 위치와 이동한 거리를 출력
- 각 이동마다 50% 확률의 이벤트 발생
- 10번의 이동이 완료된 후, 이동한 거리와 이벤트 발생횟수를 로그로 출력
  
<img width="363" height="297" alt="image" src="https://github.com/user-attachments/assets/3ce5f990-4875-40f6-a893-ec376cec192e" />

# 로그 결과

<img width="932" height="514" alt="image" src="https://github.com/user-attachments/assets/999f1431-d001-40b1-a464-c54a903d7c80" />


# 언리얼 엔진 Reflection System

- 리플렉션은 `UObject`를 위한 운영체제 

- 언리얼 엔진 내부에서 동작하는 여러 모듈(가비지 컬렉터, 스크립트 시스템) 등은 모두 UObject 기반 
 
- 그러나 C++을 이용해 사용자가 정의한 타입들의 경우 엔진에서 알지 못하므로, 이를 위한 작업이 리플렉션
![](https://velog.velcdn.com/images/soggeum/post/d3ddd6b9-b75a-4266-9965-a5517a383b55/image.png)

## UHT 코드 생성기

- UHT는 C++ 컴파일러가 수행되기 되기 전에 동작하여 C++ 코드 내에서 메타 데이터를 얻고,  내부적으로 소스 코드를 생성

- 이 동작이 완료된 이후에 C++ 컴파일러가 수행되고 언리얼 엔진에서 UObject로 관리 가능

![](https://velog.velcdn.com/images/soggeum/post/0485de85-13fd-471e-9d56-fbe3b5758b8b/image.png)

## 핵심 매크로

![](https://velog.velcdn.com/images/soggeum/post/3622fe60-534b-4bea-ac8e-795840f8a268/image.png)

- 이러한 매크로를 통해 사용 가능하다

- Struct 사용 예시
 
```cpp
// FMyStructData.h (or within another .h)
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MyStructData.generated.h"

USTRUCT(BlueprintType) // 블루프린트에서 이 구조체를 타입으로 사용할 수 있도록 함
struct FMyStructData
{
    GENERATED_BODY() // UHT가 필요한 코드를 생성하도록 합니다.

public:
	// 멤버 변수를 property로 등록
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStructData")	
    int32 SampleInt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStructData")
    FString SampleString;

    FMyStructData() : SampleInt(0), SampleString(TEXT("Default")) {}
};
```

- Class 사용 예시

```cpp
UCLASS(Blueprintable, BlueprintType) // 블루프린트에서 생성 가능하고 타입으로 사용하게 함
class YOURPROJECT_API UMyReflectedObject : public UObject // UObject를 상속받습니다.
{
    GENERATED_BODY() // UHT가 필요한 코드를 생성하도록 합니다.

public:
    // ... Properties and Functions will go here ...
    UMyReflectedObject(); // Constructor
};
```
 
- 리플렉션 정리

![](https://velog.velcdn.com/images/soggeum/post/dfe297c5-2b70-4894-b7f5-b5a6e7d67662/image.png)


# UHT

- 언리얼 엔진에서 우리가 만든 C++ 클래스를 사용하려면 그에 맞게 UObject로 만들어줘야함
- 그 과정에서 필요한 것이 UHT 코드
```cpp
UCLASS()  // UHT
class ASSIGNMENT5_API AMyActor : public AActor
{
	GENERATED_BODY()  // UHT
	
public:	
	UFUNCTION(BlueprintCallable, Category = "Actions")  // UHT
	void move();

	float distance(FVector2D first, FVector2D second);

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariables")  // UHT
  int32 a;

private:
	FVector2D start;
```
- 먼저 UHT 코드를 넣어 해당 클래스가 Unreal Engine에서도 사용할 수 있게 설정해주고
- `UFUNCTION`, `UPROPERTY`를 통해서도 해당 함수, 변수가 에디터에서 어떻게 쓰일 것인지를 설정해준다
- 에디터에서 사용하려면 무조건 public으로 선언해야함
- 따라서 `move()`, `a`만 에디터에서 나타나며 사용할 수 있다


# 추가 기능

## 블루프린트로 만들기

1. Content Drawer에서 마우스 우클릭하여 새로운 블루프린트 만들기 클릭
2. 부모클래스를 만들었던 `MyActor`로 설정
<img width="463" height="355" alt="image" src="https://github.com/user-attachments/assets/0c41d81f-b5d0-4b4b-8ed8-372f1218bf72" />


3. 멤버변수는 디테일 패널에서 확인 가능
<img width="874" height="110" alt="image" src="https://github.com/user-attachments/assets/1a0682c6-808e-41cf-97b1-f2756ae41ed6" />
<img width="561" height="407" alt="image" src="https://github.com/user-attachments/assets/01e5f78e-c076-4597-b9bd-d1cc76de2271" />


4. 멤버함수는 EventGraph에서 우클릭하여 노드 추가시 확인 가능
<img width="1402" height="342" alt="image" src="https://github.com/user-attachments/assets/eb13dcfa-be76-49ea-ba87-e0a24c74c837" />



## parent class와 블루프린트 순서

- 부모클래스인 `MyActor`와 이 클래스를 상속받은 블루프린트 `BP_MyActor` 둘 다 `BeginPlay()`함수를 가짐
- 블루프린트의 `BeginPlay()`노드에 다른 함수들 연결시키면 먼저 부모클래스 `MyActor`가 실행이 되고 나서 그 다음에 블루프린트의 `BeginPlay()`가 시작
- 이와 같이 다른 대부분의 상황(overlap, hit..)에서도 먼저 부모가 먼저 실행이 되고 그 다음에 자식이 실행됨

## C++로 meshcomponent 추가해보기

- 헤더파일과 cpp 파일에 각각 아래와 같은 코드를 추가해준다
```cpp
// MyActor.hpp
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

// MyActor.cpp
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;	// 액터의 중심 컴포넌트로 지정
```

- 아래와 같이 `MyActor`클래스를 상속받은 블루프린트에서 `MeshComponent`를 확인할 수 있다
<img width="388" height="383" alt="image" src="https://github.com/user-attachments/assets/08d40a05-fdd3-41e8-9d57-13c2b0ce2dcc" />


### Sphere Mesh 추가해보기

```cpp
static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));	// 기본 sphere mesh 경로
if (SphereMesh.Succeeded())
{
	MeshComponent->SetStaticMesh(SphereMesh.Object);
}
```
<img width="1938" height="792" alt="image" src="https://github.com/user-attachments/assets/ffd31812-0ee9-4967-aca3-7b10510b0c42" />


## 동작 완료 후 sound 출력해보기

```cpp
// MyActor.hpp
public:
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SuccessSound;		// 음악

private:
	void PlaySuccessSound();		// 음악 재생 함수

// MyActor.cpp
void AMyActor::PlaySuccessSound()
{
	if (SuccessSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, SuccessSound, GetActorLocation());
	}
}
```
- SuccessSound를 UPROPERTY로 선언했기 때문에 에디터에서 음악을 설정해줄 수 있다
<img width="563" height="444" alt="image" src="https://github.com/user-attachments/assets/958b9ca6-ecd2-49b1-b029-adac72549dcf" />


- `move()`가 끝나고 `PlaySuccessSound()`를 호출하여 음악이 들리게 하였다.
