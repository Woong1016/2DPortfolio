#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size)
{
    type = Type::RECT;  // 유형 정하기 (사각형으로)

    Vector2 halfSize = size * 0.5f; // 꼭짓점 내기용 절반 크기 반영 연산

    // 연산된 절반 크기를 기존 꼭짓점으로 지정 (그리고 정점 목록에 추가)
    vertices.emplace_back(-halfSize.x, +halfSize.y);    // 뒤의 +는 사실 필요 없지만, 칸 맞추려고 넣음
    vertices.emplace_back(+halfSize.x, +halfSize.y);    // 윗줄은 왼쪽 위, 이 줄은 오른쪽 위
    vertices.emplace_back(+halfSize.x, -halfSize.y);    // 오른쪽 아래
    vertices.emplace_back(-halfSize.x, -halfSize.y);    // 왼쪽 아래
    vertices.emplace_back(-halfSize.x, +halfSize.y);    // 돌아서 다시 왼쪽 위

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), // VertexPos : 콜라이더 기준 꼭짓점
        vertices.size());

}

bool RectCollider::IsPointCollision(Vector2 point)
{
    // 지정된 점이 단순히 사각형의 영역 안에 있으면 그만 (그것도 x, y만 보면 된다)

    // 공통 공간

    Matrix invWorld = XMMatrixInverse(nullptr, world);  // '내' 공간을 기초로 한 역행렬=역공간
                                                        // =다른 정보에 곱해서 한 공간에 넣으려고
    point *= invWorld;                                  // <- 이렇게.

    // 이걸로 점과 사각형이 한 공간을 공유한다
    // 이 점이 사각형의 x, y 범위 안에 있는지만 보면 그만

    Vector2 half = Half();

    // 절대값으로 정해진 point의 좌표가, 사각형의 1사분면에 들어왔는지 계산
    return ((abs(point.x)) < half.x && abs(point.y) < half.y);

    // -> 계산이 복잡해진 이유 : 충돌체가 자기 공간에서 차지하는 위치가 주어지지 않아서
    //                         다른 말로 충돌체의 영역이 자기 공간 내에서 존재하는 위치는 여전히 0, 0
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap) // 교집합이 발생했거나, 미리 주어져 있으면(호출 단계에서 예상되면)
        return IsAABB(rect, overlap);   // 직사각형끼리 견줘보고 교집합 크기에 따라 판별을 한다
    
    // overlap이 없다면? 교집합이 없을 수 있거나, 적어도 호출 단계에서 예상 가능하진 않았다
    // -> (말은 사각형이지만) 원과 사각형이거나, 사각형끼리지만 대각선 배치에 따라 교집합이 유동적

    return IsOBB(rect); // OBB 함수로 해결
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    // 원 충돌은 다음 기회에.....

    return false;
}

Vector2 RectCollider::LeftTop()
{
    //영역상의 극단 : 계산상만이 아니라 공간 내에서 고려해야 할 가장 바깥 좌표

    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f; // 여유까지 감안한 최고 극단점
    // edge는 원점이 0, 0인 걸로 되어 있으므로, 공간까지 감안하기 위해 world를 곱하고 반환
    // (내 공간 -> 진짜 공간 순으로 곱을 하면 새 정보(지금의 경우, "내 위치")를 추가)
    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;
    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;
    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;
    return edge * world;
}

float RectCollider::L() // 전체 내에서 내 극단점이 가진 최대 극단점 (이 경우, '가장 왼쪽 점')
{
    // 이 연산을 통해서 얻을 수 있는 부가 장점 : 그림이 위아래가 뒤집혀도 왼쪽을 찾을 수 있다!
    
     // 사각형을 둘러싼 좌상 극단과 좌하 극단 중에서 "왼쪽"에 더 가까운 (x가 적은) 고른다
    float minLeft = min(LeftTop().x, LeftBottom().x); // min : 윈도우 매크로. 주어진 숫자들 중 제일 작은 수를 의미
    
    // 우상 극단과 우하 극단도 비교해서 더 왼쪽 점을 고른다
    float minRight= min(RightTop().x, RightBottom().x);

    //비교한 두 극단 중에서 다시 더 적은(=더 왼쪽인) 극단을 고른다
    return min(minLeft, minRight);
}

float RectCollider::R()
{
    // 우, 상 하 극단도 위쪽 함수와 동일, 좌표와 비교만 다르게
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);
    return max(maxLeft, maxRight);
}

float RectCollider::T()
{
    float maxTop = max(LeftTop().y, LeftBottom().y);
    float maxBottom = max(RightTop().y, RightBottom().y);
    return max(maxTop, maxBottom);
}

float RectCollider::B()
{
    float minTop = min(LeftTop().y, LeftBottom().y);
    float minBottom = min(RightTop().y, RightBottom().y);
    return min(minTop, minBottom);
}

RectCollider::ObbDesc RectCollider::GetObb() // ObbDesc 자료형에 클래스명을 명시해서 소속제시=오류해결
{
    // OBB 구조체 데이터 참조

    obbDesc.position = GlobalPos(); // 일단 반환 중에는 '상대'가 없다 -> 일단 내 정보
                                    // 많은 경우 이 정보가 그대로 쓰이기도 (상대 쪽에서 내 정보를 참조)
                                    // 혹은 필요하면 외부에서 추가 수정을 해도 된다

    obbDesc.halfSize = Half();  // 절반 크기

    obbDesc.axis[0] = Right();  // X축
    obbDesc.axis[1] = Up();     // Y축

    return obbDesc;
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    // 사각형끼리 부딪친 건지 여부 판별

    Vector2 halfSize = Size() * 0.5f; // 절반 크기 먼저 내기

    // 부딪친 도형의 교집합 내기
    float minRight = min(R(), rect->R()); // 두 사각형의 두 우극단 중, 더 왼쪽에 있는 것
    float maxLeft = max(L(), rect->L());  // 좌, 상, 하 모두 더 반대쪽인 것을 구하면 -> 교집합 내기
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    // 그 교집합의 크기를 본다
    overlap->x = minRight - maxLeft;
    overlap->y = minTop - maxBottom;

    // 이렇게 나온 교집합에 '눈에 보이는 형태' 즉 크기가 있으면??
    if (overlap->x > 0 && overlap->y > 0)
        return true;        // 직사각형 간의 충돌이다.

    // 그렇지 않으면 (여기까지 오면 overlap에 한 축 이상 크기가 0이하)??
    return false;   // 적어도 직사각형끼리 충돌한 상황은 아니다.
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    // 이 함수를 실행해야 되는 상황?
    // 1. 상대방이 진짜 원일 때.
    // 2. 사각형끼리 인접했는데 (어쩌면 대각선이 살짝 들어왔을지도??) 모양, 방향 관계 때문에 교집합 X

    // -> "직사각형끼리 꽝 부딪치고 교집합이 생긴 건 아닌데, 딱 잘라 원인지도 애매한 상황)

    ObbDesc obbA = GetObb();    // 이 사각형의 도형 정보를 OBB 구조체에 기록
    ObbDesc obbB = rect->GetObb();

    if (IsSeperate(obbA.axis[0], obbA, obbB)) return false; // 인접도 아니고, 교점도 없을 거고...
    if (IsSeperate(obbA.axis[1], obbA, obbB)) return false; // 다른 축에도 한번 더 계산 (검산)

    // (필수는 아니지만) 기분상 검산 2회 더
    if (IsSeperate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[1], obbA, obbB)) return false;

    // 여기까지 오면서 '분리'라는 결과가 한 번도 안 나왔다면???
    // -> 교점이 분명히 나온 게 맞다. = 충돌 관계가 의심스럽다

    return true;    // 좀 더 보자 (혹은 "OBB 관계로 판별을 하자")
}

bool RectCollider::IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2) // 축 분리법
{
    // 기준축과 관측축을 내고 그에 따른 거리 점곱 관계를 본다 (SAT) ...는 연산으로 위치 관계 파악

    // * 축은 매개변수로 받는다.

    // 거리 내기 (d) : DX의 점곱 함수(의 간이화) 사용
    float d = abs(Dot(seperateAxis, box1.position - box2.position));

    // Dot (V1, V2) : 벡터 V1과 벡터 V2의 점곱 결과를 표시
    // abs(f) : 매개변수 f를 절대값으로 바꾸는 DX 수학 함수 및 여기서의 간이화
    // * 비슷한 호출과 기능들이 다른 엔진에도 많이 있으므로, 이런 수학 관련 호출은 미리 봐두길 추천

    // 두 축 분리 (x도 있고 y도 있으니까) - 하나의 기준에 대해 X 입장, Y 입장으로 계산

    Vector2 right = box1.axis[0] * box1.halfSize.x; // 한쪽 상자의 축에 현재 영역 크기 반영
    Vector2 up = box1.axis[1] * box1.halfSize.y; // 순서 무관

    //이에 따라 첫 상자와 관측축 간의 점곱을 낸다

    float a = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    // 위 과정을 상자 2에도 적용 (위쪽이 상자 2였으면 지금은 1)

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    // 두 상자의 관측축에 대한 점곱 결과가 a, b로 정리되었다
    // 이 결과를 거리 d와 비교해서 겹치는지 아닌지 보면 된다

    return d > (a + b); // 더 크면 "축분리법에 의해, 두 도형은 [분리]되었다"고 판단
}
