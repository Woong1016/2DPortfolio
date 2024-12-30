#include "Framework.h"

Quad::Quad(Vector2 size, Vector2 pos)
{
    // 기본 사각형 만들기 (그림 없음)
    CreateMesh(size, pos); // 크기, 위치 순으로 사각형 만들기
}

Quad::Quad(wstring file, Vector2 pos)
{
    // 그림 있는 사각형 만들기 (파일 원본 있음)

    SetTexture(file); // 그림 입히기 함수를 불러서 최초 그림 설정
    size = texture->GetSize();  // 텍스처에 등록된 데이터에서, DX에 있는 기능을 써서, 이미지 크기 확인
    CreateMesh(size, pos);     // 사각형 모양 만들기
}

Quad::~Quad()
{
    // 텍스처를 지워야 한다. 원래는 (포인터니까)
    // -> 텍스처의 경우, 정적 데이터라서 여기서 막 지우다가 오류 날 수 있다 (다른 곳에서 그림을 쓴다든가)
    // -> 앱이 끝나면 정적 데이터를 싹 지우는 절차가 사실 있다 : 그래서 텍스처는 괜찮다
}

void Quad::Render()
{
    texture->PSSet();   // "그림을 그려라"라는 호출을 진행 (과정은 텍스처 클래스에서 확인)

    // 나머지 게임 사물로서의 데이터도 출력 진행을 해주면 된다
    GameObject::Render(); // 부모 클래스의 같은 이름 함수
}

void Quad::SetTexture(wstring file)
{
    // 텍스처 변수에 데이터 할당 + 앱 메모리에 이미지 등록
    texture = Texture::Add(file); // 클래스에 이미지를 등록하고, 반환된 이미지를 변수에 넣으면 끝.
}

void Quad::CreateMesh(Vector2 size, Vector2 pos)
{

     // 위치를 중심점으로 삼아서 네 기점을 만든다

    float left = pos.x - size.x * 0.5f; // 중심에서, 주어진 크기의 반만큼, 왼쪽으로 가면 좌단
    float right = pos.x + size.x * 0.5f;    // 우단
    float top = pos.y + size.y * 0.5f;  // 상단 (DX니까 +- 뒤집을 필요 없음)
    float bottom = pos.y - size.y * 0.5f; // 하단

    // 네 기점에서 짐작되는 꼭짓점 데이터를 벡터에 집어넣는다
    // * 지난 버전과 달리 꼭짓점 데이터와 같이 들어가는 벡터의 구성이 조금 다르다
    // * 'emplace_back' : 벡터의 push_back과 비슷한데, 메모리를 가능한 범위에서 덜 옮기는 함수
    vertices.emplace_back(left, top, 0, 0);
    vertices.emplace_back(right, top, 1, 0);
    vertices.emplace_back(left, bottom, 0, 1);
    vertices.emplace_back(right, bottom, 1, 1);

    // 벡터 원소 추가에서 사용된 뒤쪽 매개변수 ({0, 0}, {1, 0} 등)....
    // -> 이것이 UV좌표. 지정한 꼭짓점이 (left+top 등) 그림으로 치면 어디인지 지정하는 것.
    //    UV 좌표는 0이 최소, 1이 최대 따라서....
    // vertices.emplace_back(left, top, 0, 0) <- 여기서 0, 0은 곧 그림의 최고 왼쪽 위라는 뜻
    // vertices.emplace_back(right, bottom, 1, 1) <- 여기서 1, 1은 그림의 최고 오른쪽 아래라는 뜻

    // 이 정점들을 화면이 출력하도록 3개씩 순서를 지정해주면 된다 (삼각형 + 삼각형)

    indices = { 0, 1, 2, 2, 1, 3 }; // 012 삼각형 + 213 삼각형

    // 다 만든 정점 데이터와 순번(읽을 점 순서) 데이터를 메모리에 등록하면 끝
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    // 벡터의 데이터를, 벡터라는 자료형 크기를 기준으로, 벡터 속 원소 개수만큼 메모리에 등록한다는 뜻
    indexBuffer = new IndexBuffer(indices.data(), indices.size()); // int라서 기준 생략
}
