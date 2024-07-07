#pragma once
class Plant_monster : public Rect
{
public:
    enum ActionType
    {
        PLANT_IDLE, PLANT_WALK, PLANT_HURT, PLANT_DEAD,
        WORM_IDLE, WORM_WALK, WORM_HURT, WORM_DEAD, WORM_ATTACK,
        BLOATED_IDLE, BLOATED_WALK, BLOATED_HURT, BLOATED_DEAD,
        BLUESLIME_IDLE, BLUESLIME_WALK, BLUESLIME_HURT, BLUESLIME_DEAD,
        GREENSLIME_IDLE, GREENSLIME_WALK, GREENSLIME_HURT, GREENSLIME_DEAD,
        DRAGON_IDLE, DRAGON_WALK, DRAGON_HURT, DRAGON_DEAD,
        BABYDRAGON_IDLE, BABYDRAGON_WALK, BABYDRAGON_HURT, BABYDRAGON_DEAD
    };

    int monster_number;

    /*
    if (monster_number == 1)
    {

    }
    else if (monster_number == 2)
    {

    }
    */


    void plantCollision(vector<Plant_monster*> pla);

    float WALK_SPEED = 100.0f;
    float RUN_MULT = 1.5f;

    float JUMP_POWER = 750.0f;
    float GRAVITY = 1500.0f;
    float BOTTOM_CHECK = 10.0f;

    float GHOST_TIME = 3.0f;
    float ALPHA_SPEED = 1000.0f;

    float ATTACK_DELAY = 0.1f;
    float ATTACK_COMBO = 1.5f;

    float HP;
    float Max_HP = 100.0f;
    float hp_per;

    int monster_atk = 15;

    bool CanMove = true;

    bool itActive = true;

    bool left_on = true;
    bool right_on = true;
    bool top_on = true;
    bool bottom_on = true;

    bool CanMove_left = true;
    bool CanMove_right = true;
    bool CanMove_top = true;
    bool CanMove_bottom = true;

    float player_speed;

    void SetAction(ActionType type);

    float sizeX;
    float sizeY;
    float posX;
    float posY;
public:
    int play_atk = 0;
    int full_charge;

    Plant_monster(int mon_num);
    ~Plant_monster();

    void Update();
    void Render(HDC hdc);

    void HitBox();

    Rect* hitsize;

    bool gethurt = false;



private:
    void GetHit();
    void EndGetHit();
    void Die();

    void Attack();
    void EndAttack();
    void EndDie();

    

    void WalkAndRun();


    void CreateAnimations();

public:
    Texture* plant_texture;
    ImageRect* plant_imageRect;

    Texture* worm_texture;
    ImageRect* worm_imageRect;

    Texture* Bloated_texture;
    ImageRect* Bloated_imageRect;

    Texture* BlueSlime_texture;
    ImageRect* BlueSlime_imageRect;

    Texture* GreenSlime_texture;
    ImageRect* GreenSlime_imageRect;

    Texture* Dragon_texture;
    ImageRect* Dragon_imageRect;

    Texture* BabyDragon_texture;
    ImageRect* BabyDragon_imageRect;
    
    Vector2 imageOffset;

    map<ActionType, Animation*> animations;

    ActionType curAction = PLANT_IDLE;

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

    enum COL_DIRECTION // <-���� ���� �ǹ̸� �������� �Ἥ ���߿� �˾ƺ��� ���� ���� ��
    {
        NONE,
        LEFT,
        RIGHT,
        ABOVE,
        BENEATH,
    };

    //���� �ִ� �������� �Ἥ �浹 ������ �� �� �ִ� ������ ������
    COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
    {
        //�浹�� �� �簢���� ��ġ�� ������ �ľ��ؼ�,
        // �̵��� �浹 ���°� ������ ����, ���� ������ ������ �Ѵ�

        float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
        float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
        float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
        float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

        //�� ������ ����, �� �簢���� ��ġ�� ���� �� �ִ��� ���� ���� = �������� ���� �� �ִ�

        //�׸��� �������� ����� �Ǻ��ؼ�

        bool collideHorizontal;
        if (_right - _left > _bottom - _top) //���� (����) �簢���� ���ΰ� ���κ��� ũ��
        {
            collideHorizontal = false; // �������� �浹�ߴ� (���Ʒ� ��ġ = �׷��� �������� �����ϴ�)
        }
        else collideHorizontal = true; //���� �浹 (���� ������ ��ġ)

        if (collideHorizontal) //���� �浹�̴�
        {
            //���� ���� ���г��� ���ؼ� �� ���ʿ� �ִ� ���� ����
            if (rect_one->Left() < rect_two->Left())
            {
                return LEFT; //rect_one�� rect_two�� �����̴�
            }
            else
            {
                return RIGHT;
            }
        }
        else if (!collideHorizontal)
        {
            if (rect_one->Bottom() < rect_two->Bottom())
            {
                //�浹 ���� ũ�Ⱑ Ŀ�� �ʹ� ũ��! -> �̰� �׳� �����!

                return ABOVE; //��
            }
            else
            {
                return BENEATH; //�Ʒ�
            }
        }
    }

    //�� ����� �ޱ� ���� ���� �߰� (�ɼ�)
    COL_DIRECTION singleDir; //�� ���� ĳ���Ͱ�, �ϳ��� ���ǿ� ���� ������ ���Ⱚ

    bool IsRectCollision(Rect* rect);
};

