#pragma once

// �ؽ�ó
// DX�� �׸� ����� ȣ���ؼ�, �츮�� �׸� ������ �����ϴ� Ŭ����

class Texture
{
private:
    Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file);
    ~Texture();

    // ID3D11ShaderResourceView, ScratchImage : DX�� �׸� ������ �ؼ��ؼ� ������ �߰� ������
    // �̷��� �߰� �����͸� ���� ��, �ٽ� �ٸ� �ɼ�(���ͳ�, �ռ��̳�, ��� ��� ���� ��)�� ���ļ�
    // ���������� ����Ϳ� ��Ÿ����

public:
    void PSSet(UINT slot = 0); // �ȼ� ���̴� ���� �Լ�
                               // �ȼ� ���̴� : �׸��� ���� �ִ� �����͸� � ������ �ؼ������� ���� �ڵ�

    Vector2 GetSize() // �׸� ũ�� ����
    {
        return Vector2(image.GetMetadata().width, image.GetMetadata().height);
    }

public:

    // ���� �Լ��� : ���� ��ü�� �� ������ �ʾƵ� Ŭ������ ������ ȣ�� ����
    // -> �� ������� �ۿ� ���� �׸� ���ϵ��� ����� �� �ֱ� ���� (�����ڸ� �����)

    static Texture* Add(wstring file);
    static void Delete();

private:

    // �׸� ���� ������
    wstring file; // ���� �׸� ���ϸ�

    ScratchImage image;             // �ؼ��� �̹��� 1
    ID3D11ShaderResourceView* srv;  // �ؼ��� �̹��� 2

    static unordered_map<wstring, Texture*> textures;   // �� �ۿ� ��ϵ� ��� �׸� ���ϵ�(�� �����)

    // * unordered_map : map�� �� ����. map�� ����Ʈ�� Ư¡�� ���ؼ�, �޸��� ���� ���� ������ ��.
    //   -> �� �� �ȿ��� ���� ������ ���� ���� ���, ���� �ϳ��� ȣ���ϰų�, �߰��ϰų�, ������ �� ������
    //      = �׸� ���� ���� �ε��ϰ� ����ϰ� �޸𸮿��� �����ϱ⿡ �� ����
};