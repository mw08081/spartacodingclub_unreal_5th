# 사전캠프

## 중요한 가르침
- [25.08.11.](https://github.com/mw08081/spartacodingclub_unreal_5th/blob/main/README.md#250811)

### 25.11.26
- To Do List
  - [x] 코드카타
  - [x] 4-4 완강 
- Today I Learned
  - Server Init Function
    - AGameMode: OnPreLogin(), OnPostLogin(), Login(), StartPlay()
    - APlayerController: PostNetInit(), OnActorChannelOpen(), PostInitializeComponents()
  - 네트워크 연결 단위
    - Connection: NetDriver가 관리.(서버는 ClientConnection을 가지고 클라이언트는 ServerConnection 을 갖음)
    - Channel: NetConnection 아래에서 리플리케이트 되는 단위? -> ActorChannel, ControllChannel ...etc
    - Packet
    - Bunch
    

### 25.11.25
- To Do List
  - [x] 코드카타
  - [x] 4-3 완강 
- Today I Learned
  - Net Connection + NetDriver
    - Net Connection이 연결되면 NetDirver가 생성
    - 서버에는 ClientConnection이 TArray<>형태로 저장되고, 클라이언트는 ServerConnection 생성된다(ServerConnection == nullptr -> Server)
  - NetRole
    - 복제된 곳에 롤과 생성된 곳의 롤이 두가지 존재
    - 서버에서 생성된 경우 Authority <-> Autonomous Proxy
    - 다른 클라이언트 입장에서는 Authority <-> Simulated Proxy

### 25.10.02
- To Do List
  - [x] 코드카타
- Today I Learned
    - 스폰 룰(Spawn Collision Handling Method)
      ```c++
      FVector SpawnLocation = ...; // 원하는 스폰 위치
      FRotator SpawnRotation = ...; // 원하는 스폰 회전
      
      FActorSpawnParameters SpawnParams;
      SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; 
      // 충돌이 있으면 위치를 조정하되, 가능하지 않으면 그래도 스폰
      // 또는 ESpawnActorCollisionHandlingMethod::AlwaysSpawn, ESpawnActorCollisionHandlingMethod::FailIfColliding 등 선택 가능
      
      // 실제 스폰 시도
      ABP_AIBase_C* SpawnedActor = GetWorld()->SpawnActor<ABP_AIBase_C>(BP_AIBaseClass, SpawnLocation, SpawnRotation, SpawnParams);
      
      if (!SpawnedActor)
      {
          UE_LOG(LogTemp, Warning, TEXT("Failed to spawn BP_AIBase_C at location %s"), *SpawnLocation.ToString());
      }
      ```
      스폰 룰 옵션
      - AlwaysSpawn: 무조건 스폰, 충돌 무시 (주의 필요)
      - AdjustIfPossibleButAlwaysSpawn: 충돌 위치가 있으면 위치 조정 시도, 그래도 안되면 무조건 스폰
      - AdjustIfPossibleButDontSpawnIfColliding: 충돌 시 위치 조정 후 실패 시 스폰 안함
      - DontSpawnIfColliding: 충돌 시 스폰 안함


### 25.10.01
- To Do List
  - [x] 코드카타
- Today I Learned
    - 에라토스테네스 체의 이면  
      일단 오늘의 주인공을 소개한다  
      ```c++
      bool isPrime(long long num) {
          if (num < 2) return false;
          for (long long i = 2; i * i <= num; i++) {
              if (num % i == 0) return false;
          }
          return true;
      }
      ```  
      소수와 관련된 문제는 항상 에라토스테네스의 체를 사용했다. 하지만 [이 문제](https://school.programmers.co.kr/learn/courses/30/lessons/92335#)는 달랐다.  
      에라토스테네스의 체는 반복적으로 소수를 판별하는데 유용하다. 반면 이 문제는 최대 1111111111111(13자리, 797161의 3진법) 까지 소수인지 구분해야했다.  
  
      에라토스테네스의 체를 아무런 생각없이 사용했고, 1111111111111까지 소수를 구하려고 하니 시간초과가 났다. 메모리도 부족했다.  
      결과적으로 1111111111111와 같이 한번만 이 수가 소수인지 아닌지를 판별하는 경우에는 위의 코드를 사용하는게 더 나을 수도 있다는 뜻이다(메모리나 시간적 측면에서)  
  
      이를 고려해서 앞으로는 직접 소수를 구하는 방법과 에라토스테네스의 체를 이용한 방법 두가지를 고려해보자


### 25.09.30
- To Do List
  - [x] 코드카타
- Today I Learned
    - <numeric> 헤더에 있는 accumulate함수의 세번째 매개변수 타입을 조정하면, 리턴값도 변경된다
      ```c++
      double <- accumulate(it, it, 0) / (double)it.size();
      double <- accumulate(it, it, 0.0) / it.size();        // *****
      ```


### 25.09.29
- To Do List
  - [x] 코드카타
- Today I Learned
    - 스켈레탈 메시 Hit Bone을 이용한 피격 부위 -> 스켈레탈 메시를 감싸는 캡슐콜라이더(루트콜라이더)와 총알의 콜리젼을 제거해줄 필요가 있음
      ```c++
      if (Hit.BoneName.ToString().StartsWith("Head")) {
      	Damage *= 1.2f;
      }
      else if (Hit.BoneName.ToString().StartsWith("Spine")) {
      	Damage *= 0.7f;
      }
      else {
      	Damage *= 0.4f;
      }
      ```

      
### 25.09.19
- To Do List
  - [x] 코드카타
- Today I Learned
    - 올림, 내림, 반올림 in `#include <cmath>`  
      올림: `ceil(value)`, 내림: `floor(value)`, 반올림: `round(value)`


### 25.09.17
- To Do List
  - [x] 코드카타
- Today I Learned
    - How to split string that contains space
      ```c++
      #include <sstream>

      // input: Enter uid1234 Muzi
      stringstream ss(input)
      string cmd, uid, nickname;

      ss >> cmd >> uid >> nickname;

      cout << cmd << " " << uid << " " << nickname << '\n';  // Enter uid1234 Muzi

      // 만약 닉네임 부분이 없는 입력이라면 nickname은 공백으로 처리된다.
      ```
  - string + string 의 속도 차이
    ```c++
    string res = m[e.second];
    res += "님이 ";
    if(e.first == "Enter") res += "들어왔습니다.";
    else if(e.first == "Leave") res += "나갔습니다.";

    answer.push_back(res);
    ```
    vs
    ```c++
    string action;
    if(e.first == "Enter") action = "들어왔습니다.";
    else if(e.first == "Leave") action = "나갔습니다.";

    answer.push_back(m[e.second] + "님이 " + action);
    ```
    <img width="357" height="112" alt="image" src="https://github.com/user-attachments/assets/4fa7d4a9-e71c-4524-8e10-1a691035bd51" />

    
### 25.09.18
- To Do List
  - [x] 코드카타
- Today I Learned
    - 나머지 연산
      `(a + b) % k` == `(a % k + b % k) % k`


### 25.09.15
- To Do List
  - [x] 코드카타
- Today I Learned
    - How to sort unordered_map using value
      ```c++
      vector<pair<int, int>> v(m.begin(), m.end());
      sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
          return a.second > b.second;
      });
      ```
  - How to rotate vector
    ```c++
    rotate(s.begin(), s.begin()+1, s.end());
    ```


### 25.09.22
- To Do List
  - [x] 코드카타
  - [x] sparta unreal c++ 강의 완강 
- Today I Learned
    - 언리얼 액터 라이프 사이클
      ```c++
      virtual void PostInitializeComponents() override;
      virtual void BeginPlay() override;
      virtual void Tick(float DeltaTime) override;
      virtual void Destroyed() override;
      virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
      ```
    - How to create custom Log Category name
      ```c++
      // "LogSparta"라는 이름으로 로그 카테고리 선언 in .h
      DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);
      
      // in .cpp
      DEFINE_LOG_CATEGORY(LogSparta);
      ```
      다른 소스코드에서도 해당 카테고리를 사용하고자한다면, 해당 해더파일을 임포트하면 됨.(그렇게 해서 카테고리만 모여있는 헤더파일을 만들 수 있다)

      
### 25.09.09
- To Do List
  - [ ] 코드카타
  - [x] BFS/DFS 알고리즘
- Today I Learned
    - BFS: Queue
    - DFS: Stack


### 25.09.08
- To Do List
  - [x] 코드카타
- Today I Learned
    - cpp stl: set.insert()
      `std::pair<iterator,bool> insert( const value_type& value );` : A pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a bool value set to true if and only if the insertion took place.
      ```c++
      unordered_set<string> s;
      
      s.insert("baekjoon");
      s.insert("programmers");
      // 삽입 실패
      auto res = s.insert("baekjoon");

      cout << res.second; // false
      ```
  - cpp algorithm: minmax_element  
      `std::pair<ForwardIt, ForwardIt> minmax_element( ForwardIt first, ForwardIt last );`: Finds the smallest and greatest element in the range [first, last).  
      ```c++
      // https://school.programmers.co.kr/learn/courses/30/lessons/12951
      auto res = minmax_element(vec.begin(),vec.end());
      return to_string(*res.first) + " " + to_string(*res.second);
      ```

      
### 25.08.28
- To Do List
  - [x] 코드카타
  - [x] ai 프로젝트 리펙토링
- Today I Learned
  - Unreal AI: 순찰  
    ![patrol](https://github.com/user-attachments/assets/a47c98ba-2dd5-4370-a158-969b7b6636f4)  
  - Unreal AI: 탐색과 추격  
    ![ai2](https://github.com/user-attachments/assets/4f3797bb-9b4b-4d8f-ba80-12a5995946d7)


### 25.08.27
- To Do List
  - [x] 코드카타
  - [x] cpp 3,4 과제
- Today I Learned
  - 템플릿 제한하기: 아래와 같이 템플릿을 제한할 수 있다
    ```c++
    // 템플릿 클래스 Inventory
    template <typename T, typename = std::enable_if_t<std::is_base_of<Item, T>::value>>
    class Inventory
    ```


### 25.08.22
- To Do List
  - [x] 코드카타
  - [x] cpp 사전강의 ~4주차
- Today I Learned
  - 알고리즘 유틸
    - string도 clear(), empty() 함수 호출이 가능하다.


### 25.08.20
- To Do List
  - [x] 코드카타
  - [ ] cpp 사전강의 ~4주차
- Today I Learned
  - 알고리즘 유틸
    - `#include <functional>`: `greater<T>()` 를 이용한 내림차순 정렬
    - `#include <numeric>`: `int accumulate(nums.begin(), nums.end(), 0);`
    - `#include <algoritm>`
      - `distance(Iterator, Iterator)`: 랜덤접근이 불가한 컨테이너(list)에서 Iterator간 간격을 반환함
      - `Iterator min_element`: 옛날에는 min_element 앞에 *를 붙이는 이유를 몰랐으나, 그것이 iterator였기때문이라고..


### 25.08.18
- To Do List
  - [x] 코드카타
  - [ ] cpp 사전강의 ~4주차
- Today I Learned
  - 알고리즘 유틸
    - `#include <string>`: `stio()`, `stoll()`, `to_string()`, `string.substr( *[0, i) )`
    - `#include <algorithm>`: `reverse(Iterator_start, Iterator_end)`, `find(Iterator_start, Iterator_end)`
  - `UBTTaskNode` vs `UBTService_BlackboardBase`: `UBTService_BlackboardBase`는 `UBTTaskNode`를 상속받고 추가로 `FBlackboardKeySelector`가 내부적으로 선언되어있다. 그래서 에디터에서 Blackborad키를 선택가능하며, 코드로는 `GetSelectedBlackboardKey()`를 호출할 수 있다
  - `UBTTaskNode` vs `UBTService`: Task는 말 그대로 어떤 동작이며, Service는 동작보다 지속적으로 모니터링하거나 값을 업데이트하는 것으로 사용된다
  - AI 관련 코드들
    ```c++
    // Task
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // Service 
    virtual void TickNode(UBhaviorTreeComponent& OwnerComp, unit8* NodeMemory, float DeltaSecons) override;

    #include "AIController.h"
    OwnerComp.GetAIOwner(); // return AAIController* 

    OwnerComp.GetAIOwner()->GetPawn();  // return AActor*
    OwnerComp.GetOwner(); // return AActor*

    #include "BehaviorTree/BlackboardComponent.h"
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent(); // return BlackboardComponent *

    FName SelectedBlackboardKeyName = GetSelectedBlackboardKey();
    BB->IsVectorValueSet(SelectedBlackboardKeyName); // return bool
    BB->SetValueAsVector(GetSelectedBlackboardKey(), FVector); //return void
    ```


### 25.08.19
- To Do List
  - [x] 코드카타
  - [ ] cpp 사전강의 ~4주차
- Today I Learned
  - STL: map, set
    - `bool map.insert({key, value})`, `Iterator map.find(key)`
    - `pair<Iterator, bool> set.insert(value)`, `Iterator set.find(value)`


### 25.08.14
- To Do List
  - [x] 프로그래머스 2문제
  - [x] 알고리즘 강의 ~2주차
  - [ ] cpp 사전강의 ~4주차
- Today I Learned
  - cpp stl에 관하여
    - cpp `map`은 '레드 블랙 트리'를 이용하기에 삽입시 정렬로 인해 `O(logN)`의 시간이 계속 소요된다. 정렬이 필요없다면 `unordered_map`을 사용하여 hash기반의 O(1)의 힘을 느껴보자
    - `map.find()`, `map.insert()` etc...
      ```c++
      unordered_map<string, int> map;

      map['a'] = 65;  // 현재로써 중복되지 않아, 삽입
      map['a'] = 97;  // 중복된 키에 대해 값 교채

      map.append(make_pair('b', 66)); // return true
      map.append({'b', 98}); // return false -> 중복값에 대해서 삽입 실패를 반환
      ```
    - vector vs list vs deque: vector-> 전방삽입 x, 임의접근이 빠름 / list-> 전방삽입 o, 임의접근 x / deque-> 전방삽입 o, 임의접근 다소 느림 (상황에 맞춰 사용)
  
   
### 25.08.11
- To Do List
  - [x] 본캠프 5일차 과제(지난주 해결하지 못한 부분은 클래스를 다시 만드니까 됐다.. 하..)
- Today I Learned
  - SweepMutilByChannel에 대한 깊은 이해  
    SweepMultiByChannel은 단순히 해당 범위(Start~End)를 스캔하여 다수의 액터를 검출한다고 알고있었다.  
    하지만 실제로는 Sweep에 사용되는 도형(또는 라인)이 해당 트레이스 채널에 대해서 overlap인경우 투과되고 block인 경우 투과되지 않으며, 트레이스범위와 block을 만나 sweep이 멈추는 범위 중 작은 범위에서 조건에 맞는 액터를 검출한다.  
    ```c++
    FCollisionShape CollsionCapsule = FCollisionShape::MakeCapsule(35, 60);

    TArray<FHitResult> HitResults;
    FVector Start = GetActorLocation();
    FVector End = Start + Camera->GetForwardVector() * 150.0f;
    
    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults, 
        Start, 
        End,
        FQuat::Identity,
        ECC_GameTraceChannel1,
        CollsionCapsule
    );
    ```
    <img width="535" height="350" alt="TraceMultiMyChannel" src="https://github.com/user-attachments/assets/adc9517c-5237-427e-9cc4-beb5caf00031" />
    
    (왼쪽위에서부터 TraceChannel이 B,B,B,B, O,O,B,O이다- B:Block, O:Overlap)
  - Fab에서 가져온 에셋이 `SetSimulatePhysics(true);`가 적용이 안된다..
    ```(Trying to simulate physics on ''/Game/ThirdPerson/Maps/ThirdPersonMap.ThirdPersonMap:PersistentLevel.StaticMeshActor_UAID_D8BBC14F7090358402_1140807227.StaticMeshComponent0'' but it has ComplexAsSimple collision)```  
    추론하건데 콜리젼이 너무 복잡해서 물리계산을 할 수 없다는 뜻같다.. 추가적으로 이상한 부분은 StaticMesh에서 ShowSimpleCollison을 체크하면 이상하게 Complex Collsion이 같이 보인다는 점이다.  
    <img width="132" height="138" alt="image" src="https://github.com/user-attachments/assets/36d94451-c26f-4d5f-addf-bcff4b30153e" />  
    이 부분은 `Use Complex Collsion As Simple Collision`대신 `Use Simple Collsion As Complex Collision`을 사용하니 해결됐다  
    <img width="535" height="350" alt="image" src="https://github.com/user-attachments/assets/56fb8ab8-70df-4964-87c1-fd5107625884" />
  - 컴파일이 3초이상 걸리는 작업에 대해서 블루프린트 노티파이와 같이 금방 컴파일 할 수 있는 수단을 이용하도록 하자
  - 언리얼에서 TraceChannel을 Visibility를 사용하기보다, 커스텀으로 하나 만드는게 좋다(소리가 영향이 된다.. 나중에)
  
  
### 25.08.08
- To Do List
  - [ ] 본캠프 5일차 과제
- Today I Learned
  - `Actor->Tags`는 TArray<T>로 되어있다
  - 갑자기 tick이 호출되지 않는다.. 미칙ㅆ당ㄴㄹ
 
    
### 25.08.07
- To Do List
  - [x] 본캠프 4일차 과제
  - [x] cpp 사전강의 4주차 듣고 실습해보기
- Today I Learned
  - Character의 Use Controller Rotaion Yaw를 끄면 컨트롤러의 회전이 폰의 Yaw(상하축) 회전에 영향을 주지 않는다
  - Cahracter Movement의 Orient Rotaion to Movement를 켜면 케릭터의 회전을 wasd로 조작할 수 있다
  - Behavior Tree: Sequnece- 전부 다 성공해야 True
  - Behavior Tree: Selector- 하나라도 실패하면 False

    
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
### 25.07.30
- To Do List
  - [ ] cpp 사전강의 4-1
- Today I Learned
  - 언리얼 ai를 위한 BlackBoard(메모리)와 BehaviorTree(프로그램카운터)가 존재

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


### 25.07.21
- To Do List
  - [ ] 사전캠프 c++ 강의 3-1강 프리뷰
- Today I Learned
  - Basis 프로젝트 빌드간 오류를 해결하기위해.. 열심히 구글링하였으나 아직 해결하지 못함.. -> UE5.4를 설치해서 해결

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
