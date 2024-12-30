#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file)
    : srv(srv), image(move(image)), file(file)
{
    // Add를 통해서 각 그림 데이터를 행성하므로 여기선 다른 할 일이 없다 (변수 전달 전용)
}

Texture::~Texture()
{
    srv->Release();
}

void Texture::PSSet(UINT slot)
{
    // 텍스터에 픽셀 셰이더를 지정하는 함수

    // DX에서 컴퓨터는 코드를 비트맵에 그대로 쓰는 게 아니고 해석을 해야 되고, 한다
    // -> 이 때, 색을 해석하는 과정과 그 호출, 구성 등을 통칭해서 셰이더라고 한다
    // -> 만들어진 출력의 각 픽셀(=도트)의 구성색을 지정하는 셰이더를 픽셀 셰이더라고 한다

    DC->PSSetShaderResources(slot, 1, &srv);

    // PSSetShaderResources -> DX에서 사용하는 픽셀 셰이더 지정 함수 (부르기만 하면 OK)
    // 매개변수
    // srv : "셰이더 리소스 형태(뷰)" 원본 이미지를 컴퓨터가 어떻게 (1차) 해석했는지에 대한 데이터
    // 1 : 사용되는 srv의 갯수. 경우에 따라서는 이후 2개 이상의 이미지가 필요한 경우가 생기기도
    // slot : 셰이더의 '슬롯'을 지정하는 값
    // * 슬롯 : 컴퓨터가 동일한 종류의 데이터가 여럿 있을 때, 해당 데이터를 무한히 겹쳐 연산하지 않도록
    //          연산할 메모리 부위를 미리 할당해 두고, 거기서만 작업이 수행되게 만든 공간

    // 셰이더를 지정하면, 나중에 Shader 폴더에 있는 .hlsl (고수준 셰이더 언어) 파일에서 출력 연산을 진행

    // -> 그래서, 결국....

    // 이 함수가 호출되면, 텍스처에 저장된 이미지 데이터가 픽셀 셰이더를 부여받고
    // 컴퓨터에서 연산된 후, -> 모니터에 나타나게 된다. 간단히 말하면 "이제 그려라"라는 뜻이기도 하다
}

Texture* Texture::Add(wstring file)
{
    // 맵에 원소를 집어넣는 것과 동일하다 (unordered map이니까)

    // 제일 먼저, 원소가 이미 있으면 건너뛰기 (+ 있는 거 그냥 쓰기)
    if (textures.count(file) > 0)
        return textures[file]; // []는 맵에서 순번이 아니고, key에 대응한 value

    ScratchImage image; // 컴퓨터가 해석한 이미지를 저장할 데이터
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image); // 파일에서 이미지를 읽은 후 저장

    ID3D11ShaderResourceView* srv; // 이것도 컴퓨터가 해석한 이미지 데이터....

    // ....왜 이렇게 종류가 많은가????? : 자체 투명색 적용, 다른 이미지와의 합성, 모니터와의 연계....
    //                                  혹은 "그런 추가 기능이 적용되지 않은 최초의 이미지" 등
    //                                  컴퓨터 입장에서도 보존해야 되는 중간 데이터가 많아서 그렇다...

    // 이렇게 만든 리소스 형상을 셰이더와 연계하는 데이터로 만든다
    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    // 다 만들어진 "그림" 데이터를 맵에 집어넣는다
    textures[file] = new Texture(srv, image, file); // <- Texture 생성자를 여기서 쓴다.
                                                    // 다른 말로, 밖에서는 Texture 생성자보단 여기 이
                                                    // Add 함수를 더 많이 쓰게 될 것.

    return textures[file];  // 다 추가된 이미지를 반환하면 함수 역할 끝.

    // 요약하면 : 1. 파일 원본에서 이미지를 읽는다.
    //           2. 컴퓨터가 해석한다. (그 과정에서 DX가 제공한 자료형들이 동원된다)
    //           3. 맵에 다 해석된 이미지 데이터를 추가한다.

    //           4. 이 결과를 밖에서 호출한다

    // 그러므로 : 해석이나 맵 구성 등이 달라져야 한다면, 여기로 오면 된다.
}

void Texture::Delete()
{
    // 텍스처 데이터를 지우고, 포인터를 삭제하는 코드

    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}
