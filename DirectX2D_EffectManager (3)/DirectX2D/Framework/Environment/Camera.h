#pragma once

// 카메라 클래스 : 시야 공간과 실제로 계산된 가상의 행렬 공간 사이에
//                의도적인 위치 불일치를 만들어서 결과적으로 시야가 이동하는 효과를 구현하는 것을 목적으로 한 클래스

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void SetView();

    // 트랜스폼이 가지고 있을 법한 건 대부분 가지고 있다 (특히 렉트, 쿼드)
    void SetTarget(Transform* target) { this->target = target; }
    void SetOffset(float x, float y) { targetOffset = { x, y }; }
    void SetLeftBottom(float x, float y) { leftBottom = { x, y }; }
    void SetRightTop(float x, float y) { rightTop = { x, y }; }
    void SetDeviceSize(float x, float y) { deviceSize = { x, y }; } // 출력 대상 영역의 크기

    Vector2 ScreenToWorld(Vector2 pos);
    Vector2 WorldToScreen(Vector2 pos);

    void SetDevMode(bool value) { isDevMode = value; }  // 완전 개발자 모드를 on/off
                                                        // 개발자 모드 : 임시 전용 기능
                                                        // 기능에서 구현된 한계를 무시하고 100% 수동으로 카메라 조작

private:
    // 자유 조작 모드 여부 (외부에서 설정은 불가능, 카메라가 따라다닐 표적을 설정하면 자동으로 같이 설정)
    // -> 표적이 설정되면 해당 표적 물체를 쫓아다니고, 그렇지 않으면 자유 조작 상태가 된다
    void FreeMode();            // 표적이 없을 때
    void FollowMode();          // 표적이 있을 때

    void FixPosition(Vector2& position);    // 표적이 있든 없든 정해진 위치를 멋대로 벗어나지 않게 고정하는 역할
                                            // (외부에서 신경 안 써도 무방)

private:

    // 카메라 구현의 핵심 아이디어
    MatrixBuffer* viewBuffer;
    Matrix view;

    float speed = 100.0f;
    bool isDevMode = false;

    // 카메라 유형 설정의 핵심 : 추적 대상
    Transform* target = nullptr;

    // 트랜스폼 데이터들
    Vector2 targetOffset = { CENTER_X, CENTER_Y };
    Vector2 leftBottom;
    Vector2 rightTop = { WIN_WIDTH, WIN_HEIGHT };
    Vector2 deviceSize = { WIN_WIDTH, WIN_HEIGHT };
};