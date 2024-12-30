#pragma once

// 총알 관리 클래스

class BulletManager : public Singleton<BulletManager> // 이 클래스를 유일무이하게
{
private:
    friend class Singleton; // friend class : "이 이름으로 지정된 클래스는 나하고 친구입니다"
                            //                -> 해당 클래스의 private 데이터를 쓸 수 있게 해준다

    BulletManager();
    ~BulletManager();

public:
    void Update();
    void Render();

    void Fire(Vector2 pos, Vector2 direction); // 비행기의 발사 함수
                                               // (비행기의 총알 관리 기능을 독립시킨 것)
    void EnemyFire(Vector2 pos, Vector2 direction); // 적의 발사

    // Get() 등 싱글턴 자체로서 있어야 할 함수는 싱글턴 클래스 내에 이미 존재 (그걸 위한 friend)

    void CollisionBullets();    // 총알과 다른 총알 사이의 충돌 감지 (내부 통합)
                                // 여기 있는 데이터끼리만 쓸 테니 결과 반환 불필요
    bool CollisionBulletToOther(Collider* collider);  // 총알(들)이 다른 물체에 부딪치면?

private:

    vector<Bullet*> bullets; // 총알 (등장인물과 별개로 게임에 등록될 데이터)
    vector<EnemyBullet*> enemyBullets; // 적의 총알

    // 다른 총알이 필요하면 역시 여기서 벡터 작성 후에 호출하면 끝

};

