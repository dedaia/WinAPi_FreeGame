#pragma once
class SampleCharacter : public Rect
{
private:
    enum ActionType
    {
        IDLE, RUN, WALK, JUMP, JUMP_DOWN,
        HURT, DEAD,
        ATTACK_1, ATTACK_2, ATTACK_3,
        RUN_ATTACK
    };

    const float WALK_SPEED = 500.0f;
    const float RUN_MULT = 1.5f;

    const float JUMP_POWER = 750.0f;
    const float GRAVITY = 1500.0f;
    const float BOTTOM_CHECK = 10.0f;

    const float GHOST_TIME = 3.0f;
    const float ALPHA_SPEED = 1000.0f;

    const float ATTACK_DELAY = 0.1f;
    const float ATTACK_COMBO = 0.5f;

public:
    SampleCharacter();
    ~SampleCharacter();

    void Update();
    void Render(HDC hdc);

private:
    void Jump();
    void GetHit();
    void EndGetHit();
    void Die();

    void Attack();
    void Attack_Run();
    void Attack_GetCombo();
    void Attack_InputDelay();
    void EndAttack();

    bool OnGround();
    void WalkAndRun();

    void AutoAnimation();
    void SetAction(ActionType type);

    void CreateAnimations();

private:
    Texture* texture;

    ImageRect* imageRect;
    Vector2 imageOffset;

    map<ActionType, Animation*> animations;

    ActionType curAction = IDLE;

    bool isLeft = false;

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

