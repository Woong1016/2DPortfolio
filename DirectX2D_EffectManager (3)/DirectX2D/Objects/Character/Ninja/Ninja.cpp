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

    if (KEY_DOWN('S'))      // ������ Ű�� ������ (DOWN = 1ȸ�� ó��)
        SetAction(GLIDE);   // �׼��� �۶��̵�� ��ȭ (��ȭ�� �׼��� �� ����)

    if (KEY_UP('S'))            // Ű�� ���� (UP = 1ȸ�� ó��)
        SetAction(JUMP_DOWN);   // �۶��̵� ���� (���� ��������� : ������ �������� �ڵ����� ����)
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
    //������
    actions[IDLE] = new Action("Textures/Ninja/", "Ninja_Idle.xml", true);

    //�޸���
    actions[RUN] = new NinjaRun(this);

    //���� : ���
    actions[JUMP_UP] = new NinjaJumpUp(this);
    actions[JUMP_UP]->SetEvent(bind(&Ninja::Fall, this));

    //���� : �ϰ�
    actions[JUMP_DOWN] = new NinjaJumpDown(this);
    actions[JUMP_DOWN]->SetEvent(bind(&Ninja::SetIdle, this));

    //���� : �Ϲ�, ����
    actions[ATTACK] = new NinjaMeleeAttack(this);
    actions[ATTACK]->SetEvent(bind(&Ninja::SetIdle, this));

    //���� : �Ϲ�, ����
    actions[JUMP_ATTACK] = new NinjaJumpAttack(this);
    actions[JUMP_ATTACK]->SetEvent(bind(&Ninja::Fall, this));

    //���� : ��ô, ����
    actions[THROW] = new NinjaThrow(this);
    actions[THROW]->SetEvent(bind(&Ninja::SetIdle, this));

    //���� : ��ô, ����
    actions[JUMP_THROW] = new NinjaThrow(this);
    actions[JUMP_THROW]->SetEvent(bind(&Ninja::Fall, this));

    //Ȱ�� (���� ����)
    actions[GLIDE] = new NinjaGlide(this);    
}