# 사전캠프

### 25.07.14
- To Do List
  - [x] github 정리 및 블로그용 레포지토리 생성
  - [ ] 나에게 필요한 강의 점검
- Today I Learned
  - 사전강의는 필요한 부분만 수강하기로 .. 필요한 부분을 정리해보자

### 25.07.15
- x

### 25.07.16
- To Do List 
  - [ ] c++ 강의 수강
  - [ ] 강의 진척도 파악하기
- Today I Learned
  - 개인사정으로 인해 강의 수강이 어려웠음...

### 25.07.17
- To Do List 
  - [x] 사전캠프 퀘스트: 캐릭터생성
  - [ ] 사전캠프 퀘스트: 인터렉션 구현
- Today I Learned
  - 오랜만에 언리얼 프로젝트를 처움부터 다시 구성
  - 나만의 커스텀 캐릭터를 위한 c++ 케릭터클래스를 작성하고 리페런팅을 통해 케릭터를 생성해봄
    ```C++
    // MyCharacter.cpp
    void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
    {
        Super::SetupPlayerInputComponent(PlayerInputComponent);
        
        PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
        PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
        
        PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &APawn::AddControllerPitchInput);
        PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &APawn::AddControllerYawInput);
        
        PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction(TEXT("Interact") , EInputEvent::IE_Pressed, this, &AMyCharacter::Interact);
    }
    
    void AMyCharacter::MoveForward(float Value)
    {
        AddMovementInput(GetActorForwardVector() * Value);
    }
    
    void AMyCharacter::MoveRight(float Value)
    {
        AddMovementInput(GetActorRightVector() * Value);
    }
    
    void AMyCharacter::Interact()
    {
        FCollisionShape CollisionShape = FCollisionShape::MakeSphere(50.0f); // 반지름 50 구체
        FHitResult HitResult;
        FVector Start = GetActorLocation();
        FVector End = Start + GetActorForwardVector() * 500.0f;
  
        // sweeping
        bool bHit = GetWorld()->SweepSingleByChannel(
            HitResult,
            Start,
            End,
            FQuat::Identity,
            ECC_Visibility,
            CollisionShape
        );
        
        if (bHit && HitResult.GetActor())
        {
            // HitResult 정보 활용
            if (HitResult.GetActor()->ActorHasTag("interactable")) {
                UE_LOG(LogTemp, Display, TEXT("Interaction !!"));
                AInteractableItem* Interactable = Cast<AInteractableItem>(HitResult.GetActor());
                Interactable->Interact();
            }
        }
    }
    ```

### 25.07.18
- To Do List 
  - [x] 사전캠프 퀘스트: 아이템 인터렉션 구현
- Today I Learned
  - 상속을 통한 InteractableItem Class 구현 및 Interact함수 오버라이딩
  - 벡터의 외적을 통한 문과 플레이어간의 위치 관계 판별
  - 캐릭터의 스켈레탈 메쉬 소켓에 무기 부착  
  ![GIF 2025-07-18 오후 4-51-44](https://github.com/user-attachments/assets/2e8531ca-de98-403d-8d70-cedda96238d5)
  ![GIF 2025-07-18 오후 4-52-14](https://github.com/user-attachments/assets/6a9e3958-e8a5-4cde-b705-3e265fc511fa)
    ```c++
  
    // InteractableItem.h
    class SPARTAPRECAMP_API AInteractableItem : public AActor
    {
    public:
        virtual void Interact();
    };
  
    // Door.h
    class SPARTAPRECAMP_API ADoor : public AInteractableItem
    {
    public:
        virtual void Interact() override;
    }
  
    // Door.cpp
    void ADoor::Interact()
    {
        Super::Interact();
  
        IsInteracted = true;
        if (IsOpen == false) {
            APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
            if (Pawn == nullptr) return;
  
            //벡터의 외적을 통한 위치관계 판별
            FVector AVector = GetActorRightVector();
            FVector BVector = (Pawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            FVector CrossVec = FVector::CrossProduct(AVector, BVector);
            IsPositiveOpenDirection = CrossVec.Z < 0;
        }
    }
  
    void AWeapon::Interact()
    {
        ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
        if (Character) {
            USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
            if (CharacterMesh)
            {
                FName HandSocket(TEXT("hand_rSocket"));
                AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
            }
        }
    }
    ```

### 25.07.21
- To Do List
  - [ ] 사전캠프 c++ 강의 3-1강 프리뷰
- Today I Learned
  - Basis 프로젝트 빌드간 오류를 해결하기위해.. 열심히 구글링하였으나 아직 해결하지 못함.. -> UE5.4를 설치해서 해결

### 25.07.22
- To Do List
  - [ ] 사전캠프 c++ 강의 3-1강 구현
- Today I Learned
  - 여전히 빌드오류.. 해결하지 못하고있음 -> 언리얼엔진 제거 후 경로를 지정하여 재설치(‪C:\Program Files\Epic Games\UE_5.4)

### 25.07.23
- To Do List
  - [x] 사전캠프 c++ 강의 3-1강 구현
- Today I Learned
  - How to bind EnhancedInputAction to EnhancedInputComponent at Unreal Engine5
    ```c++
    void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputController)
    {
    	Super::SetupPlayerInputComponent(PlayerInputController);
    
    	if (UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent>(PlayerInputController))
    	{
    		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
    		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Look);
    		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBase::Fire);
    		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerBase::Zoom);
    	}
    }
    ```
  - WeaponeBase.cpp
    ```c++
    void AWeaponBase::Fire()
    {
      // 애니메이션 몽타주도 Spawn()이후에 출력하는게 나을 듯
    	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
    	if (IsValid(AnimInstance) && IsValid(FireAnimMontage)) {
    		AnimInstance->Montage_Play(FireAnimMontage);
    	}
    
    	if (IsValid(BulletClass)) {
    		FRotator SpawnRotation = MuzzleOffset->GetComponentRotation();
    		FVector SpawnLocation = MuzzleOffset->GetComponentLocation();
    
    		FActorSpawnParameters SpawnParams;
    		SpawnParams.Owner = this;
    
    		// 왜 APlayerBase로 캐스팅해야돼? Enmey가 총을 쏠 수도 있잖아
    		APlayerBase* Owner = Cast<APlayerBase>(GetOwner());
    		if (!IsValid(Owner)) return;
    
    		APlayerController* PlayerController = Cast<APlayerController>(Owner->GetController());
    		if (!IsValid(PlayerController)) return;
    
    		int32 x, y;
    		PlayerController->GetViewportSize(x, y);
  
        // WorldCenter의 존재 이유: ??? 디버깅 필요 (WorldFront * 10000 더해지기전 값)
    		FVector WorldCenter;
    		FVector WorldFront;
    		PlayerController->DeprojectScreenPositionToWorld(x * 0.5f, y * 0.5f, WorldCenter, WorldFront);
  
        // 존재의 이유를 확인
        UE_LOG(LogTemp, Display, TEXT("World Center: %s"), *WorldCenter.ToCompactString());
    
    		WorldCenter += WorldFront * 10000;
    		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, WorldCenter);
    
    		GetWorld()->SpawnActor<ABulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
    	}
    }
    ```
  - `PlayerController->DeprojectScreenPositionToWorld(~);` 를 활용하는 이유는 `Weapon->GetForwardVector()`를 이용해도 되지만, 해당 벡터가 정확하게 화면 중앙을 타겟팅할 것이라는 보장이 없기때문이다. 추가적으로 Deprojection을 통해 화면의 좌표를 3D월드의 좌표로 확인할 수 있다.
  - `FRotator UKismetMathLibrary::FindLookAtRotation(
    const FVector& Start,
    const FVector& Target
);`는 FVector(Target - Start) 를 Rotator값으로 변경해준다. 실제로 (Target - Start).Rotator 와 동일한 값을 출력한다.. 그렇다면 왜 있는걸까
    ```c++
    FVector Start;
    FVector Target;
    
    FRotator rot = UKismetMathLibrary::FindLookAtRotation(Start, Target);
    FRotator rot2 = (Target - Start).Rotator
    // rot == rot2
    ```
### 25.07.24
- To Do List
  - [x] 사전강의 cpp 3-2 강의
  - [x] 사전강의 cpp 3-3 강의
  - [x] 사전강의 cpp 3-4 강의
- Today I Learned
  - Input Mapping Context 의 WASD 설정
    ```bash
    // y축기준
    W -> Swizzle Input Axis Values
    S -> Swizzle Input Axis Values, Negate
    A -> Negate
    D -> None
    ```
    <img width="980" height="139" alt="image" src="https://github.com/user-attachments/assets/1f588410-ab9e-415a-a2de-5f5778c2f7b7" />
  - Input Mapping Context Bind At CPP
    ```c++
    // PlayerBase.h
    UPROPERTY(EditDefaultsOnly)
    class UInputMappingContext* InputMappingContext;
    
    // PlayerBase.cpp
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (IsValid(PlayerController)) {
    	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
    	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player)) {
    		Subsystem->AddMappingContext(InputMappingContext, 0);
    	}
    }
    ```
    
### 25.07.25
- 병원일정

### 25.07.28
- To Do List
  - [x] 사전강의 cpp 3주차 구현
  - [ ] UMG 값 바인딩 실패 .. 
- Today I Learned
  - 블루프린트로 UMG를 생성하기위한 바인딩 옵션: `UPROPERTY(meta = (BindWidget))`
    ```c++
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* PB_HPGauge;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_HPPercent;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_KillCount;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_StageLv;
    ```
  - FString, FText차이: FText는 UMG에 보통 사용되고, 대부분의 경우 FString이 사용된다고..한다
    ```c++
    int32 Val = 30;

    // 변수값 활용
    FString::FromInt(Val);            // FString
    FString::Printf(TEXT("%d"), Val); // FString

    // 리터럴 상수 활용
    FString(TEXT("Literal Constant")); // FSTring

    // FText 변수 생성
    FText::FromString(FString str);     // FText    
    ```
  
### 25.07.29
- To Do List
  - [x] UMG 연결(플레이어 호출, not tick)   
  - [x] 3주차- Bullet Event Binding: OnHit
- Today I Learned
  - UMG를 연결 완료 후, Player -> GameMode -> UMG 순으로 데이터 갱신(원래 GameMode에서 Widget을 가지고 있지 않는다.. 해당 레퍼런스는 로컬게임이니까 대충 한듯으로 보인다)
    ```c++
    // PlayerBase.cpp
    void APlayerBase::IncreaseKillCount()
    {
    	Super::IncreaseKillCount();
    
    	KillCount += 1;
    	CurGameMode->SetPlayerKillCount(KillCount);
    }

    // BasisDefaultGameMode.cpp
    void ABasisDefaultGameMode::SetPlayerKillCount(int32 KillCount)
    {
    	PlayerKillCount = KillCount;
    	Cast<UMainHUD>(MainHUD)->SetKillCount(PlayerKillCount);
    }

    // UMainHUD.cpp
    void UMainHUD::SetKillCount(int32 Value)
    {
    	if (IsValid(Txt_KillCount))
    	{
    		Txt_KillCount->SetText(FText::FromString(FString::Printf(TEXT("Kill: %d"), Value)));
    	}
    }
    ```
    ![GIF 2025-07-29 오후 5-48-15](https://github.com/user-attachments/assets/d136e92b-d243-4d17-a28c-3b3ee5529275)

  - Bullet의 OnHit를 Buttet.StaticMeshComponent의 Hit Event로 등록하는 방법은 다음과 같다
    ```c++
    StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
    ```
    ![GIF 2025-07-29 오후 5-48-41](https://github.com/user-attachments/assets/570332d0-0854-4c80-9462-c4ef6c67e4fc)  
    (나의 체력이 줄어드는 것은 보여주기 위해 임시로 연결했기때문.. )
### 25.07.30
- To Do List
  - [ ] cpp 사전강의 4-1
- Today I Learned
  - 언리얼 ai를 위한 BlackBoard(메모리)와 BehaviorTree(프로그램카운터)가 존재
    
### 25.08.06
- To Do List
  - [x] 3일차 과제를 cpp로 해결해보자
- Today I Learned
  - InputMappingContext에 InputAction을 등록할때, Trigger를 등록하지않으면 여러번 눌리는것 같다.. 버그인가?
  - IsA연산자: 비교클래스 또는 비교클래스의 하위클래스일 경우 true를 반환
    ```c++
    AActor* HitActor = HitResult.GetActor();

    // HitActor가 Weapon 클래스로부터 파생된 클래스 또는 Weapon클래스인 경우 True를 반환
    if (HitActor->IsA(AWeapon::StaticClass()))
    {
        Weapon = Cast<AWeapon>(HitActor);
        HitActor->SetOwner(this);
    }
    ```
  - AWeapon을 상속받아 Gun을 만들었다. 해당 총기의 Shot,Reload,CoolDown(Excute in Tick)함수를 추가  
    (총기별 탄약수와 배럴온도를 저장하려면 그냥 무기를 클래스로 저장하고, 습득하는 총기별로 성능을 에디터에서 변경해주면 된다)
    ```c++
    // Gun.h
    #include "CoreMinimal.h"
    #include "Interactable/Weapon.h"
    #include "Gun.generated.h"
    
    struct GunType
    {
    	FString Label;
    	int32 MaxAmmoCapacity;
    	int32 Damage;
    
    	GunType(FString InLabel, int32 InMaxAmmoCapacity, int32 InDamage)
    		: Label(InLabel), MaxAmmoCapacity(InMaxAmmoCapacity), Damage(InDamage)
    	{
    	}
    
    	GunType() 
    		: Label(""), MaxAmmoCapacity(0), Damage(0)
    	{
    	}
    };

    // 생략...
    
    //Gun.cpp
    void AGun::Shot()
    {
    	if (CurAmmoCount < 1) 
    	{
    		UE_LOG(LogTemp, Warning, TEXT("Out of ammo..."));
    		return;
    	}
    
    	if (CurBarrelTemp > 70)
    	{
    		UE_LOG(LogTemp, Warning, TEXT("Can't Fire(Cur Barrel State: %s(%f))"), *GetCurBarrelState(), CurBarrelTemp);
    		return;
    	}
    
    	CurAmmoCount -= 1;
    	CurBarrelTemp += 1;
    	UE_LOG(LogTemp, Display, TEXT("BBang(Cur Remain Ammo Count: %d, Cur Barrel State: %s(%f))"), CurAmmoCount, *GetCurBarrelState(), CurBarrelTemp);
    }
    
    void AGun::Reload()
    {
    	if (CurAmmoCount == MaxAmmoCapacity)
    	{
    		UE_LOG(LogTemp, Warning, TEXT("Already full ammo"));
    		return;
    	}
    
    	CurAmmoCount = MaxAmmoCapacity;
    	UE_LOG(LogTemp, Display, TEXT("Reload(Cur Remain Ammo Count: %d)"), CurAmmoCount);
    }
    
    /// <summary>
    /// Excute in Tick
    /// </summary>
    /// <param name="DeltaTime"></param>
    void AGun::CoolDown(float DeltaTime)
    {
    	CurBarrelTemp -= DeltaTime*100;
    	UE_LOG(LogTemp, Warning, TEXT("Cool Down ...(Cur Barrel State: %s(%f))"), *GetCurBarrelState(), CurBarrelTemp);
    
    	if (CurBarrelTemp < 16)
    	{
    		bIsInCoolDown = false;
    	}
    }
    
    void AGun::SwitchWeapon(int32 Weapon)
    {
    	UE_LOG(LogTemp, Display, TEXT("Switch Weapon :%s"), *GunTypeList[Weapon - 1].Label);
    
    	MaxAmmoCapacity = GunTypeList[Weapon - 1].MaxAmmoCapacity;
    	Damage = GunTypeList[Weapon - 1].Damage;
    
    	CurAmmoCount = MaxAmmoCapacity;
    	CurBarrelTemp = 15;
    }
    ```
    <img width="628" height="566" alt="image" src="https://github.com/user-attachments/assets/76f5d168-1119-44be-963d-ad9cce1e4ad9" />
    <img width="600" height="183" alt="image" src="https://github.com/user-attachments/assets/91025137-f8d7-4ed1-b7f9-64c559475f84" />

### 25.08.07
- To Do List
  - [x] 본캠프 4일차 과제
  - [x] cpp 사전강의 4주차 듣고 실습해보기
- Today I Learned
  - Character의 Use Controller Rotaion Yaw를 끄면 컨트롤러의 회전이 폰의 Yaw(상하축) 회전에 영향을 주지 않는다
  - Cahracter Movement의 Orient Rotaion to Movement를 켜면 케릭터의 회전을 wasd로 조작할 수 있다
  - Behavior Tree: Sequnece- 전부 다 성공해야 True
  - Behavior Tree: Selector- 하나라도 실패하면 False
  

### 25.08.08
- To Do List
  - [ ] 본캠프 5일차 과제
- Today I Learned
  - `Actor->Tags`는 TArray<T>로 되어있다
  - 갑자기 tick이 호출되지 않는다.. 미칙ㅆ당ㄴㄹ
