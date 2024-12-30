#pragma once

// 텍스처
// DX의 그림 기능을 호출해서, 우리가 그림 파일을 관리하는 클래스

class Texture
{
private:
    Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file);
    ~Texture();

    // ID3D11ShaderResourceView, ScratchImage : DX가 그림 파일을 해석해서 연산한 중간 데이터
    // 이렇게 중간 데이터를 만든 후, 다시 다른 옵션(필터나, 합성이나, 출력 장소 지정 등)을 거쳐서
    // 마지막으로 모니터에 나타낸다

public:
    void PSSet(UINT slot = 0); // 픽셀 셰이더 지정 함수
                               // 픽셀 셰이더 : 그림에 원래 있던 데이터를 어떤 색으로 해석할지에 대한 코드

    Vector2 GetSize() // 그림 크기 겟터
    {
        return Vector2(image.GetMetadata().width, image.GetMetadata().height);
    }

public:

    // 정적 함수들 : 따로 객체를 더 만들지 않아도 클래스명만 가지고 호출 가능
    // -> 이 방법으로 앱에 직접 그림 파일들을 등록할 수 있기 때문 (말하자면 원재료)

    static Texture* Add(wstring file);
    static void Delete();

private:

    // 그림 세부 데이터
    wstring file; // 원본 그림 파일명

    ScratchImage image;             // 해석된 이미지 1
    ID3D11ShaderResourceView* srv;  // 해석된 이미지 2

    static unordered_map<wstring, Texture*> textures;   // 이 앱에 등록된 모든 그림 파일들(의 저장소)

    // * unordered_map : map의 한 종류. map에 리스트의 특징을 더해서, 메모리의 정렬 등을 제외한 것.
    //   -> 한 맵 안에서 원소 관리가 많이 늦은 대신, 원소 하나를 호출하거나, 추가하거나, 삭제할 땐 빠르다
    //      = 그림 파일 등을 로딩하고 사용하고 메모리에서 종료하기에 딱 좋다
};