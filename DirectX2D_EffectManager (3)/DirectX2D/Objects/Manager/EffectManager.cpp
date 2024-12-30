#include "Framework.h"

EffectManager::~EffectManager()
{
    // 맵 속에 벡터가, 벡터의 원소로서 포인터가 있었으므로 지우기

    for (pair<string, Effects> effects : totalEffect)    // 벡터의 이름을 typedef로 줄여서 간단 호출 가능
    {
        for (Effect* effect : effects.second) // 각 페어의 값 데이터를 통해 이펙트 포인터 접근
        {
            delete effect;  // 포인터 지우기
        }
    }
}

void EffectManager::Update()
{
    for (pair<string, Effects> effects : totalEffect) // 맵을 구성하는 각 페어에 접근
    {
        for (Effect* effect : effects.second)   // 페어에서 실질 데이터를 구성하는 이펙트에 접근
        {
            effect->Update();   // 이펙트 갱신
        }
    }
    // 이렇게 맵을 돌면서 안에 있는 이펙트 전부 갱신
}

void EffectManager::Render()
{
    for (pair<string, Effects> effects : totalEffect) // 맵을 구성하는 각 페어에 접근
    {
        for (Effect* effect : effects.second)   // 페어에서 실질 데이터를 구성하는 이펙트에 접근
        {
            effect->Render();
        }
    }
}

void EffectManager::Add(string key, UINT poolSize, wstring textureFile, float maxFrameX, float maxFrameY, float speed, bool isAdditive)
{
    // 중복 데이터가 있는지 검사
    // 1. 데이터를 찾아서, 존재하면 (find 함수 사용)
    // 2. 해당 데이터에 속하는 결과가 1개 이상이면 (=이러나 저러나 있다는 소리) : 아래 코드
    if (totalEffect.count(key) > 0) // 데이터에 맞는 결과가 1개 이상!
        return;                     // 이미 있는 데이터 ("같은 이름으로 된 이펙트가 이미 존재합니다~") -> 강종

    // * 맵은 어차피 중복 데이터를 추가해주지 않지만... 그래도 이렇게 강종을 시키면 시간을 더 절약 가능

    // -> 중복이 없으면 진짜 추가 과정을 실행

    Effects effects(poolSize);  // -> vector를 poolSize만큼 만들고 리셋

    for (Effect*& effect : effects) // 벡터 내 모든 원소에 실제 데이터로서 접근
    {

        effect = new Effect(textureFile, Vector2(maxFrameX, maxFrameY), speed, isAdditive);
    }

    // -> 여기까지 오면 새 이펙트 'effects'가 완성
    // -> 이 데이터를 key와 함께 맵에 넣으면 끝

    totalEffect[key] = effects; // 맵에 새 key와 value(=effects) 추가
}

void EffectManager::Play(string key, Vector2 position)
{
    // 데이터가 존재하는지 확인하고... "데이터가 없으면 강종."
    if (totalEffect.count(key) == 0) return; // 세어봤는데 0개면 없다는 이야기

    for (Effect* effect : totalEffect[key]) // key로 등록된 이펙트만 접근
    {
        if (!effect->Active()) // 애니메이션이니까, "트랜스폼" 존재 + 실행 여부 판별 후
        {
            effect->Play(position); // 아직 실행 중이 아니었으면 지정된 위치에서 실행하기
            return;                 // 실행 지시가 이미 끝났으므로, 지시를 내린 후 종료
        }
    }
}

void EffectManager::SetColor(string key, float r, float g, float b, float a)
{
    // 데이터가 존재하는지 확인
    if (totalEffect.count(key) == 0) return;

    for (Effect* effect : totalEffect[key]) // key로 등록된 이펙트만 접근
        effect->GetColor() = { r, g, b, a };    // 매개변수로 받은 색 정보 전달하기

}
