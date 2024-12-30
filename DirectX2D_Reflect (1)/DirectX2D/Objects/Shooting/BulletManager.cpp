#include "Framework.h"

BulletManager::BulletManager()
{
    // 비행기 때와 같은 총알 생성을 여기에서 다시 작성하면 된다 (독립 벡터에서 총알 작성)
    bullets.resize(30); // 이 클래스를 쓰는 등장인물이 이제 하나가 아닐 수 있으므로 넉넉하게 데이터를 준비

    for (Bullet*& bullet : bullets) // bullets 벡터에 있는 모든 원소를 bullet으로 임시 지칭하고
        bullet = new Bullet();      // 그 bullet에 새 인스턴스를 만들어서 객체로 할당

    // 적의 총알도 생성
    enemyBullets.resize(50);
    for (EnemyBullet*& bullet : enemyBullets) // 임시 이름이라 원소 이름은 이번에도 bullet
        bullet = new EnemyBullet();

}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)  // 벡터의 모든 원소를 각각 bullet으로 지칭하고
        delete bullet;              // 포인터 위치 삭제 (혹은 개방)

    for (EnemyBullet* bullet : enemyBullets)
        delete bullet;
}

void BulletManager::Update()
{
    for (Bullet* bullet : bullets)  // 벡터의 모든 원소를 각각 bullet으로 지칭하고
        bullet->Update();           // 각 원소를 업데이트

    //적 총알도 업데이트
    for (EnemyBullet* bullet : enemyBullets)
        bullet->Update();
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
        bullet->Render();           // 모든 벡터 속의 총알 출력

    for (EnemyBullet* bullet : enemyBullets)
        bullet->Render();
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
    // 총알 발사 부분만 가져와서 여기서 반복
    // -> 총알 단 1개 (=1종류) 그거만 쏴야 하므로 이 내용은 건드릴 수 없다
    //    (적의 총알에 대응하는 함수가 필요할 경우, 별도로 하나 더 만들어야)

    for (Bullet* bullet : bullets) // 모든 총알을 검사해서
    {
        if (!bullet->Active()) // 아직 발사 안 된 총알 중에 첫 번째를 찾아서
        {
            bullet->Fire(pos, direction);   // 발사한다. (그리고 함수로 받은 매개변수 pos, dir을
                                            // 총알에 그대로 전달해준다)
            return;                         // 그리고 함수 종료 (여러 개 발사되지 않게!)
        }
    }
}

void BulletManager::EnemyFire(Vector2 pos, Vector2 direction)
{
    // 적의 총알 발사용 함수. EnemyBullet 클래스를 대상으로 한다
    // 이렇게 만들면 총알 매니저가 이제 비행기에도, 적에게도 영향을 미친다

    for (EnemyBullet* bullet : enemyBullets)
    {
        if (!bullet->Active()) // 아직 발사 안 된 총알 중에 첫 번째를 찾아서
        {
            bullet->Fire(pos, direction);   // 발사한다. (그리고 함수로 받은 매개변수 pos, dir을
            // 총알에 그대로 전달해준다)
            return;                         // 그리고 함수 종료 (여러 개 발사되지 않게!)
        }
    }
}

void BulletManager::CollisionBullets()
{
    // 각 총알마다 돌아가면서 충돌 체크를 하면 된다
    for (Bullet* b1 : bullets)  // 총알 벡터에 있는 각 총알마다 돌아가면서 b1으로 지칭
    {
        // 연산을 하지 않는 경우부터 수행
        if (!b1->Active()) continue; // continue : 반복문 중, 현재 수행 폐기, 다음 연산 속행

        // 같은 종류 총알끼리
        for (Bullet* b2 : bullets) // 총알 벡터에 있는 각 총알마다 한번 더 돌아가면서 b2로 지칭
        {
            // 이 반복문이 도는 동안 원소 하나당 벡터 내의 다른 모든 원소와 비교를 한다
            // 말하자면 리그전.

            if (!b2->Active()) continue;
            if (b1 == b2) continue; // 두 대상이 동일하면 연산 폐기 후 속행

            if (b1->GetCollider()->IsCollision(b2->GetCollider())) // 두 총알의 충돌체가 서로 부딪치면?
            {
                // TODO : 충돌한 경우 수행할 연산을 적으면 OK
            }
        }

        // 종류가 다른 총알과도 충돌 비교 가능
        for (EnemyBullet* e1 : enemyBullets)
        {
            if (!e1->Active()) continue;

            if (b1->GetCollider()->IsCollision(e1->GetCollider()))
            {
                // TODO : 내 총알과 적 총알이 부딪친 경우 일어날 일
                
                // -- 샘플 : 둘 다 없어지게
                // b1->SetActive(false); // 반사를 위해 주석화
                e1->SetActive(false);
            }

            // 두 총알이 부딪칠 때, 교집합을 살펴 가면서 반사까지 수행하는 코드
            // -> 충돌체 함수 중, 두 번째 매개변수 지정이 가능한 사각형 충돌 함수를 콕 집어 써보기

            Vector2 overlap = { 0, 0 }; // 교집합으로 사용하기 위한 임시 데이터 (충돌 확인 전이므로 값 없음)

            // 두 충돌체를 사각형으로써 비교 ( + 위에서 만든 overlap 데이터에 값도 넣기)
            if (b1->GetCollider()->IsRectCollision((RectCollider*)e1->GetCollider(), &overlap))
            {
                Vector2 floor; // 지금 바닥(부딪친 면)이 정확히 어느 벡터인지 구하기 위한 데이터

                // 여기서 필요한 것이 교집합의 모양
                if (overlap.x > overlap.y) // 가로로 납작한 교집합 = 수직 충돌 (위나 아래에서 부딪침)
                {
                    // 바닥은 대상의 상대적 수평선를 기준으로 한다
                    floor  = { ((RectCollider*)e1->GetCollider())->R(), ((RectCollider*)e1->GetCollider())->T() };
                    floor -= { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->T() };

                    // 여기까지 오면 부딪친 곳(지금은 e1)의 좌우를 뺀 위-아래 선을 벡터 면으로 삼는다
                }
                else // 수평 충돌 (왼쪽이나 오른쪽에서 부딪침)
                {
                    // 바닥은 대상의 상대적 수직선을 기준으로 한다
                    floor  = { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->B() };
                    floor -= { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->T() };
                }

                // 이 시점에서, 아무튼, 바닥(혹은 "부딪친 반사면")은 구한 셈

                // 그 반사면을 기준으로 만드는 반사용 법선을 내기

                Vector2 reflect = floor.Normal(); // 바닥의 법선 내기 (x, y 좌표 뒤집고 하나를 음수로 만들어 방향 꺾기)
                reflect = reflect.GetNormalized();  // 정규화하기 (길이가 1이 되도록!)

                // 이 정규화된 법선 (튕겨 올라갈 수직선) ...에 입사한 총알의 이동력만큼의 힘을 적용해주면 반사

                // 총알이 반사면에 가한 힘(투입한 힘)을 알기 위한 점곱(내적)을 진행
                float ratio = b1->GetDir().Dot(reflect);

                // 이 힘(비율)을 수직 벡터에 피드백하면 -> 그 길이만큼 벡터가 늘어나서 투영 벡터로 작용
                reflect = reflect * ratio; // 새로운 투입 벡터
                reflect = reflect * -1;    // 투입으로 투영으로 바꾸기

                reflect = reflect * 2;     // 투영 벡터를 더 더해서 반사하는 힘으로

                // 다 만들어진 반사하는 힘을 원래의 입사 벡터에 적용하면 반사 벡터로 만들게 된다

                b1->GetDir() = b1->GetDir() + reflect; // 새로운 방향이 만들어진다

                // (옵션) 새로운 방향에 맞게 회전
                b1->Rot().z = b1->GetDir().Angle(); // 새로운 방향의 각도로 회전

                // 여기까지 오면 내 총알의 방향 계산이 끝난다.
                // 상대 총알은 이 과정을 한번 더 따로 (TODO!!!! 과제 ㅋㅋㅋㅋ)

            }
        }

        // 여기까지 오면 내 총알에 필요한 비교는 다 했다
    }

    // 적 총알에 충돌이 있다면
    for (EnemyBullet* e1 : enemyBullets)
    {
        if (!e1->Active()) continue;

        // 적의 총알을 내 총알과 비교할 필요는 지금은 없다 : 위에 다 해놔서
        // 적의 총알에 지금 필요한 충돌 비교는 : 같은 종류끼리
        for (EnemyBullet* e2 : enemyBullets)
        {
            if (!e2->Active()) continue;
            if (e1 == e2) continue;

            if (e1->GetCollider()->IsCollision(e2->GetCollider()))
            {
                // 두 총알이 부딪치면 일어날 일을 작성

                //-- 샘플 : 두 총알이 부딪치면 색이 바뀔 수 있는지 실험
                e1->GetCollider()->GetColor() = { 1, 1, 1, 1 }; // 흰색
                e2->GetCollider()->GetColor() = { 1, 1, 0, 1 }; // 노랑

                // 두 총알이 부딪쳤을 때, 반대로 튕겨나가려면???
            }
        }
    }
}

bool BulletManager::CollisionBulletToOther(Collider* collider)
{
    return false;

    // TODO : 과제로 해봅시다!! (총알과 다른 물체의 충돌!!)
}
