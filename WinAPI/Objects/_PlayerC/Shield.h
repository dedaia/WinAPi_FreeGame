#pragma once
class Shield : public Rect
{
public:
    enum ActionType
    {
        shi1, shi2, shi3, shi4, shi5, shi6, shi7,
        shi8, shi9, shi10, shi11, shi12, shi13, shi14,
    };

    Shield();
    ~Shield();

    void Update();
    void Render(HDC hdc);
    void HitBox();

    float player_speed;

    void SetPos(Rect* source, int pos, int pos_wi);

    void SetAction(ActionType type);

    void CreateAnimations();

    float yVelocity = 0.0f;
    float alphaValue = 255;

    void Use(Rect* source);

    int shield_number;    
    int pos_aaaa;
    int pos_wi;

    float delta;
    float life_time = 3.0f;

    bool isLeft = false;
    bool life = false;
    
    Texture* texture;

    ImageRect* imageRect;
    Vector2 imageOffset;

    Rect* hitsize;

    map<ActionType, Animation*> animations;

    ActionType curAction = shi1;


    wstring attacks;

};