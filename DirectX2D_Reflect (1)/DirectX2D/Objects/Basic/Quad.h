#pragma once

class Quad : public GameObject
{
    // 쿼드 : Rect를 대신해 앞으로 DX에서 직사각형을 나타낼 새 이름

public:

    Quad(Vector2 size, Vector2 pos = Vector2() );    // 읽을 파일이 없을 때, 기본 사각형을 그리는 함수
    Quad(wstring file, Vector2 pos = Vector2() );    // 그림 원본이 있을 때, 원본을 읽는 경우

    // * 함수 선언 중에, 매개변수에 값을 할당하는 행위를 디폴트 할당이라고 한다
    //   -> 매개변수에 해당 순서부터 값을 입력하지 않아도, 디폴트 값이 적용된다
    //      (이 경우, Quad 생성자 호출 시 pos를 입력하지 않으면 {0, 0}이 위치가 된다)

    // * 디폴트 할당의 주의점 : 디폴트 할당은 한 번 시작하면 더 뒤의 나머지 변수도 다 디폴트를 줘야 한다
    //   (즉 매개변수 1, 2, 3이 있는데 2번 변수에 디폴트를 주면, 3번도 줘야 한다. 안 주면 오류)

    ~Quad();

    virtual void Render() override;

    void SetTexture(wstring file);  // 텍스처를 입히거나 바꾸는 함수

    Vector2 Half() { return size * 0.5f; } // 사각형의 절반 (중심을 기준으로 계산할 때 쓰려고)

protected:
    // 겉보기 형상(메시라고 한다) 제작하는 함수 (그러니까, 정점으로 사각형을 그리겠다는 이야기)
    void CreateMesh(Vector2 size, Vector2 pos); // 생성자와 운구를 맞추기 위해, 크기->위치 순으로 매개변수


    // 그림 데이터
    Texture* texture = nullptr;

private:

    // 사각형이 사각형인 이유 : 사각형의 형태를 지정할 크기 데이터
    Vector2 size;

};

