#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateSamplerState();
    CreateBlendState();
}

Environment::~Environment()
{
    delete projectionBuffer;
}

void Environment::CreateProjection()
{
    // 투영 데이터 만들기 = 카메라 만들기

    Matrix orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    projectionBuffer = new MatrixBuffer();
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
}

void Environment::CreateSamplerState()
{
    // 공간에서 이미지가 어떻게 보여야 할지 규칙 만들기
    // 이후 규칙이 바뀌어야 하면 여기로 온다는 것만 알면 된다

    // * Address 뒤에 붙은 UVW : XYZ와 닮은, 좌표계에 붙이는 이름 중 하나.
    //                          일반적으로 U가 가로, V가 세로, W가 높낮이
    //                          왜 다른 이름을 쓰는가? : XYZ와 한 자리에서 연산은 하지만,
    //                          단위체계가 다른 그림 등을 사용해야 할 때 그 좌표를 계산하기 위해
    //                          별도의 이름을 가진 좌표계로서 이런 UVW 좌표를 쓴다
    //                          (게임 개발에서 아주 많이 쓰고, W도 생략하고 UV맵이라고도 한다)
    //                          -> 주로 게임에 사용되는 (보이거나, 보이지 않는) 그림, 텍스처에 적용

    // 아래 옵션의 의미 : 2D 기본값, 그림은 그려진 그대로, 가시거리는 최대...라는 뜻

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;        
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;      
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것

    // 다 만든 옵션으로 실제 그림이 그려질 공간을 연산, 생성

    DEVICE->CreateSamplerState(&samplerDesc, &samplerState);
    DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
    // 샘플러(샘플 데이터 생성)와 비슷. 이쪽은 합성 규칙을 설정

    // 옵션의 의미 : 역시 2D 기본값. 반투명 이미지가 있을 경우, 알파 블렌딩한다
    //              더불어 반투명 처리 시, 별도의 색 변조는 없는 걸로 (흰색 반투명)

    D3D11_BLEND_DESC blendDesc = {};    
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // *위 코드에 사용된 "RenderTarget" = 별도 연산된 결과를 모니터의 일부 혹은 전부에 출력하는, 원격출력

    DEVICE->CreateBlendState(&blendDesc, &blendState);

    float blendFactor[4] = {};
    DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);

    // 그래서, 여기까지 오면....

    // 1. 컴퓨터는 카메라가 생긴다.
    // 2. 컴퓨터는 색과 합성을 진행할 규칙과, 그 규칙이 적용된 공간이 생긴다.

    // -> 씬에서 더 이상 이런 부분을 신경쓸 필요가 없어진다.
}
