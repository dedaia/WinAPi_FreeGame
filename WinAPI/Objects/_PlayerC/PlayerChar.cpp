#include "Framework.h"
#include "PlayerChar.h"

PlayerChar::PlayerChar()
{
    srand(GetTickCount64());

    texture = Texture::Add(L"Textures/_char/player_ver1.bmp", 8, 10);
    imageRect = new ImageRect(texture);
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    float sizeX = 50;
    float sizeY = 50;
    float posX = CENTER_X; // 256 : 위에 있는 캐릭터 (그림) 영역의 위치
    float posY = CENTER_Y + sizeY / 2; //512 : 캐릭터 (그림) 영역의 크기에서 캐릭터 (충돌) 영역의 크기를 뺀 것

    hitsize = new Rect(Vector2(posX, posY), Vector2(sizeX, sizeY));
    
    // at_range = new Rect(Vector2(posX, posY), Vector2(300, 300));

    _Left =         new Rect(Vector2(posX - 96, posY), Vector2(96, 96));
    _Left_Top =     new Rect(Vector2(posX - 96, posY - 96), Vector2(96, 96));
    _Top =          new Rect(Vector2(posX, posY - 96), Vector2(96, 96));
    _Right_Top =    new Rect(Vector2(posX + 96, posY - 96), Vector2(96, 96));
    _Right =        new Rect(Vector2(posX + 96, posY), Vector2(96, 96));
    _Right_Bottom = new Rect(Vector2(posX + 96, posY + 96), Vector2(96, 96));
    _Bottom =       new Rect(Vector2(posX, posY + 96), Vector2(96, 96));
    _Left_Bottom =  new Rect(Vector2(posX - 96, posY + 96), Vector2(96, 96));

    CreateAnimations();
    animations[curAction]->Play();
}

PlayerChar::~PlayerChar()
{
    delete imageRect;


    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;
}

void PlayerChar::Update()
{
    hitsize;

    GetHit();

    WalkAndRun();

    Attack();

    Defence();    

    // Attack_GetCombo();
    // Attack_InputDelay();

    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();
}

void PlayerChar::Render(HDC hdc)
{
    // Rect::LineRender(hdc);

    charge_per = atk_second / ATTACK_DELAY;
    full_charge = 60 * charge_per;

    hp_per = char_HP / Max_HP;
    full_charge2 = 60 * hp_per;

    exp_per = player_exp / Max_exp;
    full_charge3 = 1280 * exp_per;

    // 체력과 어택차지 바
    {
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
        HGDIOBJ oldBrush = SelectObject(hdc, brush);

        Rectangle(hdc, CENTER_X - 30, CENTER_Y - 20, CENTER_X + 30, CENTER_Y - 15);

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(255, 0, 0));
        oldBrush = SelectObject(hdc, brush);

        // 체력바
        Rectangle(hdc, CENTER_X - 30, CENTER_Y - 20, (CENTER_X - 30) + full_charge2, CENTER_Y - 15);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);



        pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
        oldPen = SelectObject(hdc, pen);
        brush = CreateSolidBrush(RGB(0, 0, 0));
        oldBrush = SelectObject(hdc, brush);

        Rectangle(hdc, CENTER_X - 30, CENTER_Y - 10, CENTER_X + 30, CENTER_Y - 5);

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(255, 0, 255));
        oldBrush = SelectObject(hdc, brush);
        // 공격 준비
        Rectangle(hdc, CENTER_X - 30, CENTER_Y - 10, (CENTER_X - 30) + full_charge, CENTER_Y - 5);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        

        
    }

    


    //hitsize->Render(hdc);
    // at_range->Render(hdc);

    // _Left->Render(hdc);
    // _Left_Top->Render(hdc);
    // _Top->Render(hdc);
    // _Right_Top->Render(hdc);
    // _Right->Render(hdc);
    // _Right_Bottom->Render(hdc);
    // _Bottom->Render(hdc);
    // _Left_Bottom->Render(hdc);

    imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());
}

void PlayerChar::Defence()
{
    if (KEY_DOWN(VK_NUMPAD1))
    {
        if (curAction != WALK &&
            curAction != RUN &&
            curAction != HURT &&
            curAction != ATTACK_1 &&
            curAction != ATTACK_2 &&
            curAction != ATTACK_3 &&
            curAction != ATTACK_UPPER)
        SetAction(DEFENSE);
    }    
}

void PlayerChar::EndDefence()
{
    SetAction(IDLE);
}

void PlayerChar::Attack()
{
    if (!StageManager::Get()->IsPlay()) return;

    if (curAction == RUN) return;



    if (!atk_charge)
    {
        atk_second += DELTA;
    }

    if (ATTACK_DELAY <= atk_second)
    {
        atk_charge = true;

        if (atk_charge)
        {
            atk_second = ATTACK_DELAY;
        }
    }

    if (atk_on && atk_charge)
    {
        // attackCount = rand() % 100;
        attackCount = 20;

        if (attackCount >= 0 && attackCount <= 39)
        {
            at_1 = true;
            atk_charge = false;
            atk_second = 0.0f;
            SetAction(ATTACK_1);
        }
        else if (attackCount >= 40 && attackCount <= 79)
        {
            at_2 = true;
            atk_charge = false;
            atk_second = 0.0f;
            SetAction(ATTACK_2);
        }
        else if (attackCount >= 80 && attackCount <= 99)
        {
            at_3 = true;
            atk_charge = false;
            atk_second = 0.0f;
            SetAction(ATTACK_3);
        }
    }
}

void PlayerChar::Attack_GetCombo()
{
    if (attackComboCurrentTime < 0)
    {
        attackComboCurrentTime = 0;
        attackCount = 0;
    }

    if (attackComboCurrentTime == 0) return;
    else attackComboCurrentTime -= DELTA;
}

void PlayerChar::Attack_InputDelay()
{
    if (attackInputDelay < 0)
    {
        attackInputDelay = 0;
    }

    if (attackInputDelay == 0) return;
    else attackInputDelay -= DELTA;
}

void PlayerChar::WalkAndRun()
{
    if (!StageManager::Get()->IsPlay()) return;

    chong_speed = WALK_SPEED;

    if (KEY_DOWN(VK_SHIFT))
    {
        if (!isHighProfile) isHighProfile = true;
        
    }
    if (KEY_UP(VK_SHIFT))
    {
        if (isHighProfile) isHighProfile = false;
        
    }

    if (KEY_DOWN(VK_LEFT))
    {
        at_1 = false;
        at_2 = false;
        at_3 = false;
        at_up = false;
    }
    if (KEY_PRESS(VK_LEFT) && left_on)
    {
        if (!isLeft) isLeft = true;
        if (isHighProfile)
        {
            chong_speed = WALK_SPEED * RUN_MULT;
            if (curAction != RUN && curAction != HURT) SetAction(RUN);
            StageManager::Get()->Move(chong_speed  * DELTA * -1, 0);
            at_1 = false;
            at_2 = false;
            at_3 = false;
            at_up = false;
        }
        else
        {
            chong_speed = WALK_SPEED;
            if (curAction != WALK && curAction != HURT) SetAction(WALK);
            StageManager::Get()->Move(chong_speed * DELTA * -1, 0);
            at_1 = false;
            at_2 = false;
            at_3 = false;
            at_up = false;
        }
    }
    if (KEY_UP(VK_LEFT))
    {
        SetAction(IDLE);
    }

    if (KEY_DOWN(VK_RIGHT))
    {
        at_1 = false;
        at_2 = false;
        at_3 = false;
        at_up = false;
    }
    if (KEY_PRESS(VK_RIGHT) && right_on)
    {
        if (isLeft) isLeft = false;

        if (isHighProfile)
        {
            chong_speed = WALK_SPEED * RUN_MULT;
            if ( curAction != RUN && curAction != HURT) SetAction(RUN);
            StageManager::Get()->Move(chong_speed * DELTA, 0);
        }
        else
        {
            chong_speed = WALK_SPEED;
            if ( curAction != WALK && curAction != HURT) SetAction(WALK);
            StageManager::Get()->Move(chong_speed * DELTA, 0);
        }
    }
    if (KEY_UP(VK_RIGHT))
    {
        SetAction(IDLE);
    }

    if (KEY_DOWN(VK_UP))
    {
        at_1 = false;
        at_2 = false;
        at_3 = false;
        at_up = false;
    }
    if (KEY_PRESS(VK_UP) && top_on)
    {

        if (isHighProfile)
        {
            chong_speed = WALK_SPEED * RUN_MULT;
            if (curAction != RUN && curAction != HURT) SetAction(RUN);
            StageManager::Get()->Move(0, chong_speed * DELTA);
        }
        else
        {
            chong_speed = WALK_SPEED;
            if (curAction != WALK && curAction != HURT) SetAction(WALK);
            StageManager::Get()->Move(0, chong_speed * DELTA);
        }
    }
    if (KEY_UP(VK_UP))
    {
        SetAction(IDLE);
    }

    if (KEY_DOWN(VK_DOWN))
    {
        at_1 = false;
        at_2 = false;
        at_3 = false;
        at_up = false;
    }
    if (KEY_PRESS(VK_DOWN) && bottom_on)
    {

        if (isHighProfile)
        {
            chong_speed = WALK_SPEED * RUN_MULT;
            if (curAction != RUN && curAction != HURT) SetAction(RUN);
            StageManager::Get()->Move(0, chong_speed * DELTA * -1);
        }
        else
        {
            chong_speed = WALK_SPEED;
            if (curAction != WALK && curAction != HURT) SetAction(WALK);
            StageManager::Get()->Move(0, chong_speed* DELTA * -1);
        }
    }
    if (KEY_UP(VK_DOWN))
    {
        SetAction(IDLE);
    }
}

void PlayerChar::GetHit()
{
    if (Plant_hurt_on)
    {
        at_1 = false;
        at_2 = false;
        at_3 = false;
        at_up = false;
        SetAction(HURT);
    }

    if (char_HP <= 0)
    {
        Die();
    }
}

void PlayerChar::Die()
{
    SetAction(DEAD);

    StageManager::Get()->Stop();
}

void PlayerChar::EndGetHit()
{
    char_HP -= monster_atk;
    Plant_hurt_on = false;
    SetAction(IDLE);
}

void PlayerChar::EndAttack()
{
    at_1 = false;
    at_2 = false;
    at_3 = false;
    at_up = false;

    SetAction(IDLE);
    //attackComboCurrentTime = ATTACK_COMBO;
}

void PlayerChar::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void PlayerChar::Attack_Upper()
{
    at_3 = false;
    at_up = true;

    SetAction(ATTACK_UPPER);
}

void PlayerChar::Level_Up()
{
    Max_exp = (LV * 1.5) * 100;

    if (player_exp >= Max_exp)
    {
        player_exp -= Max_exp;
        LV++;

        vlvel_up = true;
    }
}

void PlayerChar::CreateAnimations()
{
    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(32, 36, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(48, 53, true);

    animations[WALK] = new Animation(texture->GetFrame());
    animations[WALK]->SetPart(64, 71, true);

    animations[HURT] = new Animation(texture->GetFrame());
    animations[HURT]->SetPart(24, 26);
    animations[HURT]->SetEndEvent(bind(&PlayerChar::EndGetHit, this));

    animations[DEAD] = new Animation(texture->GetFrame());
    animations[DEAD]->SetPart(16, 19);

    animations[DEFENSE] = new Animation(texture->GetFrame());
    animations[DEFENSE]->SetPart(40, 41);
    animations[DEFENSE]->SetEndEvent(bind(&PlayerChar::EndDefence, this));

    animations[ATTACK_1] = new Animation(texture->GetFrame());
    animations[ATTACK_1]->SetPart(0, 3);
    animations[ATTACK_1]->SetEndEvent(bind(&PlayerChar::EndAttack, this));

    animations[ATTACK_2] = new Animation(texture->GetFrame());
    animations[ATTACK_2]->SetPart(8, 11);
    animations[ATTACK_2]->SetEndEvent(bind(&PlayerChar::EndAttack, this));

    animations[ATTACK_3] = new Animation(texture->GetFrame());
    animations[ATTACK_3]->SetPart(0, 3);
    animations[ATTACK_3]->SetEndEvent(bind(&PlayerChar::Attack_Upper, this));

    animations[ATTACK_UPPER] = new Animation(texture->GetFrame());
    animations[ATTACK_UPPER]->SetPart(10, 11);
    animations[ATTACK_UPPER]->SetEndEvent(bind(&PlayerChar::EndAttack, this));
}