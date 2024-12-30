#pragma once

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();
        
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:    // 이 씬에서만 쓰이는 내부용 함수

    void CheckCollision();

private:

    //Rect* rect; // DX에 빼앗긴 "렉트"란 이름... 갑자기 왜?
                  // 이번 프레임워크에서는 더 일반적인, 강화된 DX를 쓰고 있기 때문!
                  // (라이브러리 폴더에 그림 파일, 텍스처를 관리하는 DX-Tex 기능이 추가됨)

    // 이제 rect가 아닌, 새로운 이름으로, 더 많은 기능을 써줘야 하고...... 쓸 수 있다!

    // 다시 말해, 우리는 이제 다이렉트X로 그림을 표현할 수 있다.


    // 그림을 가진 사각형 출력....을 해보자

    //Quad* plane;

    Plane* plane;   // 자기 클래스가 이제 있는 비행기로
    
    Enemy* enemy;   // 이제 적 등장!
    Enemy* enemy2;   // 적2도 등장!
};