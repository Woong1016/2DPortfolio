#include "Framework.h"

Plane::Plane()
    : Quad(L"Textures/Shooting/airplane.png")
{
    tag = "Plane";

    weapon = new Quad(L"Textures/Shooting/player.png");
    weapon->SetParent(this);
    weapon->Pos().x = 100.0f;

    BulletManager::Get();
}

Plane::~Plane()
{
    delete weapon;

    BulletManager::Delete();
}

void Plane::Update()
{
    Move();
    Rotate();
    Fire();

    UpdateWorld();
    weapon->UpdateWorld();

    BulletManager::Get()->Update();
}

void Plane::Render()
{
    Quad::Render();
    weapon->Render();

    BulletManager::Get()->Render();
}

void Plane::Move()
{
    if (KEY_PRESS('W'))
    {
        localPosition += Right() * speed * DELTA;
        //localPosition.y += speed * DELTA;
        //
        //if (localPosition.y > WIN_HEIGHT - Half().y)
        //    localPosition.y = WIN_HEIGHT - Half().y;
    }

    if (KEY_PRESS('S'))
    {
        localPosition -= Right() * speed * DELTA;
        //localPosition.y -= speed * DELTA;
        //
        //if (localPosition.y < Half().y)
        //    localPosition.y = Half().y;
    }
/*
    if (KEY_PRESS('A'))
    {
        localPosition.x -= speed * DELTA;

        if (localPosition.x < Half().x)
            localPosition.x = Half().x;
    }

    if (KEY_PRESS('D'))
    {
        localPosition.x += speed * DELTA;

        if (localPosition.x > WIN_WIDTH - Half().x)
            localPosition.x = WIN_WIDTH - Half().x;
    }
    */
}

void Plane::Rotate()
{
    //localRotation.z = (mousePos - localPosition).Angle();

    if (KEY_PRESS('A'))
    {
        localRotation.z += DELTA;
    }

    if (KEY_PRESS('D'))
    {
        localRotation.z -= DELTA;
    }
}

void Plane::Fire()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        BulletManager::Get()->Fire(weapon->GlobalPos(), Right());
    }
}
