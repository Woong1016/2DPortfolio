#include "Framework.h"

Plane::Plane()
    : Quad(L"Textures/Shooting/airplane.png") // 부모 생성자 + 고정 인수
{
    // 생성과 동시에 비행기(그림)로서 만들어진다!

    tag = "Plane";  // <- 나중에 이 물체가 무엇인지 판별할 때 판단할 근거로 쓰기

    // * 태그가 없어도 인스턴스명, 포인터 등으로 컴퓨터에서 서로 동일 데이터 여부를 판단할 수 있지 않나?
    //   그런데 왜 태그?

    // = 태그는 반드시 같은 대상에게만 붙이지 않아도 된다 = "범주화"

    // 터렛도 초기화
    turret = new Quad(L"Textures/Shooting/rectEnemy.png"); // 포탑 생성

    turret->SetParent(this);    // 포탑에게 이 비행기를 부모 행렬로 전달
                                // -> 포탑은 앞으로 위치 갱신 등을 할 때 반드시 이 비행기를 같이 참조
                                //    다른 말로 = 포탑은 이제 비행기를 따라다닌다!

    // DX는 반투명 처리가 기본 지원. 이 때, 반투명 지정 색은 각 그림 파일 헤더에서 지정된다 (코드 개입 x)
    // 또한 DX는 bmp 외 다른 그림 포맷도 다양하게 지원한다.

    // (참고)
    // 포탑의 현재 위치 : "비행기를 기준으로, {0, 0}"
    // -> 포탑의 위치를 달라고 코드로 요청하면, {0, 0}이 돌아온다
    // -> 포탑의 진짜 위치를 알려면 GlobalPos() 즉 전체 공간 내에서의
    //    (행렬 연산 결과를 역으로 DX가 뜯어낸) 좌표상 위치가 필요하다

    // 그럼 여기서 포탑의 상대 위치 ( "Pos()" ) 이걸 수정하면?
    turret->Pos().x = 100;  // (상대) 위치를 100으로 수정

    // 총알 만들기 (1개짜리)
    // bullet = new Bullet();

    // 총알을 벡터로 만들기

    /*for (int i = 0; i < 10; ++i)
    {
        Bullet* tmp = new Bullet(); // 총알 생성 후
        bullets.push_back(tmp);     // 벡터에 총알 (의 포인터) 넣기
    }*/
    // <- 이렇게 해야 원칙에 맞지만, 성능상 쓰지 않는다

    // 총알 벡터 만들기 : 성능 중시 코드 (싱글턴 사용 이전)

    // bullets.resize(10); // 10개짜리 엉터리 데이터를 채운 총알의 벡터를 미리 만든다.
   
    //for (int i = 0; i < bullets.size(); ++i)    // 벡터에 있는 원소의 개수만큼 반복
    //    bullets[i] = new Bullet();  // i번째 원소에 새 값을 할당하기

    // for each문
    // 자료형 + & : 해당 반복문에서 검색할 자료형 (& : "실체를 대상으로 한다"는 의미)
    // -> 벡터 속의 원소 자료형이 Bullet의 포인터니까 그걸 검색
    // 어디서? bullets라는 벡터에서.
    // 찾아낸 데이터는 반복 시마다 bullet으로 임시 지칭
    // -> 반복 시마다 원소0번부터 9번까지를 돌아가면서 대상으로 지정한다
    // 다른 말로, 벡터 속의 모든 원소를 bullet이라고 치고, 이 bullet을 대상으로 연산을 수행
    // "벡터 속 모든 원소에게 이런저런 연산을 수행하라!"
    // for (Bullet*& bullet : bullets)
    //    bullet = new Bullet();  // 이렇게 적으면 위의 for문과 똑같은 의미가 된다

    // ------------------------------

    // 싱글턴 사용 시 (*혼자 쓸 때 전용. 여러 객체가 쓰면, 씬에서 따로 생성)
    // BulletManager::Get(); // 총알 매니저를 불러온 후... 아무 것도 하지 않는다.
                          // 이 코드는 뭔가 하려고 사용한 코드가 아니라, 애초에 총알 매니저가
                          // 인스턴스 즉 완전한 객체로 앱 속에 존재하게 만들려고 일부러 쓴 낭비 코드다.
                          // 일종의 확인사살 (무조건 존재하도록, 그래서 "객체가 없어서 생기는 오류"가 없게)


    // 연사 관련 변수 첫 할당
    canFire = true; // 일단 쏠 수 있는 걸로
    fireTime = 0;   // 쏜 적이 없어서 걸린 시간 없음
}

Plane::~Plane()
{
    delete turret;  // 이 비행기가 소멸할 때, 포탑도 같이 지워지게

    // 벡터에 만들어진 포인터도 for each로 삭제
    // for (Bullet* bullet : bullets)
    //    delete bullet;

    // BulletManager::Delete();    // 싱글턴 삭제 (단, 등장인물이 여럿이면 이 코드는 주석이어야 한다)
                                // * 등장인물이 여럿이면, 생성자의 Get과 이 코드가 씬에서 실행되는 것도 추천
}

void Plane::Update()
{
    // 연사 판별용 코드 : 필요하면 별도 함수로 작성 가능

    if (!canFire) // 쏠 수 없는 경우 아래 {} 연산 (발사 후 지연 시간 계산)
    {
        fireTime += DELTA;  // 경과한 시간만큼 시간 변수에 누적 = 경과 시간 기록

        if (fireTime >= fireDelay) // 경과 시간이 정해진 지연 시간을 넘어서면
        {
            canFire = true; // 다시 쏠 수 있게
            fireTime = 0;   // 경과시간 0으로
        }
        // 이것이 게임에서 흔히 보는 재사용 대기시간 (쿨다운) 기본 알고리즘
    }

    //-----------------------------------------------


    // 비행기의 행동을 갱신 과정에서 감지하고 수행
    Move();         // 움직이기
    Rotate();       // 회전하기
    Fire();         // 발사하기

    GameObject::Update();   // 게임 속 사물로서 자신을 갱신
    turret->Update();       // 포탑도 갱신시킨다. (그래서 다른 곳에서 포탑 호출을 안 해도 되게.)

    // 총알 업데이트 (1개)
    // bullet->Update();

    // 총알(들) 업데이트
    //for (Bullet* bullet : bullets)
    //    bullet->Update();   // 벡터 내에 존재하는 모든 '총알'을 업데이트

    // 업데이트도 이제 플레이어의 책임이 아니다. 씬의 책임
    //BulletManager::Get()->Update(); //총알 매니저를 업데이트 (->하면 안에 있는 총알들이 업데이트)
}

void Plane::Render()
{

    Quad::Render();          // 자기 자신을 출력 (사각형 속 그림까지 출력)
    turret->Render();        // 포탑도 출력

    //bullet->Render();

    //for (Bullet* bullet : bullets)
    //    bullet->Render();   // 벡터 내에 존재하는 모든 '총알'을 출력(렌더)

    // BulletManager::Get()->Render(); //총알 매니저를 화면에 출력(렌더)
}

void Plane::Move()
{

    if (KEY_PRESS('W'))
    {
        Pos() += Right() * speed * DELTA;   // 위치를 "현재 방향 기준 오른쪽"으로, 속력만큼 이동
    }

    if (KEY_PRESS('S'))
    {
        Pos() -= Right() * speed * DELTA;   // 똑같은 코드, +-만 반대로
    }

}

void Plane::Rotate()
{
    if (KEY_PRESS(VK_LEFT))
    {
        Rot().z += DELTA;   // DX 좌표계 방향 = 반시계
                            // * DX 좌표계는 일반 수학 좌표계와 거의 같고 Z축 방향만 반대
                            //   = "왼손 좌표계"
    }

    if (KEY_PRESS(VK_RIGHT))
    {
        Rot().z -= DELTA;   // DX 좌표계 반대 방향 = 시계
    }

    // 포탑을 움직이기

    if (KEY_PRESS('I'))
    {
        turret->Rot().z += DELTA;   // 포탑의 방향을 수정
    }

    if (KEY_PRESS('K'))
    {
        turret->Rot().z -= DELTA;   // 포탑의 방향을 수정 (반대로)
    }
}

void Plane::Fire()
{
    if (KEY_PRESS(VK_SPACE)) // 스페이스키
    {
        //포탑에서 발사
        // bullet->Fire(turret->GlobalPos(), turret->Right()); // 포탑의 절대위치 반영

        // 벡터를 검색해서...이 중에서 아직 발사가 안 된 총알이 있다면 1개만 발사
        
        // 1. 벡터를 돌아가면서 총알마다 발사가 됐는지 검사
        // 2. 발사가 안 됐으면 발사 (됐으면 패스)
        // 3. 1개 발사 후에, 연산 종료(조건문 종료)

        // 원칙적 for문
        //for (int i = 0; i < bullets.size(); i++)
        //{
        //    if (!bullets[i]->Active()) // 아직 화면에 안 나온 경우라면
        //    {
        //        // 발사 수행
        //        bullets[i]->Fire(turret->GlobalPos(), turret->Right());
        //        return; // 함수 종료 (다른 원소가 더 이상 연산되지 않게, 1개만 발사되도록)
        //    }
        //}
        if (canFire) // (연사 옵션 적용) 쏠 수 있다면
        {
            BulletManager::Get()->Fire(turret->GlobalPos(), turret->Right()); // 총알 매니저로 명령 전달
            // -> 총알 매니저에서 인수로 받은 포탑 위치, 포탑 방향을 가지고
            //    안에 있는 총알을 검사한 후, 준비된 총알을 발사

            // (연사 관련) 쏜 직후에는 연사 불가
            canFire = false; // * 변수의 이름이 반대로 'fireCheck' 같은 식이면 값도 true로 설정 가능
        }
    }

    if (KEY_DOWN(VK_LBUTTON)) // 마우스의 결정 버튼 (기본값 = 좌클릭) * 왼손잡이는 우클릭에 해당
    {
        // 비행기에서 발사
        // bullet->Fire(Pos(), Right());   // 자기 위치 + 자기=비행기의 방향

        // for each문 (위의 for문 발사와 같은 의미)
        //for (Bullet* bullet : bullets)
        //{
        //    if (!bullet->Active())
        //    {
        //        bullet->Fire(Pos(), Right());
        //        return;
        //    }
        //}

        if (canFire) // (연사 옵션 적용) 쏠 수 있다면
        {
            BulletManager::Get()->Fire(Pos(), Right()); // 나를 중심으로, 총알 매니저로 발사 명령 전달

            // (연사 관련) 쏜 직후에는 연사 불가
            canFire = false;
        }
    }
}
