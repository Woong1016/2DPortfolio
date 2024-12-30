#pragma once

// 충돌체 (충돌의 영역) : 데이터로 존재하는 각 객체에 배타적 공간이 있으면
//                       (실체일 수도 있고, 아무튼 오면 부딪칠 수도 있고)
//                       그 영역이 어디서부터 어디까지인지 나타내는 총괄 연산 클래스

class Collider : public Transform // 공간 데이터와 하나로 묶으면 편하므로 이 참에 그냥 상속 관계로 설정
{
protected:
    // 충돌체의 종류 지정용 데이터
    // enum Type
    enum class Type // enum class : 열거형을 고유 클래스 범위로만 사용하게 한정하는 것
    {
        RECT,   // 사각형
        CIRCLE, // 원
    };

    // 열거형을 enum class로 지정하면 사용할 때, 값을 무조건 클래스명으로 써야 하는 제약이 붙는다
    // (일종의 인터페이스라고 봐도 된다) 그 대신, 클래스명까지 있어야 하므로 값이 중복될 확률이 매우 낮아진다
    // Type::RECT; // <- 호출예시

public:

    Collider();
    ~Collider();

    void Render(); // 충돌체 영역이 눈에 보이도록 만들어주기 (개발자용)

    bool IsCollision(Collider* collider);

    // 상대방이 어떤 모양인지 봐 가면서 충돌 계산을 시도하는 종류별 맞춤 함수 (인터페이스)
    // * 매개변수의 class는 class 전방 선언을 매개 변수 안에서 해치운 것.
    //   즉 클래스 밖에서 'class RectCollider'라고 선언한 것과 효과가 같다. (=앞으로 이것도 만들어야 한다)
    virtual bool IsPointCollision(Vector2 point) = 0;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
    virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

    // 개발자용 영역 표시에서 색을 바꿀 필요가 있다면
    Float4& GetColor() { return colorBuffer->Get(); }

protected:
    Type type; // 충돌체의 유형

    //충돌체의 형태
    VertexBuffer* vertexBuffer; // 만들어진 정점들이 메모리에 등록되어 있도록 만드는 변수 (할당용)
    vector<VertexPos> vertices; // 정점 데이터들 (연산용)

private:

    // 끝난 계산이 화면과 공간에서 적용되기 위한 자료들
    
    // 눈에 보이게 하는 것 (=셰이더)
    VertexShader* vertexShader; // 데이터를 위치로 연산해준다
    PixelShader* pixelShader;   // 만들어진 위치 데이터를 도트로 바꿔준다

    // 공간 데이터 (+ 색)
    MatrixBuffer* worldBuffer;  // 공간 데이터를 메모리에 올린 것
    ColorBuffer* colorBuffer;   // 색 데이터도 메모리에 올려둬서 매번 연산하는 수고를 덜기로

};

