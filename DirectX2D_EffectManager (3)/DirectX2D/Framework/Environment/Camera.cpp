#include "Framework.h"

Camera::Camera()
{
    // �̸� ���� (Ʈ���������μ�)
    tag = "Camera";

    //�þ� ������ �޸𸮿� ���� (ȯ�漳���� �Ϻθ� ī�޶� ���� �д�)
    viewBuffer = new MatrixBuffer();
    viewBuffer->SetVS(1);
}

Camera::~Camera()
{
    delete viewBuffer;
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
        FreeMode();

    SetView();
}

void Camera::SetView()
{
    UpdateWorld();

    // ȯ�� ������ �ִ� �þ� �ڵ带 ī�޶�� �Űܿ� ��
    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view);
    viewBuffer->SetVS(1);
}

Vector2 Camera::ScreenToWorld(Vector2 pos)
{
    return pos * world;
}

Vector2 Camera::WorldToScreen(Vector2 pos)
{
    return pos * view;
}

void Camera::FreeMode()
{
    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS(VK_UP))
            Pos().y += speed * DELTA;
        if (KEY_PRESS(VK_DOWN))
            Pos().y -= speed * DELTA;
        if (KEY_PRESS(VK_LEFT))
            Pos().x -= speed * DELTA;
        if (KEY_PRESS(VK_RIGHT))
            Pos().x += speed * DELTA;
    }

    FixPosition(localPosition);
}

void Camera::FollowMode()
{
    Vector2 targetPos = target->GlobalPos() - targetOffset;

    FixPosition(targetPos);

    localPosition = Lerp(localPosition, targetPos, speed * DELTA);
}

void Camera::FixPosition(Vector2& position)
{
    if (isDevMode) return;

    if (position.x < leftBottom.x)
        position.x = leftBottom.x;

    if (position.x > rightTop.x - deviceSize.x)
        position.x = rightTop.x - deviceSize.x;

    if (position.y < leftBottom.y)
        position.y = leftBottom.y;

    if (position.y > rightTop.y - deviceSize.y)
        position.y = rightTop.y - deviceSize.y;
}
