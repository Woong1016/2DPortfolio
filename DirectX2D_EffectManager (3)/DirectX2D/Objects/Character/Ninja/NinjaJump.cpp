#include "Framework.h"

NinjaJump::NinjaJump(Transform* target)
    : target(target)
{
}

void NinjaJump::Update()
{
    velocity -= GRAVITY * DELTA;

    target->Pos().y += velocity * DELTA;

    Move();

    Action::Update();
}

void NinjaJump::Move()
{
    if (KEY_PRESS('D'))
    {
        target->Pos().x += MOVE_SPEED * DELTA;
        target->Rot().y = 0;
    }

    if (KEY_PRESS('A'))
    {
        target->Pos().x -= MOVE_SPEED * DELTA;
        target->Rot().y = XM_PI;
    }
}
