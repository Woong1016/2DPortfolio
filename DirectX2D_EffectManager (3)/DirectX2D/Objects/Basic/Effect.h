#pragma once

// 이펙트 클래스 : 프레임과 클립으로 구성된 단방향 애니메이션
//                -> 무조건 일정하게, 무조건 한쪽 흐름으로만, 무조건 정해진 설정대로만 재생

class Effect : public Quad
{
private:
    const float FPS = 10.0f; // 초당 프레임

    // 그림 데이터를 메모리에 올려두기 위한 클래스(Buffer라는 이름으로 만들고 인스턴스를 띄우면 변수화)
    class FrameBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Vector2 maxFrame;
            Vector2 curFrame;            
        };

    public:
        FrameBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        void SetMaxFrame(Vector2 maxFrame) { data.maxFrame = maxFrame; }

        Vector2& GetCurFrame() { return data.curFrame; }

    private:
        Data data;
    };

public:
    Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive);
    ~Effect();

    // 그림 재생용 함수들 (애니메이션과 동일)
    void Update();
    void Render();

    void Play(Vector2 position);
    void End();

private:
    FrameBuffer* frameBuffer;    

    float delayTime = 1.0f / FPS;
    float frameTime = 0.0f;
    float speed;

    UINT curFrameNum = 0;
    UINT maxFrameNum = 0;

    UINT maxFrameX = 0;

    // 이펙트 전용 별도 데이터
    bool isAdditive; // 화소 누적 표현인가 여부

                     // 화소 누적 (애디티브, 화소 적층) : 색조와 밝기 등의 화소 데이터를 기존 데이터에 추가하는 방식
                     // -> 결과적으로 이펙트가 희미해지는 대신, 밝아진다
};