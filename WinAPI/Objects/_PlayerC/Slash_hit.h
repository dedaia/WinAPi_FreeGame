#pragma once
class Slash_hit : public Rect
{
public:
    enum ActionType
    {
        LEFT, RIGTH, TOP, BOTTOM, LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGTH_BOTTOM
    };

    Slash_hit(int vl);
    Slash_hit(Vector2 pos, Vector2 size) :Rect(pos, size) {}
    Slash_hit(float left, float top, float right, float bottom)
        : Rect(left, top, right, bottom) {}

    void Start(Rect* source, int position);
    void Render(HDC hdc);

    HBITMAP sla;;

    void Update();

    void SetPosition(Rect* source, int position);

    bool isLeft = false;
    bool isTop = false;

    int slash_lv;

    float currentTime = 0;
    float timeSpan = 0.3;

    void SetAction(ActionType type);

    void CreateAnimations();

    int spawn_pos = 60;
    int slah_LEVEL(int LEVEL);
private:

    Texture* texture;

    ImageRect* imageRect;
    Vector2 imageOffset;

    map<ActionType, Animation*> animations;

    ActionType curAction = LEFT;

    float yVelocity = 0.0f;
    UINT jumpCount = 0;

    UINT attackCount = 0;
    float attackInputDelay = 0;
    float attackComboCurrentTime = 0;
    bool isAttacking = false;

    bool isGhost = false;
    float ghostTime = 0.0f;

    float alphaValue = 255;
    bool isIncreaseAlpha = false;

    bool isHighProfile = false;

    wstring attacks;
};