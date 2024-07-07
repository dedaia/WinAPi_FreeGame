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

    enum COL_DIRECTION // <-위와 같은 의미를 열거형을 써서 나중에 알아보기 쉽게 만든 것
    {
        NONE,
        LEFT,
        RIGHT,
        ABOVE,
        BENEATH,
    };

    //위에 있는 열거형을 써서 충돌 방향을 알 수 있는 연산을 만들자
    COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
    {
        //충돌한 두 사각형의 겹치는 영역을 파악해서,
        // 이들의 충돌 형태가 수직에 가까운가, 수평에 가까운가를 보고자 한다

        float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
        float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
        float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
        float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

        //위 연산을 통해, 두 사각형의 겹치는 영역 중 최대한 작은 영역 = 교집합을 구할 수 있다

        //그리고 교집합의 모양을 판별해서

        bool collideHorizontal;
        if (_right - _left > _bottom - _top) //작은 (가상) 사각형의 가로가 세로보다 크면
        {
            collideHorizontal = false; // 수직으로 충돌했다 (위아래 위치 = 그래서 교집합이 납작하다)
        }
        else collideHorizontal = true; //수평 충돌 (왼쪽 오른쪽 위치)

        if (collideHorizontal) //수평 충돌이다
        {
            //서로 왼쪽 선분끼리 비교해서 더 왼쪽에 있는 쪽이 왼쪽
            if (rect_one->Left() < rect_two->Left())
            {
                return LEFT; //rect_one은 rect_two의 왼쪽이다
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
                //충돌 영역 크기가 커도 너무 크다! -> 이건 그냥 통과다!

                return ABOVE; //위
            }
            else
            {
                return BENEATH; //아래
            }
        }
    }

    //위 결과를 받기 위한 변수 추가 (옵션)
    COL_DIRECTION singleDir; //한 명의 캐릭터가, 하나의 물건에 대해 가지는 방향값

    bool IsRectCollision(Rect* rect);
};

