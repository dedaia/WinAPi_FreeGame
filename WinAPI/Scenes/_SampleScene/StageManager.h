#pragma once

class StageManager : public PoolingManager, public Singleton<StageManager>
{
private:

    //�������� �ʴ� ������ �����ϴ� ���
    enum TileType
    {
        //0 : ���� (�̵� ����)
        //1 : ���� (���� �� ����)
        //2 : ������ ������
        //3 : ��ֹ� (����� �� ���ų�, �ε�ġ�� ����)
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
