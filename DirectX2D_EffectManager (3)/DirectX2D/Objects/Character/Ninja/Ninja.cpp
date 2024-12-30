#include "Framework.h"

Ninja::Ninja()    
{
    Pos() = { CENTER_X, CENTER_Y };

    CreateActions();
    actions[curAction]->Start();
}

Ninja::~Ninja()
{
    for (pair<ActionType, Action*> action : actions)
        delete action.second;
}

void Ninja::Update()
{
    Control();

    actions[curAction]->Update();
    UpdateWorld();
}

void Ninja::Render()
{
    SetRender();

    actions[curAction]->Render();
}

void Ninja::PostRender()
{
    
}

void Ninja::Control()
{
    Move();
    Jump();
    Attack();
    Glide();
}

void Ninja::Move()
{
    if (curAction == JUMP_UP || curAction == JUMP_DOWN) return;
    if (curAction == GLIDE) return;
    if (curAction >= ATTACK) return;

    bool isMove = false;

    isMove |= KEY_PRESS('D');
    isMove |= KEY_PRESS('A');

    isMove ? SetAction(RUN) : SetAction(IDLE);
}

void Ninja::Jump()
{
    if (curAction >= ATTACK) return;
    if (curAction == GLIDE) return;
    if (curAction == JUMP_UP || curAction == JUMP_DOWN) return;

    if (KEY_DOWN(VK_SPACE))
        SetAction(JUMP_UP);
}

void Ninja::Attack()
{
    if (curAction >= ATTACK) return;
    if (curAction == GLIDE) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        if (curAction == JUMP_UP || curAction == JUMP_DOWN)
        {
            SetAction(JUMP_ATTACK);
        }
        else
        {
            SetAction(ATTACK);
        }
    }
    
    if (KEY_DOWN(VK_RBUTTON))
    {
        if (curAction == JUMP_UP || curAction == JUMP_DOWN)
        {
            SetAction(JUMP_THROW);
        }
        else
        {
            SetAction(THROW);
        }
    }
}

void Ninja::Glide()
{
    if (curAction >= ATTACK) return;
    if (curAction == IDLE || curAction == RUN) return;

    if (KEY_DOWN('S'))      // 설정한 키를 누르면 (DOWN = 1회만 처리)
        SetAction(GLIDE);   // 액션이 글라이드로 변화 (변화한 액션이 쭉 수행)

    if (KEY_UP('S'))            // 키를 떼면 (UP = 1회만 처리)
        SetAction(JUMP_DOWN);   // 글라이드 종료 (점프 떨어지기로 : 점프가 끝났으면 자동으로 착지)
}

void Ninja::SetIdle()
{
    SetAction(IDLE);
}

void Ninja::Fall()
{
    SetAction(JUMP_DOWN);
}

void Ninja::SetAction(int type)
{
    if (curAction == type) return;

    curAction = (ActionType)type;
    actions[(ActionType)type]->Start();
}

void Ninja::CreateActions()
{
    //가만히
    actions[IDLE] = new Action("Textures/Ninja/", "Ninja_Idle.xml", true);

    //달리기
    actions[RUN] = new NinjaRun(this);

    //점프 : 상승
    actions[JUMP_UP] = new NinjaJumpUp(this);
    actions[JUMP_UP]->SetEvent(bind(&Ninja::Fall, this));

    //점프 : 하강
    actions[JUMP_DOWN] = new NinjaJumpDown(this);
    actions[JUMP_DOWN]->SetEvent(bind(&Ninja::SetIdle, this));

    //공격 : 일반, 지상
    actions[ATTACK] = new NinjaMeleeAttack(this);
    actions[ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));

    //공격 : 일반, 공중
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::Fall, this));

    //공격 : 투척, 지상
    actions[THROW] = new NinjaThrow(this);
    actions[THROW]->SetEvent(bind(&Ninja::SetIdle, this));

    //공격 : 투척, 공중
    actions[JUMP_THROW] = new NinjaThrow(this);
    actions[JUMP_THROW]->SetEvent(bind(&Ninja::Fall, this));

    //활강 (저속 낙하)
    actions[GLIDE] = new NinjaGlide(this);    
}