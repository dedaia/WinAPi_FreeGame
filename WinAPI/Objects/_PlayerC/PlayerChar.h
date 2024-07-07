#pragma once
class PlayerChar : public Rect
{
public:
    enum ActionType
    {
        IDLE, RUN, WALK, DEFENSE,
        HURT, DEAD,
        ATTACK_1, ATTACK_2, ATTACK_3, ATTACK_UPPER
    };

    // 공격력
    float ATTACK_DELAY = 1.5f;
    float ATTACK_COMBO = 0.5f;
    float ATK_power = 100.0f;
    // 체력
    float char_HP = 100;
    float Max_HP = 100;
    float hp_per;
    // 스피드
    float WALK_SPEED = 300.0f;
    float RUN_MULT = 5.5f;
    float chong_speed = 0.0f;
    // 경험치
    float Max_exp;
    float player_exp = 0;
    float exp_per = 0.0f;

    int LV = 1;
    bool vlvel_up = false;

    void Level_Up();

    float atk_second;

    bool atk_charge = false;

    float charge_per;
    int full_charge;
    int full_charge2;
    int full_charge3;

    int monster_atk;

    bool left_on = true;
    bool right_on = true;
    bool top_on = true;
    bool bottom_on = true;

    bool Plant_hurt_on = false;
public:
    

    PlayerChar();
    ~PlayerChar();

    void Update();
    void Render(HDC hdc);

    float Getspeed() { return WALK_SPEED; }

    bool IsRectCollision(Rect* rect)
    {
        if (!isActive) return false;
        if (!rect->isActive) return false;

        if (rect->Left() < Right() && rect->Right() > Left())
        {
            if (rect->Top() < Bottom() && rect->Bottom() > Top())
            {
                return true;
            }
        }

        return false;
    }

    Rect* hitsize;
    Rect* at_range;

    Rect* _Left;
    Rect* _Left_Top;
    Rect* _Top;
    Rect* _Right_Top;
    Rect* _Right;
    Rect* _Right_Bottom;
    Rect* _Bottom;
    Rect* _Left_Bottom;

    bool at_1 = false;
    bool at_2 = false;
    bool at_3 = false;
    bool at_up = false;

    void HitBox();

    bool isLeft = false;

    bool atk_on = false;

public:
    void GetHit();
    void EndGetHit();
    void Die();

    void Defence();
    void EndDefence();

    void Attack();
    void Attack_GetCombo();
    void Attack_InputDelay();
    void EndAttack();



    void Attack_Upper();

    void WalkAndRun();

    void SetAction(ActionType type);

    void CreateAnimations();
public:
    Texture* texture;

    ImageRect* imageRect;
    Vector2 imageOffset;

    map<ActionType, Animation*> animations;

    ActionType curAction = IDLE;    

    float yVelocity = 0.0f;

    int attackCount = 0;
    float attackInputDelay = 0;
    float attackComboCurrentTime = 0;
    // bool isAttacking = false;

    bool isGhost = false;
    float ghostTime = 0.0f;

    float alphaValue = 255;
    bool isIncreaseAlpha = false;

    bool isHighProfile = false;

    wstring attacks;
};

