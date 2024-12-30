#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);

    worldBuffer = new MatrixBuffer(); // 등록 데이터 일단 만들어 두기 (이후 변동이 있으면 적용)
}

GameObject::~GameObject()
{
    if (vertexBuffer)
        delete vertexBuffer;

    if (indexBuffer)
        delete indexBuffer;

    delete worldBuffer; // 물체를 (=트랜스폼을) 둔 공간 삭제
}

void GameObject::Update()
{
    // 트랜스폼 데이터를 갱신해서 위치와 공간을 부여
    UpdateWorld(); // 부모 클래스의 함수 수행
}

void GameObject::Render()
{    
    // DX로서 셰이더를 거치므로, 공간에도 셰이더를 줘야 한다
    // -> 이 경우, 셰이더의 대상이 도트(픽셀)가 아니라 공간 내부의 점(꼭짓점)이 된다
    //    "이 데이터가 공간 속의 어느 위치를 차지한 듯이 연산하고, 3D 계산 후, 모니터에 출력해야 하는가?"

    // -> 이렇게 연산되는 공간 그래픽 셰이더를 "꼭짓점 셰이더(Vertex Shader)"라고 한다

    worldBuffer->Set(world);  // 부모 클래스에서 받는 wolrd 데이터를 공간에 넣는다
    worldBuffer->SetVS(0);    // VS (버텍스 셰이더) 슬롯 설정 (셰이더 슬롯은 텍스처 클래스 확인)

    // -> 이 사물의 공간이 가상 행렬 속에서 어떻게 연산되는지 컴퓨터가 알고, 그걸 출력해줄 수 있다

    // 이 과정 후에, 사물이 가진 세부 데이터를 출력해주면 된다

    //---------------------------------------------------------------------------

    if (vertexBuffer)
        vertexBuffer->Set();
    if (indexBuffer)
        indexBuffer->Set();
    
    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
