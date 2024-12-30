#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    bg = new Quad(L"Textures/Shooting/bgTest.png");
    bg->Pos() = { CENTER_X, CENTER_Y };
    bg->UpdateWorld();

    plane = new Plane();
    plane->Pos() = { CENTER_X, CENTER_Y };    
}

TextureScene::~TextureScene()
{
    delete plane;
    delete bg;
}

void TextureScene::Update()
{   
    plane->Update();
}

void TextureScene::Render()
{
    bg->Render();

    plane->Render();
}

void TextureScene::PostRender()
{
    plane->RenderUI();
}
