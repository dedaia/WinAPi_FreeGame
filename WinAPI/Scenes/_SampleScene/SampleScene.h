#pragma once
class SampleScene : public Scene
{
public:
    SampleScene();
    ~SampleScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    float Random_X();
    float Random_Y();

    void play_monster(vector<Plant_monster*> mon);
    void Atk_position(vector<Plant_monster*> mon);
    void Monster_Dead();
    void shield_eft();

    void MonsterSpawn();

    float second = 0.0f;
    int second2 = 0;
    int minute = 0;
    float atk_del;

    float X;
    float Y;

    float delat;
    bool si_she = false;

    int ala = 0;

    float spawn_count = 0;

    bool Wave1 = false;
    bool Wave2 = false;
    bool Wave3 = false;
    bool Wave4 = false;
    bool Wave5 = false;
    int WaveNum = 0;

    int Atk_po = 1;

    float LastSpawnX;
    float LastSpawnY;

    int randomSpawn;
    int monster_random_number;
    
    PlayerChar* player;
    PlayUI* plUI;
private:
    Landscape* landscape;
    vector<Plant_monster*> pl_mon;

    Slash_hit* fx;
    Slash_hit* fx2;
    Slash_hit* fx3;
    Slash_hit* fx4;
    Slash_hit* fx5;

    Shield* shield;

    Physics* py;

    bool isLoop = false;
};

