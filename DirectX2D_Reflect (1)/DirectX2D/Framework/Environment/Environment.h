#pragma once

// ȯ��(���) Ŭ���� : ��� ������ ó���ϴ� �� (�׸��� ���� ������)
// = ��ü ���� ī�޶� ���� Ŭ������� ���� �ȴ�

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
    MatrixBuffer* projectionBuffer;     // ���� ����

    ID3D11SamplerState* samplerState;   // ���ø� ��Ģ (���ø� : ��û�� �����͸� �����ϰ� ����� ����� ��)
    ID3D11BlendState* blendState;       // ���� ��Ģ (���� : ���� �̹����� �� �ڸ����� �ռ��ϴ� ��)
};