#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_START_X 100
#define WIN_START_Y 100

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetElapsedTime()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

//ImGui
#include <ImGui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "ImGui.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

//Framework Header

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/System/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Render/Texture.h"

#include "Framework/Collision/Collider.h" // 충돌체 클래스 (기본 규칙)
#include "Framework/Collision/RectCollider.h" // 사각형 충돌체
#include "Framework/Collision/CircleCollider.h"

#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"

#include "Objects/Shooting/Plane.h"
#include "Objects/Shooting/Enemy.h"
#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/EnemyBullet.h"
#include "Objects/Shooting/BulletManager.h" // 매니저가 있으려면 그 전에 매니저가 다룰 대상들이 다 로딩되어야 한다

//Scene Header
#include "Scenes/Scene.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;