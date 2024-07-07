#pragma once

class StageManager : public PoolingManager, public Singleton<StageManager>
{
private:

    //움직이지 않는 지형을 지정하는 방법
    enum TileType
    {
        //0 : 없음 (이동 영역)
        //1 : 지면 (밟을 수 있음)
        //2 : 집어드는 아이템
        //3 : 장애물 (통과할 수 없거나, 부딪치면 피해)
        NONE, GROUND, PICKUP, OBSTACLE
    };

    friend class Singleton;

    StageManager() = default;
    ~StageManager() = default;

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Move(float _x, float _y);

    float GetGroundHeight(Vector2 pos);
    void CollisionPickup(GameObject* object);
    bool CollisionObstacle(GameObject* object);

    void LoadTileData(string file);

    float GetSpeed() { return speed; }
    bool IsPlay() { return isPlay; }

    void Play() { isPlay = true; }
    void Stop() { isPlay = false; }

    void SetAuto(bool value) { isAutoScroll = value; }

private:
    void CreateTile();

private:
    UINT width, height;
    Vector2 tileSize;

    vector<vector<TileType>> tileData;

    UINT score = 0;

    bool isPlay = true;

    bool isAutoScroll = false;
    float speed = 200.0f;
};
