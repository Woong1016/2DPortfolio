#include "Framework.h"

Bullet::Bullet()
    : Quad(L"Textures/Shooting/playerBullet2.png")
{
    // 일단은 그림 생성 후, 대기
    // + 비활성화 (나오자마자 오사되는 것을 막기 위함)

    isActive = false;

    collider = new RectCollider(texture->GetSize());    // 그림 데이터 크기가 곧 영역의 크기
    collider->SetParent(this);  // 충돌체의 부모 영역을 자기 자신으로 = 충돌체가 자신을 따라다니게!
}

Bullet::~Bullet()
{
    delete collider;
}

void Bullet::Update()
{
    // 활성화 감지 후, 활성화가 아니면 연산 없음
    if (!isActive) return;

    // 총알로서 움직이기
    Pos() += direction * speed * DELTA; // 주어진 방향대로 움직이기 (계속 직진)

    // 총알이 활성화가 되지 않는 조건 = 1. 눈에 안 보일 때. 2. 맞았을 때. (<-나중에)
    if (Pos().x < 0 || Pos().x > WIN_WIDTH) isActive = false;
    if (Pos().y < 0 || Pos().y > WIN_HEIGHT) isActive = false;

    // 게임 속 물체로서 스스로를 갱신
    GameObject::Update();
    collider->UpdateWorld();
}

void Bullet::Render()
{
    if (!isActive) return;
    Quad::Render();
    collider->Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;    // 활성화가 됐든 안 됐든 무조건 여기서 활성화 확정

    Pos() = pos;    // 매개변수를 자신에게 적용 (위치 적용)
    this->direction = direction;    // 방향 역시

    // 진행 방향에 맞추어서 자기 그림 각도도 조절
    Rot().z = direction.Angle(); // 탄젠트 역을 써서 각도 계산, DX는 y에 - 필요 없음
}
