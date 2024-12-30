#pragma once
class Bullet : public Quad
{

public:

    Bullet();
    ~Bullet();

    void Update();
    void Render(); // 여기까진 이제 공식

    void Fire(Vector2 pos, Vector2 direction); // 발사가 되면 일어나는 일

    Collider* GetCollider() { return collider; } // 충돌체 외부 참조용 겟터
    Vector2& GetDir() { return direction; }      // 속도(방향)를 얻기 위한 겟터

    // 여기서 다시
    // &와 *

    // & : 선언에서 사용하면, 데이터의 실체를 직접 다룬다는 뜻. 호출에서 사용하면, 데이터가 있는 곳(참조)
    // * : 선언에서 사용하면, 데이터가 있는 곳(주소), 호출에서 사용하면, 호출된 주소에 있는 데이터(역참조)

private:
    // 별도 함수 불필요 = 업데이트에서 다 한다
    // 총알은 복잡하게 움직이지 않는다 = 그냥 날아가고, 부딪치면 xxx한다

    // 속력은 필요!
    float speed = 300.0f;

    // 방향
    Vector2 direction;

    // 충돌체 써보기
    Collider* collider; //충돌체! (인터페이스)
};

