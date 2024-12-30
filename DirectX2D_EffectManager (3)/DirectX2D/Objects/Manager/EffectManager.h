#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
    friend class Singleton; // 부모 클래스의 private 접근

    EffectManager() = default;  // 싱글턴이니까 생성자가 별도의 데이터 설정이 있으면 부담
    ~EffectManager();

public:
    // 관리자 (접근 '대상') 함수
    void Update();
    void Render();

    // 이펙트 관리 함수

    void Add(string key, UINT poolSize, wstring textureFile, float maxFrameX, float maxFrameY,
        float speed = 1.0f, bool isAdditive = false); // 이펙트 추가
    // 위에 사용된 매개변수 중 speed : 속도 계수 (속도값만큼 원래 FPS에 적용)
    // isAdditive : 화소를 누적할 것인가 (반투명일 때, 해당 색을 더해서 보정할지, 별개로 투사할지)

    void Play(string key, Vector2 position);    // 이펙트 재생하기
    void SetColor(string key, float r, float g, float b, float a = 1); // 색이 달라져야 할 경우 실행하는 함수
                                                                       // = '팔렛 스왑'

private:
    
    // 아래 두 줄 코드는 기본 사용 형태
    //vector<Effect*> effects; // 있으면 편하지만 필수는 아님
    //unordered_map<string, vector<Effect*>> totalEffects; // 이펙트 전체 데이터 모음

    //위 코드를 간이 형태로 줄인 것
    typedef vector<Effect*> Effects;    //vector<Effect*>를 지금부터 Effects라는 철자로 명명
    unordered_map<string, Effects> totalEffect; // <- 호출도, 사용도 간단해진다
};

