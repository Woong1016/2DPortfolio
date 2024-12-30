#pragma once

// 환경(배경) 클래스 : 배경 공간을 처리하는 곳 (그리고 투영 공간도)
// = 전체 배경과 카메라 설정 클래스라고 봐도 된다

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

private:
    void CreateProjection();
    void CreateSamplerState();
    void CreateBlendState();

private:
    MatrixBuffer* projectionBuffer;     // 투영 공간

    ID3D11SamplerState* samplerState;   // 샘플링 규칙 (샘플링 : 시청각 데이터를 연산하고 결과로 만드는 것)
    ID3D11BlendState* blendState;       // 블렌딩 규칙 (블렌딩 : 여러 이미지를 한 자리에서 합성하는 것)
};