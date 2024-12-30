#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    /* 시작과 끝에 이런 표시가 있으면
    사이에 있는 모든 텍스트가 주석 */

    /* 
    // rect = new Rect({}, {}); // <- 오류.
    plane = new Quad(
        L"Textures/Shooting/airplane.png",
        { CENTER_X, CENTER_Y }
    );
    */

    // -----------------------------

    // 2개 이상 객체가 참조하고, 그 씬에서만 필요한 싱글톤이 있다면?
    // -> 객체가 아닌 씬이 해당 싱글톤을 관리하는 게 더 효율적일 수도.
    BulletManager::Get();   // 특정 클래스만이 아닌, 씬에서 바로 싱글톤 객체가 나오게.

    //그러고 나서 진짜 등장인물들을 나오게 한다.
    plane = new Plane();    // 비행기 그냥 생성 (필요한 설정은 클래스에서 이미 끝)
    plane->Pos() = { CENTER_X, CENTER_Y };  // 위치만 다시 설정

    enemy = new Enemy();
    enemy->Pos() = { CENTER_X / 2, CENTER_Y };  // 확인 삼아 위치 조정

    enemy2 = new Enemy();
    enemy2->Pos() = { CENTER_X * 3 / 2, CENTER_Y }; // 가로 3/4 위치에 등장

}

TextureScene::~TextureScene()
{
    delete plane;
    delete enemy;
    delete enemy2;

    BulletManager::Delete();    // 독립적으로 나온 싱글톤이니, 독립적으로 지울 수 있다
                                // (말하자면 "이 씬만 아니면 총알매니저 쓰는 다른 장면은 설마 없겠지?")
                                //  ....물론 다른 씬에서도 싱글톤을 쓰면, 이 코드는 다시 없어져야...
}

void TextureScene::Update()
{
    /* 조작은 다른 곳에서...
    if (KEY_PRESS(VK_LEFT))
        plane->Rot().z += DELTA;

    if (KEY_PRESS(VK_UP))
        plane->Pos() += plane->Right();
    */

    // ------------
    // 반사에 대해 일어날 일을 코드로 호출
    // * 총알끼리만 작성하면 총알 매니저가 합리적 (총알 데이터가 있는 곳)
    //   그러나 적과 플레이어 데이터까지 대상으로 삼을 땐 모든 등장인물이 있는 곳이 최적

    CheckCollision(); // 충돌 확인 및 그 이후에 일어날 일 작성

    // ------------

    plane->Update(); // 이제 생성과 갱신, 출력만 존재
    enemy->Update();
    enemy2->Update();

    BulletManager::Get()->Update();
    // -> 비행기와도, 적과도 구분되는 총알 매니저 안의 모든 데이터가 (= 총알들이)
    //    씬에서 각자 자기 데이터대로 연산되고 또 그려진다
}

void TextureScene::Render()
{
    plane->Render();
    enemy->Render();
    enemy2->Render();

    BulletManager::Get()->Render();
}

void TextureScene::PostRender()
{
}

void TextureScene::CheckCollision()
{
    // 충돌 확인 조건문

    //if (BulletManager::Get()->CollisionBulletToOther(플레이어충돌체))
    //{
    //      // 플레이어와 상호작용
    //}

    BulletManager::Get()->CollisionBullets();   // 총알끼리 일어나는 충돌 연산
}
