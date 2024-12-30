#include "Framework.h"

#include "Scenes/TextureScene.h"

GameManager::GameManager()
{
    Create();

    scene = new TextureScene();
}

GameManager::~GameManager()
{
    delete scene;

    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();

    scene->Update();
}

void GameManager::Render()
{
    Device::Get()->Clear();

    scene->Render();

    // ImGUI : 개발자용 그래픽 인터페이스. 앱에 존재하는 각종 데이터 (변수, 함수, 그 외 온갖 것들)
    //         .....를 별도의 내부 창에 표시해서 개발자가 확인해줄 수 있게 한다.

    // 우리도 ImGui를 써서 이후 코드에서 작성한 내용이 앱에서 어떻게 보일지 확인을 해볼 수 있다

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    ImGui::Text(fps.c_str());

    scene->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}
