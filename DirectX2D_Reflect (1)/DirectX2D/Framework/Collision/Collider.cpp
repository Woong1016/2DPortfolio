#include "Framework.h"

Collider::Collider()
{
    // vertexBuffer; // 이건 셰이더 + 정점의 데이터인데
                     // 셰이더는 : 밑에서 만들었음
                     // 정점은???? 아직 모양도 안 만들었으니까 (각 자식 클래스에서 따로 모양 지정)

    // 이 클래스로 만든 객체가 어떤 방식으로 보여야 하는지 지정하는 코드 (셰이더 세팅)
    vertexShader = Shader::AddVS(L"VertexPos.hlsl"); // 헤더에서 만든 VertexPos에 맞춰서
    pixelShader = Shader::AddPS(L"PixelPos.hlsl");  // VertexPos : 위치 중심의 정점 데이터
                                                    // (위치가 중요한 영역 계산 등에 쓸 만)

    worldBuffer = new MatrixBuffer();   // 원점에서 공간 생성 (기본값)
    colorBuffer = new ColorBuffer();    // 색 데이터 생성

    //색 기본값 정하기
    colorBuffer->Get() = { 0.0f, 1.0f, 0.0f, 1.0f }; // 초록색. { 0, 1, 0, 1 } 가능
                                                     // 마지막 숫자는 가시성(alpha)
}

Collider::~Collider()
{
    delete vertexBuffer;
    
    // delete vertexShader; // <- 싱글턴과 비슷하게, 다른 곳에서 관리되고 지워지는 대상
    // delete pixelShader;
    
    delete worldBuffer;
    delete colorBuffer;
}

void Collider::Render()
{
    if (!isActive) return; // 트랜스폼으로써 비활성화 시 연산 없음 (안 그림)

    //게임오브젝트처럼 충돌체도 자기 공간을 설정하고 출력하면 된다
    worldBuffer->Set(world);    // 행렬 설정에 필요한 데이터를 가진 공간 데이터로 입력 (=트랜스폼)
    worldBuffer->SetVS(0);      // 이 물체를 출력할 때, 셰이더가 앱의 몇 번째 슬롯을 쓰는지 (위치)
    colorBuffer->SetPS(0);      // (=트랜스폼, 게임오브젝트) (도트는 색깔까지)

    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    // 정점 출력 방식을 다이렉트 X의 옵션 중에서 골라 설정
    // 이번에 사용한 옵션 : PRIMITIVE_TOPOLOGY_LINESTRIP, "선 표시에 의한 기본 도형 출력"
    // PRIMITIVE : 데이터를 기본 도형의 재료와 결과로 취급합니다.
    // TOPOLOGY : 위치와 좌표에 대한 수학, 위상수학을 의미 (개발 중에는 큰 의미는 없음. 기본도형 출력시 필요하다고 함)
    // LINESTRIP : 외곽선 표시를 중심으로 한다는 뜻

    vertexShader->Set();    // 셰이더 세팅 (준비)
    pixelShader->Set();     // 정점->픽셀 순

    DC->Draw(vertices.size(), 0); // 모니터가 이 도형을 그리도록 지시
                                  // vertices.size() : 정점 데이터를, 올라간 크기만큼 (=전부 다)
                                  // 0 : 0번째 원소부터 (= 그러니까, 전부 다)
}

bool Collider::IsCollision(Collider* collider)
{
    // 충돌 판정의 과정

    // 둘 다 충돌이 필요한 (활성화된 상태인지) 판정
    if (!Active()) return false;
    if (!collider->Active()) return false;

    // 열거형을 조건문으로 나누어서 생각해보기
    switch (collider->type) // 부딪친 상대의 유형에 따라
    {
    case Collider::Type::RECT:  // 이 클래스의, enum clss "유형"의, 사각형이라면 (enum class 호출)
                                // Collider:: 까지 호출하는 경우는 다른 자식 클래스끼리도 비교시키려고

        return IsRectCollision((RectCollider*)collider); // 인터페이스 일부였던 충돌체를 본래의 자식 클래스로 형변환
        
        // break; // 윗줄에서 return을 실행하면 여기까지 컴퓨터가 볼 리가 없다
        
        // -> 이로써 사각형 충돌 여부를 별도 함수로 판별하고 그 결과를 그대로 호출한 곳으로 반환해준다

    case Collider::Type::CIRCLE:
        return IsCircleCollision((CircleCollider*)collider); // 원인 경우

    }

    // 여기까지 왔다면 가능한 경우는 하나뿐
    // collider에 부적절한 type 데이터가 들어갔다 -> 우리가 의도한 설정이 아니다

    return false;   // 그러므로 충돌 여부는 고려하지 않는다
}
