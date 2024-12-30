#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
    colliders.push_back(new CircleCollider(50.0f));
    colliders.back()->SetTag("Circle1");
    colliders.back()->Pos() = { CENTER_X, CENTER_Y };
    //
    //colliders.push_back(new CircleCollider(50.0f));
    //colliders.back()->SetTag("Circle2");
    //colliders.back()->Pos() = { CENTER_X, CENTER_Y };

    colliders.push_back(new RectCollider({50, 100}));
    colliders.back()->SetTag("Rect1");
    colliders.back()->Pos() = { CENTER_X, CENTER_Y };

    //colliders.push_back(new RectCollider({ 100, 50 }));
    //colliders.back()->SetTag("Rect2");
    //colliders.back()->Pos() = { CENTER_X, CENTER_Y };
}

CollisionScene::~CollisionScene()
{
    for (Collider* collider : colliders)
        delete collider;
}

void CollisionScene::Update()
{    
    //if (colliders[0]->IsPointCollision(mousePos))
    //{
    //    colliders[0]->GetColor() = { 1, 0, 0, 1 };
    //}
    //else
    //{
    //    colliders[0]->GetColor() = { 0, 1, 0, 1 };
    //}
    

    if (colliders[0]->IsCollision(colliders[1]))
    //Vector2 overlap;
    //if (((RectCollider*)colliders[0])->IsRectCollision((RectCollider*)colliders[1], &overlap))
    {
        colliders[0]->GetColor() = { 1, 0, 0, 1 };
        colliders[1]->GetColor() = { 1, 0, 0, 1 };
    }
    else
    {
        colliders[0]->GetColor() = { 0, 1, 0, 1 };
        colliders[1]->GetColor() = { 0, 1, 0, 1 };
    }

    for (Collider* collider : colliders)
        collider->UpdateWorld();
}

void CollisionScene::Render()
{
    for (Collider* collider : colliders)
        collider->Render();
}

void CollisionScene::PostRender()
{
    for (Collider* collider : colliders)
        collider->RenderUI();
}
