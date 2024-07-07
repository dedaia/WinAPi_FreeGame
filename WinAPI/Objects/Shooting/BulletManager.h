#pragma once

class BulletManager : public PoolingManager, public Singleton<BulletManager>
{
public:
    BulletManager();
    ~BulletManager();

    virtual void CreateObjects(string key, UINT poolSize) override;

    void Fire(const Vector2& pos);
    void Fire(const Vector2& pos, const Vector2& direction);

    bool Collision(const GameObject* object, string key);

    void CollisionBullet(string key1, string key2);
};