# C-Class-to-Unreal-Engine-BluePrint
basic practice for Unreal Engine Implementation

# Purpose
- 간단한 기능을 가진 액터클래스를 C++로 만들어 본 후, 언리얼 엔진에 블루프린터로 상속시켜보는 실습

# MyActor

- 10번 랜덤하게 이동하면서, 이동한 위치와 이동한 거리를 출력
- 각 이동마다 50% 확률의 이벤트 발생
- 10번의 이동이 완료된 후, 이동한 거리와 이벤트 발생횟수를 로그로 출력
  
  <img width="363" height="297" alt="image" src="https://github.com/user-attachments/assets/1b5813a4-16fd-43fc-82da-2f65e7d3ae56" />

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

# 로그 결과

<img width="914" height="420" alt="image" src="https://github.com/user-attachments/assets/a734f070-ae14-4642-acb7-b6d5e33f1962" />

# 추가 기능

## 블루프린트로 만들기

1. Content Drawer에서 마우스 우클릭하여 새로운 블루프린트 만들기 클릭
2. 부모클래스를 만들었던 `MyActor`로 설정
<img width="935" height="692" alt="image" src="https://github.com/user-attachments/assets/8755087b-5270-4c87-be1b-002c8582483d" />

3. 멤버변수는 디테일 패널에서 확인 가능
<img width="572" height="781" alt="image" src="https://github.com/user-attachments/assets/37804cb1-8ea3-45fc-809f-22c4fc442c65" />

4. 멤버함수는 EventGraph에서 우클릭하여 노드 추가시 확인 가능
<img width="1195" height="309" alt="image" src="https://github.com/user-attachments/assets/8042a6f6-61d1-40b6-9e6f-133fc539f46d" />

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
<img width="396" height="195" alt="image" src="https://github.com/user-attachments/assets/7b39bfb8-c4b6-4e2f-8cda-d56a213a34d1" />

### Sphere Mesh 추가해보기

```cpp
static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));	// 기본 sphere mesh 경로
if (SphereMesh.Succeeded())
{
	MeshComponent->SetStaticMesh(SphereMesh.Object);
}
```
<img width="600" height="151" alt="image" src="https://github.com/user-attachments/assets/d31bc052-0eb4-4dc4-b3ca-063583977f78" />

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
  <img width="562" height="473" alt="image" src="https://github.com/user-attachments/assets/30bc7e88-4d93-4807-8263-0899798cf40a" />

- `move()`가 끝나고 `PlaySuccessSound()`를 호출하여 음악이 들리게 하였다.
