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
  - 여전히 빌드오류.. 해결하지 못하고있음 -> 언리얼엔진 제거 후 재설치
