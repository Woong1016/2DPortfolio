#pragma once

// 사각형 충돌체

class RectCollider : public Collider
{
public: // 데이터

    struct ObbDesc  // 원과 사각형 사이의 위치 관계를 나타낼 때 기록하는 중간 데이터 (구조체)
                    // O(원) + BB(가로, 세로) 둘이 부딪친 상황에 대한 서술(Description)
    {
        Vector2 position;   // 위치
        Vector2 axis[2];    // 축의 벡터 (부딪친 사각형 쪽에서 X, Y 좌표가 어느 방향이냐)
        Vector2 halfSize;   // 부딪친 도형의 절반 크기 (위치, 변 계산 등에 쓰인다)
    };

public: // 기능

    RectCollider(Vector2 size);
    ~RectCollider() = default;

    // 충돌 함수 실구현 준비
    virtual bool IsPointCollision(Vector2 point) override;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) override;
    virtual bool IsCircleCollision(class CircleCollider* circle) override;

    // 데이터 외부 참조용
    Vector2 Size() { return size * GlobalScale(); } // 이 콜라이더가 적용된 물체의 크기까지 반영한 최종크기
    Vector2 Half() { return Size() * 0.5f; }    // 위 함수 결과의 절반

    // 꼭짓점 정보들
    Vector2 LeftTop();
    Vector2 LeftBottom();
    Vector2 RightTop();
    Vector2 RightBottom();

    // 변 위치 (길이)
    float L();
    float R();
    float T();
    float B();

    // OBB 확인용
    ObbDesc GetObb();

private: // 기능

    // 추가 판별용 함수가 필요 : 내가 사각형인 건 확정. 그러면...
    // 나하고 부딪친 상태가 사각형인가? 아니면 원인가? 를 판별할 필요가 있다

    bool IsAABB(RectCollider* rect, Vector2* overlap);  // AA(가로세로가 있는 직사각형) 대
                                                        // BB(같은 직사각형)으로 표현 가능한 관계인가?

    bool IsOBB(RectCollider* rect);                     // O + BB, 원과 직사각형 사이의 관계인가?

    bool IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2);
                                                        // 한쪽 사각형이 비뚤어져 있을 때,
                                                        // 다른 쪽 도형과 꼭짓점이 걸쳐져 있는지
                                                        // = 대각선에 의한 충돌이 벌이지고 있는지
                                                        // 판별하기 위한 2차원 계산을 위한 함수

private: // 데이터

    Vector2 size;   // 충돌체의 크기 (혹은 "어디서부터 어디까지가 물체인가?"에 대한 영역 지시)

    ObbDesc obbDesc;    // 구조체 실물 데이터

};

