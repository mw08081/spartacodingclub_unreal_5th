# 사전캠프

#### 25.07.14
- To Do List
  - [x] github 정리 및 블로그용 레포지토리 생성
  - [ ] 나에게 필요한 강의 점검
- Today I Learned
  - 사전강의는 필요한 부분만 수강하기로 .. 필요한 부분을 정리해보자 
#### 25.07.15
- x

#### 25.07.16
- To Do List 
  - [ ] c++ 강의 수강
  - [ ] 강의 진척도 파악하기
- Today I Learned
  - 개인사정으로 인해 강의 수강이 어려웠음...

#### 25.07.17
- To Do List 
  - [x] 사전캠프 퀘스트: 캐릭터생성
  - [ ] 사전캠프 퀘스트: 인터렉션 구현
- Today I Learned
  - 오랜만에 언리얼 프로젝트를 처움부터 다시 구성
  - 나만의 커스텀 캐릭터를 위한 c++ 케릭터클래스를 작성하고 리페런팅을 통해 케릭터를 생성해봄

#### 25.07.18
- To Do List 
  - [x] 사전캠프 퀘스트: 인터렉션 구현
- Today I Learned
  - 상속을 통한 InteractableItem Class 구현 및 Interact함수 오버라이딩
  - 벡터의 외적을 통한 문과 플레이어간의 위치 관계 판별
  - 캐릭터의 스켈레탈 메쉬 소켓에 무기 부착  
  ![GIF 2025-07-18 오후 4-51-44](https://github.com/user-attachments/assets/2e8531ca-de98-403d-8d70-cedda96238d5)
  ![GIF 2025-07-18 오후 4-52-14](https://github.com/user-attachments/assets/6a9e3958-e8a5-4cde-b705-3e265fc511fa)
  ```c++

  // InteractableItem.h
  class SPARTAPRECAMP_API AInteractableActor : public AActor
  {
  public:
      virtual void Interact();
  };

  // Door.h
  class SPARTAPRECAMP_API ADoor : public AInteractableActor
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
          FVector CrossRes = FVector::CrossProduct(AVector, BVector);
          IsPositiveOpenDirection = CrossRes.Z < 0;
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
