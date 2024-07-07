#include "Framework.h"
#include "Plant_monster.h"

Plant_monster::Plant_monster(int mon_num)
{
    plant_texture = Texture::Add(L"Textures/_Monster/plant_mon.bmp", 6, 9);
    plant_imageRect = new ImageRect(plant_texture);

    worm_texture = Texture::Add(L"Textures/_Monster/test2_ver1.bmp", 6, 9);
    worm_imageRect = new ImageRect(worm_texture);

    Bloated_texture = Texture::Add(L"Textures/_Monster/Bloated.bmp", 6, 9);
    Bloated_imageRect = new ImageRect(Bloated_texture);

    BlueSlime_texture = Texture::Add(L"Textures/_Monster/Slime_Blue.bmp", 8, 7);
    BlueSlime_imageRect = new ImageRect(BlueSlime_texture);

    GreenSlime_texture = Texture::Add(L"Textures/_Monster/Slime_Green.bmp", 8, 7);
    GreenSlime_imageRect = new ImageRect(GreenSlime_texture);

    Dragon_texture = Texture::Add(L"Textures/_Monster/dragon.bmp", 5, 4);
    Dragon_imageRect = new ImageRect(Dragon_texture);

    BabyDragon_texture = Texture::Add(L"Textures/_Monster/baby_dragon.bmp", 4, 4);
    BabyDragon_imageRect = new ImageRect(BabyDragon_texture);

    size = { 96, 96 };
    imageOffset = { 0, 0 };

    monster_number = mon_num;

    //if (monster_number == 1)
    //{
    //    SetAction(PLANT_IDLE);
    //}
    //else if (monster_number == 2)
    //{
    //    SetAction(WORM_IDLE);
    //}

    HP = 100;

    if (monster_number == 1) // 식물 몬스터
    {
        sizeX = 65;
        sizeY = 50;
        posX = 256;
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 2) // 벌레 몬스터
    {
        sizeX = 50;
        sizeY = 38;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 3) // 풍선 몬스터
    {
        sizeX = 50;
        sizeY = 50;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 4) // 블루 슬라임
    {
        sizeX = 50;
        sizeY = 30;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 5) // 그린 슬라임
    {
        sizeX = 50;
        sizeY = 30;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 6) // 드래곤
    {
        sizeX = 147;
        sizeY = 70;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }
    else if (monster_number == 7) // 배이비 드래곤
    {
        sizeX = 80;
        sizeY = 50;
        posX = 256; 
        posY = 200 - sizeY / 2; 
    }

    hitsize = new Rect(Vector2(posX, posY), Vector2(sizeX, sizeY));

    CreateAnimations();
    animations[curAction]->Play();
}

Plant_monster::~Plant_monster()
{
    delete plant_imageRect;
    delete worm_imageRect;

    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;
}

void Plant_monster::Update()
{
    HitBox();
    GetHit();

    Attack();
    
    Die();
    WalkAndRun();

    if (monster_number == 1)
    {
        plant_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 2)
    {
        worm_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 3)
    {
        Bloated_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 4)
    {
        BlueSlime_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 5)
    {
        GreenSlime_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 6)
    {
        Dragon_imageRect->pos = pos + imageOffset;
    }
    else if (monster_number == 7)
    {
        BabyDragon_imageRect->pos = pos + imageOffset;
    }

    animations[curAction]->Update();
}

void Plant_monster::HitBox()
{
    if (monster_number == 1)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(Left() + hitsize->Getsize().x / 2, Bottom() - hitsize->Half().y);
        }
        else
        {
            hitsize->pos = Vector2(Right() - hitsize->Getsize().x / 2, Bottom() - hitsize->Half().y);
        }
    }
    else if (monster_number == 2)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(Left() + hitsize->Getsize().x / 2 + 10, Bottom() - hitsize->Half().y - 10);
        }
        else
        {
            hitsize->pos = Vector2(Right() - hitsize->Getsize().x / 2 - 10, Bottom() - hitsize->Half().y - 10);
        }
    }
    else if (monster_number == 3)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(Left() + hitsize->Getsize().x / 2 + 10, Bottom() - hitsize->Half().y - 10);
        }
        else
        {
            hitsize->pos = Vector2(Right() - hitsize->Getsize().x / 2 - 10, Bottom() - hitsize->Half().y - 10);
        }
    }
    else if (monster_number == 4)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 19);
        }
        else
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 19);
        }
    }
    else if (monster_number == 5)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 19);
        }
        else
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 19);
        }
    }
    else if (monster_number == 6)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 16);
        }
        else
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y + 16);
        }
    }
    else if (monster_number == 7)
    {
        if (!isLeft)
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y - 28);
        }
        else
        {
            hitsize->pos = Vector2(pos.x, Bottom() - hitsize->Half().y - 28);
        }
    }
    
}

void Plant_monster::Render(HDC hdc)
{
    // Rect::LineRender(hdc);

    // hitsize->Render(hdc);

     

    if (monster_number == 1)
    {
        plant_imageRect->Render(hdc, !isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y - 10, pos.x + 30, pos.y - 5);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y - 10, (pos.x - 30) + full_charge, pos.y - 5);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 2)
    {
        worm_imageRect->Render(hdc, !isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y - 10, pos.x + 30, pos.y - 5);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y - 10, (pos.x - 30) + full_charge, pos.y - 5);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 3)
    {
        Bloated_imageRect->Render(hdc, !isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y - 20, pos.x + 30, pos.y - 15);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y - 20, (pos.x - 30) + full_charge, pos.y - 15);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 4)
    {
        BlueSlime_imageRect->Render(hdc, !isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y +10, pos.x + 30, pos.y +15);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y +10, (pos.x - 30) + full_charge, pos.y + 15);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 5)
    {
        GreenSlime_imageRect->Render(hdc, !isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y + 10, pos.x + 30, pos.y + 15);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y + 10, (pos.x - 30) + full_charge, pos.y + 15);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 6)
    {
        Dragon_imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y - 15, pos.x + 30, pos.y -10);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y - 15, (pos.x - 30) + full_charge, pos.y -10);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
    else if (monster_number == 7)
    {
        BabyDragon_imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());

        {
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            HGDIOBJ oldBrush = SelectObject(hdc, brush);

            hp_per = HP / Max_HP;

            if (hp_per < 0)
            {
                hp_per = 0;
            }

            full_charge = 60 * hp_per;

            Rectangle(hdc, pos.x - 30, pos.y - 30, pos.x + 30, pos.y - 25);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);

            brush = CreateSolidBrush(RGB(255, 0, 0));
            oldBrush = SelectObject(hdc, brush);

            Rectangle(hdc, pos.x - 30, pos.y - 30, (pos.x - 30) + full_charge, pos.y - 25);

            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }
    }
}

void Plant_monster::Attack()
{
    if (!StageManager::Get()->IsPlay()) return;

    if (monster_number == 2)
    {

    }
}

void Plant_monster::WalkAndRun()
{
    if (!StageManager::Get()->IsPlay()) return;

    if (KEY_PRESS(VK_UP) && top_on)
    {
        pos.y += player_speed * DELTA;
    }
    if (KEY_PRESS(VK_DOWN) && bottom_on)
    {
        pos.y -= player_speed * DELTA;
    }
    if (KEY_PRESS(VK_LEFT) && left_on)
    {
        pos.x += player_speed * DELTA;
    }
    if (KEY_PRESS(VK_RIGHT) && right_on)
    {
        pos.x -= player_speed * DELTA;
    }

    

    if (CanMove)
    {
        //if (monster_number == 1 )
        {
            SetAction(PLANT_WALK);
        }
        //else if (monster_number == 2 )
        {
            SetAction(WORM_WALK);
        }
        //else if (monster_number == 3)
        {
            SetAction(BLOATED_WALK);
        }
        //else if (monster_number == 4)
        {
            SetAction(BLUESLIME_WALK);
        }
        //else if (monster_number == 5)
        {
            SetAction(GREENSLIME_WALK);
        }
        //else if (monster_number == 6)
        {
            SetAction(DRAGON_WALK);
        }
        //else if (monster_number == 7)
        {
            SetAction(BABYDRAGON_WALK);
        }
        
        if (CENTER_X < pos.x ) // 센터보다 크다는 것은 오른편에 있다는 것
        {
            isLeft = true;

            pos.x -= WALK_SPEED * RUN_MULT * DELTA;
        }
        else if (CENTER_X > pos.x ) // 센터보다 작다는 것은 왼편에 있다는 것
        {
            isLeft = false;

            pos.x += WALK_SPEED * RUN_MULT * DELTA;
        }
        if (CENTER_Y < pos.y ) // 센터보다 크다는 것은 아래쪽에 있다는 것
        {
            pos.y -= WALK_SPEED * RUN_MULT * DELTA;
        }
        else if (CENTER_Y > pos.y  ) // 센터보다 작다는 것은 위쪽에 있다는 것
        {
            pos.y += WALK_SPEED * RUN_MULT * DELTA;
        }
    }
}

void Plant_monster::GetHit()
{
    //if (monster_number == 1)
    
        if (gethurt)
        {
            SetAction(PLANT_HURT);
            SetAction(WORM_HURT);
            SetAction(BLOATED_HURT);
            SetAction(BLUESLIME_HURT);
            SetAction(GREENSLIME_HURT);
            SetAction(DRAGON_HURT);
            SetAction(BABYDRAGON_HURT);
        }
    
    //else if (monster_number == 2)
    {
        if (gethurt)
        {
            
        }
    }
    //else if (monster_number == 3)
    {
        if (gethurt)
        {
            
        }
    }
    //else if (monster_number == 4)
    {
        if (gethurt)
        {
        }
    }
    //else if (monster_number == 5)
    {
        if (gethurt)
        {
        }
    }
    //else if (monster_number == 6)
    {
        if (gethurt)
        {
        }
    }
    //else if (monster_number == 7)
    {
        if (gethurt)
        {
        }
    }
}

void Plant_monster::Die()
{
    if (monster_number == 1)
    {
        if (HP < 1)
        {
            SetAction(PLANT_DEAD);
        }
    }
    else if (monster_number == 2)
    {
        if (HP < 1)
        {
            SetAction(WORM_DEAD);
        }
    }
    else if (monster_number == 3)
    {
        if (HP < 1)
        {
            SetAction(BLOATED_DEAD);
        }
    }
    else if (monster_number == 4)
    {
        if (HP < 1)
        {
            SetAction(BLUESLIME_DEAD);
        }
    }
    else if (monster_number == 5)
    {
        if (HP < 1)
        {
            SetAction(GREENSLIME_DEAD);
        }
    }
    else if (monster_number == 6)
    {
        if (HP < 1)
        {
            SetAction(DRAGON_DEAD);
        }
    }
    else if (monster_number == 7)
    {
        if (HP < 1)
        {
            SetAction(BABYDRAGON_DEAD);
        }
    }

    
}

void Plant_monster::EndDie()
{
    if (HP < 1)
    {
        itActive = false;
        CanMove = false;
    }
    
}

void Plant_monster::EndGetHit()
{
    HP = HP - play_atk;

    if (monster_number == 1)
    {
        gethurt = false;
        SetAction(PLANT_IDLE);
    }
    else if (monster_number == 2)
    {
        gethurt = false;
        SetAction(WORM_IDLE);
    }    
    else if (monster_number == 3)
    {
        gethurt = false;
        SetAction(BLOATED_IDLE);
    }
    else if (monster_number == 4)
    {
        gethurt = false;
        SetAction(BLUESLIME_IDLE);
    }
    else if (monster_number == 5)
    {
        gethurt = false;
        SetAction(GREENSLIME_IDLE);
    }
    else if (monster_number == 6)
    {
        gethurt = false;
        SetAction(DRAGON_IDLE);
    }
    else if (monster_number == 7)
    {
        gethurt = false;
        SetAction(BABYDRAGON_IDLE);
    }
}

void Plant_monster::EndAttack()
{
    if (monster_number == 2)
    {
        SetAction(WORM_IDLE);
    }    
}

void Plant_monster::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void Plant_monster::CreateAnimations()
{
    // 식물 몬스터
    {
        animations[PLANT_IDLE] = new Animation(plant_texture->GetFrame());
        animations[PLANT_IDLE]->SetPart(48, 53, true);

        animations[PLANT_WALK] = new Animation(plant_texture->GetFrame());
        animations[PLANT_WALK]->SetPart(64, 71, true);

        animations[PLANT_HURT] = new Animation(plant_texture->GetFrame());
        animations[PLANT_HURT]->SetPart(30, 33);
        animations[PLANT_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[PLANT_DEAD] = new Animation(plant_texture->GetFrame());
        animations[PLANT_DEAD]->SetPart(24, 29);
        animations[PLANT_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }
    
    // 벌레 몬스터
    {
        animations[WORM_IDLE] = new Animation(worm_texture->GetFrame());
        animations[WORM_IDLE]->SetPart(36, 39, true);

        animations[WORM_WALK] = new Animation(worm_texture->GetFrame());
        animations[WORM_WALK]->SetPart(48, 51, true);

        animations[WORM_HURT] = new Animation(worm_texture->GetFrame());
        animations[WORM_HURT]->SetPart(30, 31);
        animations[WORM_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[WORM_DEAD] = new Animation(worm_texture->GetFrame());
        animations[WORM_DEAD]->SetPart(24, 25, true);
        animations[WORM_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));

        animations[WORM_ATTACK] = new Animation(worm_texture->GetFrame());
        animations[WORM_ATTACK]->SetPart(18, 21, true);
        animations[WORM_ATTACK]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }

    // 풍선 몬스터
    {
        animations[BLOATED_IDLE] = new Animation(Bloated_texture->GetFrame());
        animations[BLOATED_IDLE]->SetPart(36, 39);

        animations[BLOATED_WALK] = new Animation(Bloated_texture->GetFrame());
        animations[BLOATED_WALK]->SetPart(48, 53);

        animations[BLOATED_HURT] = new Animation(Bloated_texture->GetFrame());
        animations[BLOATED_HURT]->SetPart(42, 43);
        animations[BLOATED_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[BLOATED_DEAD] = new Animation(Bloated_texture->GetFrame());
        animations[BLOATED_DEAD]->SetPart(24, 27);
        animations[BLOATED_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }

    // 블루 슬라임
    {
        animations[BLUESLIME_IDLE] = new Animation(BlueSlime_texture->GetFrame());
        animations[BLUESLIME_IDLE]->SetPart(40, 47);

        animations[BLUESLIME_WALK] = new Animation(BlueSlime_texture->GetFrame());
        animations[BLUESLIME_WALK]->SetPart(48, 55);

        animations[BLUESLIME_HURT] = new Animation(BlueSlime_texture->GetFrame());
        animations[BLUESLIME_HURT]->SetPart(32, 37);
        animations[BLUESLIME_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[BLUESLIME_DEAD] = new Animation(BlueSlime_texture->GetFrame());
        animations[BLUESLIME_DEAD]->SetPart(24, 26);
        animations[BLUESLIME_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }

    // 그린 슬라임
    {
        animations[GREENSLIME_IDLE] = new Animation(GreenSlime_texture->GetFrame());
        animations[GREENSLIME_IDLE]->SetPart(40, 47);

        animations[GREENSLIME_WALK] = new Animation(GreenSlime_texture->GetFrame());
        animations[GREENSLIME_WALK]->SetPart(48, 55);

        animations[GREENSLIME_HURT] = new Animation(GreenSlime_texture->GetFrame());
        animations[GREENSLIME_HURT]->SetPart(32, 37);
        animations[GREENSLIME_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[GREENSLIME_DEAD] = new Animation(GreenSlime_texture->GetFrame());
        animations[GREENSLIME_DEAD]->SetPart(24, 26);
        animations[GREENSLIME_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }
 
    // 드래곤
    {
        animations[DRAGON_IDLE] = new Animation(Dragon_texture->GetFrame());
        animations[DRAGON_IDLE]->SetPart(10, 12);

        animations[DRAGON_WALK] = new Animation(Dragon_texture->GetFrame());
        animations[DRAGON_WALK]->SetPart(15, 19);

        animations[DRAGON_HURT] = new Animation(Dragon_texture->GetFrame());
        animations[DRAGON_HURT]->SetPart(6, 7);
        animations[DRAGON_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[DRAGON_DEAD] = new Animation(Dragon_texture->GetFrame());
        animations[DRAGON_DEAD]->SetPart(0, 5);
        animations[DRAGON_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }

    // 배이비 드래곤
    {
        animations[BABYDRAGON_IDLE] = new Animation(BabyDragon_texture->GetFrame());
        animations[BABYDRAGON_IDLE]->SetPart(8, 10);

        animations[BABYDRAGON_WALK] = new Animation(BabyDragon_texture->GetFrame());
        animations[BABYDRAGON_WALK]->SetPart(12, 15);

        animations[BABYDRAGON_HURT] = new Animation(BabyDragon_texture->GetFrame());
        animations[BABYDRAGON_HURT]->SetPart(4, 5);
        animations[BABYDRAGON_HURT]->SetEndEvent(bind(&Plant_monster::EndGetHit, this));

        animations[BABYDRAGON_DEAD] = new Animation(BabyDragon_texture->GetFrame());
        animations[BABYDRAGON_DEAD]->SetPart(0, 3);
        animations[BABYDRAGON_DEAD]->SetEndEvent(bind(&Plant_monster::EndDie, this));
    }
}

void Plant_monster::plantCollision(vector<Plant_monster*> pla)
{
    int movesp = 1;
    for (int i = 0; i < pla.size(); ++i)
    {
        if (this->hitsize->IsRectCollision(pla[i]->hitsize))
        {
            if (this != pla[i])
            {
                if (GetCollisionDirection(this->hitsize, pla[i]->hitsize) == LEFT)
                {
                    this->pos.x -= movesp;
                }
                else if (GetCollisionDirection(this->hitsize, pla[i]->hitsize) == RIGHT)
                {
                    this->pos.x += movesp;
                }
                else if (GetCollisionDirection(this->hitsize, pla[i]->hitsize) == ABOVE)
                {
                    this->pos.y -= movesp;
                }
                else if (GetCollisionDirection(this->hitsize, pla[i]->hitsize) == BENEATH)
                {
                    //this->pos.y += movesp;
                }
            }            
        }        
    }
}

bool Plant_monster::IsRectCollision(Rect* rect)
{
    if (this->isActive) return false;
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