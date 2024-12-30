#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    background = new Quad(L"Textures/ETC/Kitties.jpg");
    background->Pos() = { CENTER_X, CENTER_Y };
    background->Scale() = { 0.5f, 0.5f };
    background->UpdateWorld(); // 업데이트 수행을 해줘도 되지만.. 어차피 안 움직일 거라...

    BulletManager::Get();

    ninja = new Ninja();

    // 카메라를 개발자 모드로
    //Environment::Get()->GetMainCamera()->SetDevMode(true);  // 환경설정으로 호출
    CAM->SetDevMode(true);
    
    // 카메라에 추적 대상을 설정하기 (카메라가 닌자를 따라가게)
    // CAM->SetTarget(ninja);


    // 이펙트를 (싱글턴으로) 써보기

    // 이펙트 추가
    EffectManager::Get()->Add("Explosion1", // 이펙트에 우리가 부여하는 이름 (마음대로)
        10,                                 // 앱에서 이펙트가 몇 개 등록될지 (간단히 생각하면, 동시재생 가능한 수)
        L"Textures/Effect/Explosion1.png",  // 파일 경로
        4,                                  // 파일 속 그림의 가로 개수
        4);                                 // 파일 속 그림의 세로 개수

    // 조금 더 추가 (위와 같은 데이터, 다른 key)
    EffectManager::Get()->Add("Explosion1A", 10, L"Textures/Effect/Explosion1.png", 4, 4);
    EffectManager::Get()->SetColor("Explosion1A", 1, 0, 0); // 색을 완전 빨갛게 (폭발이니까!)

    // 다른 파일도 추가
    EffectManager::Get()->Add("Explosion2", 10, L"Textures/Effect/Explosion2.png", 4, 2, // 작은 그림 개수 반영
        0.8f,       // 속도 계수
        true);      // 화소 누적 여부
}

AnimationScene::~AnimationScene()
{
    delete ninja;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    // 키를 123으로 누르면 이펙트가 각각 하나씩 재생되게
    if (KEY_DOWN('1'))
        EffectManager::Get()->Play("Explosion1", mousePos); // 재생위치 = 마우스 커서 위치
    if (KEY_DOWN('2'))
        EffectManager::Get()->Play("Explosion1A", mousePos);
    if (KEY_DOWN('3'))
        EffectManager::Get()->Play("Explosion2", mousePos);


    // background->UpdateWorld(); // 안 움직일 건데

    ninja->Update();

    BulletManager::Get()->Update();

    // 카메라 수동 조작의 경우 (클래스 안에 있긴 하지만 확인차)
    // -> 화살표키로 카메라 움직여보기
    if (KEY_PRESS(VK_LEFT))
        CAM->Pos().x -= DELTA * 100;

    if (KEY_PRESS(VK_RIGHT))
        CAM->Pos().x += DELTA * 100;

    EffectManager::Get()->Update(); // 이펙트 갱신
}

void AnimationScene::Render()
{
    background->Render();

    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render(); // 이펙트 출력
}

void AnimationScene::PostRender()
{    
    ninja->PostRender();
}
