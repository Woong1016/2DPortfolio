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
    // ���� ������ ����� = ī�޶� �����

    Matrix orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    projectionBuffer = new MatrixBuffer();
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
}

void Environment::CreateSamplerState()
{
    // �������� �̹����� ��� ������ ���� ��Ģ �����
    // ���� ��Ģ�� �ٲ��� �ϸ� ����� �´ٴ� �͸� �˸� �ȴ�

    // * Address �ڿ� ���� UVW : XYZ�� ����, ��ǥ�迡 ���̴� �̸� �� �ϳ�.
    //                          �Ϲ������� U�� ����, V�� ����, W�� ������
    //                          �� �ٸ� �̸��� ���°�? : XYZ�� �� �ڸ����� ������ ������,
    //                          ����ü�谡 �ٸ� �׸� ���� ����ؾ� �� �� �� ��ǥ�� ����ϱ� ����
    //                          ������ �̸��� ���� ��ǥ��μ� �̷� UVW ��ǥ�� ����
    //                          (���� ���߿��� ���� ���� ����, W�� �����ϰ� UV���̶�� �Ѵ�)
    //                          -> �ַ� ���ӿ� ���Ǵ� (���̰ų�, ������ �ʴ�) �׸�, �ؽ�ó�� ����

    // �Ʒ� �ɼ��� �ǹ� : 2D �⺻��, �׸��� �׷��� �״��, ���ðŸ��� �ִ�...��� ��

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;        
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;      
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : ī�޶��� �Ÿ��� ���� ����Ƽ�� �ٸ��� �ϴ� ��

    // �� ���� �ɼ����� ���� �׸��� �׷��� ������ ����, ����

    DEVICE->CreateSamplerState(&samplerDesc, &samplerState);
    DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
    // ���÷�(���� ������ ����)�� ���. ������ �ռ� ��Ģ�� ����

    // �ɼ��� �ǹ� : ���� 2D �⺻��. ������ �̹����� ���� ���, ���� �����Ѵ�
    //              ���Ҿ� ������ ó�� ��, ������ �� ������ ���� �ɷ� (��� ������)

    D3D11_BLEND_DESC blendDesc = {};    
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // *�� �ڵ忡 ���� "RenderTarget" = ���� ����� ����� ������� �Ϻ� Ȥ�� ���ο� ����ϴ�, �������

    DEVICE->CreateBlendState(&blendDesc, &blendState);

    float blendFactor[4] = {};
    DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);

    // �׷���, ������� ����....

    // 1. ��ǻ�ʹ� ī�޶� �����.
    // 2. ��ǻ�ʹ� ���� �ռ��� ������ ��Ģ��, �� ��Ģ�� ����� ������ �����.

    // -> ������ �� �̻� �̷� �κ��� �Ű澵 �ʿ䰡 ��������.
}
