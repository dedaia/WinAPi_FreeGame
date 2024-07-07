#include "Framework.h"
#include "SampleScene.h"

SampleScene::SampleScene()
{
    srand(GetTickCount64());

    StageManager::Get()->LoadTileData("TextData/_SampleScene/TileTable.csv");
    StageManager::Get()->SetAuto(isLoop);

    landscape = new Landscape(L"Textures/_SampleScene/sampleBackground.bmp", isLoop);
    player = new PlayerChar();
    player->pos = { CENTER_X, CENTER_Y};

    plUI = new PlayUI();

    pl_mon.push_back(new Plant_monster(1));
    pl_mon[pl_mon.size() - 1]->pos = { WIN_WIDTH , 100 };

    pl_mon.push_back(new Plant_monster(7));
    pl_mon[pl_mon.size() - 1]->pos = { WIN_WIDTH , 100 };
     
    shield = new Shield();

    fx = new Slash_hit(60);
    fx2 = new Slash_hit(120);
    fx3 = new Slash_hit(180);
    fx4 = new Slash_hit(240);
    fx5 = new Slash_hit(300);
}

SampleScene::~SampleScene()
{
    StageManager::Delete();

    delete landscape;
    delete player;
}

float SampleScene::Random_X()
{
    int ran;
    

    float lastX = LastSpawnX;

    while (true)
    {
        ran = rand() % 3;

        switch (ran)
        {
        case 0:
            X = -100;
            break;
        case 1:
            X = WIN_WIDTH + 100;
            break;
        case 2:
            X = CENTER_X;
            break;
        }

        if (lastX != X)
        {
            return X;
        }
    }
}

float SampleScene::Random_Y()
{
    int ran;
    

    float lastY = LastSpawnY;

    while (true)
    {
        ran = rand() % 3;

        switch (ran)
        {
        case 0:
            Y = -100;
            break;
        case 1:
            Y = WIN_HEIGHT + 100;
            break;
        case 2:
            if (X != CENTER_X)
            {
                Y = CENTER_Y;
            }
            else
            {
                Y = WIN_HEIGHT + 100;
            }
            break;
        }

        if (lastY != Y)
        {
            return Y;
        }
    }
}

void SampleScene::play_monster(vector<Plant_monster*> mon)
{
    int move = 6;

    for (int i = 0; i < mon.size(); ++i)
    {
        if (player->hitsize->IsRectCollision(mon[i]->hitsize))
        //if(py->GetCollisionDirection(player, pl_mon[i]->hitsize))
        {
            mon[i]->CanMove = false;

            if (py->GetCollisionDirection(player->hitsize, mon[i]->hitsize) == py->LEFT)
            {
                player->right_on = false;
                mon[i]->right_on = false;
                mon[i]->pos.x += move;
                player->Plant_hurt_on = true;

                player->monster_atk = pl_mon[i]->monster_atk;
            }
            if (py->GetCollisionDirection(player->hitsize, mon[i]->hitsize) == py->RIGHT)
            {
                player->left_on = false;
                mon[i]->left_on = false;
                mon[i]->pos.x -= move;
                player->Plant_hurt_on = true;

                player->monster_atk = pl_mon[i]->monster_atk;
            }
            if (py->GetCollisionDirection(player->hitsize, mon[i]->hitsize) == py->ABOVE)
            {
                player->bottom_on = false;
                mon[i]->bottom_on = false;
                mon[i]->pos.y += move;
                player->Plant_hurt_on = true;

                player->monster_atk = pl_mon[i]->monster_atk;
            }
            if (py->GetCollisionDirection(player->hitsize, mon[i]->hitsize) == py->BENEATH)
            {
                player->top_on = false;
                mon[i]->top_on = false;
                mon[i]->pos.y -= move;
                player->Plant_hurt_on = true;

                player->monster_atk = pl_mon[i]->monster_atk;
            }
        }
        else
        {
            mon[i]->left_on = true;
            mon[i]->right_on = true;
            mon[i]->top_on = true;
            mon[i]->bottom_on = true;

            player->left_on = true;
            player->right_on = true;
            player->top_on = true;
            player->bottom_on = true;

            mon[i]->CanMove = true;
        }
    }

    Atk_position(mon);
}

void SampleScene::MonsterSpawn()
{
    if (minute <= 2)
    {
        Wave1 = true;
        WaveNum = 1;
    }
    else if (minute >= 2 && minute <= 3)
    {
        Wave1 = false;
        Wave2 = true;
        WaveNum = 2;
    }
    else if (minute >= 3 && minute <= 4)
    {
        Wave2 = false;
        Wave3 = true;
        WaveNum = 3;
    }
    else if (minute >= 4 && minute <= 5)
    {
        Wave3 = false;
        Wave4 = true;
        WaveNum = 4;
    }
    else if (minute > 5)
    {
        Wave4 = false;
        Wave5 = true;
        WaveNum = 5;
    }

    spawn_count += DELTA;

    if (spawn_count >= 3 || KEY_DOWN(VK_INSERT))
    {
        spawn_count -= 3;
        
        int mon_sss = 3;

        if (Wave1) // 4
        {
            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 640 , -100 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 640 , 820 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 1380 , 360 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { -100 , 360 };
        }
        if (Wave2) // 8
        {
            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 320 , -100 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 320 , 820 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 640 , -100 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 640 , 820 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { -100 , 180 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 1380 , 180 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { -100 , 360 };

            randomSpawn = rand() % mon_sss + 1;
            pl_mon.push_back(new Plant_monster(randomSpawn));
            pl_mon[pl_mon.size() - 1]->pos = { 1380 , 360 };
        }
        if (Wave3)
        {

        }
        if (Wave4)
        {

        }
        if (Wave5)
        {

        }      
    }

     
}
                                        
void SampleScene::Monster_Dead()
{
    std::vector<int> Mon;

    
    {
        for (int i = 0; i < pl_mon.size(); ++i)
        {
            if (!pl_mon[i]->isActive)
            {
                Mon.push_back(i);
            }
        }

        for (int i = Mon.size() - 1; i >= 0; --i)
        {
            int indexToRemove = Mon[i];
            pl_mon.erase(pl_mon.begin() + indexToRemove);

            player->player_exp += 20;

            player->Level_Up();
        }
    }
}

void SampleScene::Update()
{
    landscape->SetSpeed(StageManager::Get()->GetSpeed() * 0.5f);

    StageManager::Get()->Update();
    StageManager::Get()->CollisionPickup(player);

    shield_eft();
    landscape->Update();
    player->Update();
    Monster_Dead();
    shield->player_speed = player->chong_speed;
    play_monster(pl_mon);
    shield->Update();

    // 유저 값 받아오기
    {
        plUI->atk = player->ATK_power;
        plUI->hp = player->char_HP;
        plUI->speed = player->WALK_SPEED;
    }

    plUI->Update();

    {
        player->ATK_power = plUI->atk;
        player->char_HP = plUI->hp;
        player->WALK_SPEED = plUI->speed;
    }

    // 몬스터들끼리 충돌하는지 확인
    for (int i = 0; i < pl_mon.size(); ++i)
    {
        pl_mon[i]->plantCollision(pl_mon);
    }    

    fx->Update();
    fx2->Update();
    fx3->Update();
    fx4->Update();
    fx5->Update();
    MonsterSpawn();
    
    // 어택 이미지 출력 참 거짓 여부
    if (player->at_1 && player->atk_on )
    {
        if (Atk_po == 1 || Atk_po == 2 || Atk_po == 8)
        {
            player->isLeft = true;
        }
        else if (Atk_po == 4 || Atk_po == 5 || Atk_po == 6)
        {
            player->isLeft = false;
        }
        fx->Start(player, Atk_po);
        fx2->Start(player, Atk_po);
        fx3->Start(player, Atk_po);
        fx4->Start(player, Atk_po);
        fx5->Start(player, Atk_po);
    }
    else if (player->at_2 && player->atk_on )
    {
        if (Atk_po == 1 || Atk_po == 2 || Atk_po == 8)
        {
            player->isLeft = true;
        }
        else if (Atk_po == 4 || Atk_po == 5 || Atk_po == 6)
        {
            player->isLeft = false;
        }
        fx->Start(player, Atk_po);
        fx2->Start(player, Atk_po);
        fx3->Start(player, Atk_po);
        fx4->Start(player, Atk_po);
        fx5->Start(player, Atk_po);
    }
    else if (player->at_3 && player->atk_on )
    {
        if (Atk_po == 1 || Atk_po == 2 || Atk_po == 8)
        {
            player->isLeft = true;
        }
        else if (Atk_po == 4 || Atk_po == 5 || Atk_po == 6)
        {
            player->isLeft = false;
        }
        fx->Start(player, Atk_po);
        fx2->Start(player, Atk_po);
        fx3->Start(player, Atk_po);
        fx4->Start(player, Atk_po);
        fx5->Start(player, Atk_po);
    }
    else if (player->at_up && player->atk_on)
    {
        if (Atk_po == 1 || Atk_po == 2 || Atk_po == 8)
        {
            player->isLeft = true;
        }
        else if (Atk_po == 4 || Atk_po == 5 || Atk_po == 6)
        {
            player->isLeft = false;
        }
        fx->Start(player, Atk_po);
        fx2->Start(player, Atk_po);
        fx3->Start(player, Atk_po);
        fx4->Start(player, Atk_po);
        fx5->Start(player, Atk_po);
    }
    else
    {
        fx->isActive = false;
    }
    
    // 몬스터가 살아 있는지 체크
    for (int i = 0; i < pl_mon.size(); ++i)
    {
        if (pl_mon[i]->HP < 1)
        {
            pl_mon[i]->isActive = false;
        }
    }

    // 스피드 및 몬스터 업데이트
    for (int i = 0; i < pl_mon.size(); ++i)
    {
        if (pl_mon[i]->isActive)
        {
            pl_mon[i]->player_speed = player->chong_speed;


            pl_mon[i]->Update();
        }        
    }

    

    if (plUI->shield_LV != 0)
    {
        shield->delta += DELTA;

        if (plUI->shield_LV == 1)
        {
            shield->life_time = 10;
        }
        if (plUI->shield_LV == 2)
        {
            shield->life_time = 8;
        }
        if (plUI->shield_LV == 3)
        {
            shield->life_time = 6;
        }
        if (plUI->shield_LV == 4)
        {
            shield->life_time = 1;
        }

        if (shield->delta >= shield->life_time)
        {
            shield->delta -= shield->life_time;

            shield->Use(player->hitsize);
        }
    }

    

    // 시간
    if (StageManager::Get()->IsPlay())
    {
        second += DELTA;
        atk_del += DELTA;
        second2 = second;

        if (second2 >= 60)
        {
            second -= 60;
            minute++;
        }
    }

    

    if (KEY_DOWN(VK_NUMPAD0))
    {
        minute++;
    }

    pl_mon[0]->pos.x = 20000;
    pl_mon[0]->pos.y = 20000;
}

void SampleScene::Render(HDC hdc)
{
    landscape->Render(hdc);

    StageManager::Get()->Render(hdc);
    
    player->Render(hdc);

   

    
    
    if (shield->life)
    {
        delat += DELTA;

        if (delat >= 3)
        {
            shield->life = false;
        }

        shield->Render(hdc);
    }

    for (int i = 0; i < pl_mon.size(); ++i)
    {
        pl_mon[i]->Render(hdc);
    }

    wstring str = to_wstring(minute) + L":" + to_wstring(second2);
    TextOut(hdc, (int)CENTER_X, 0, str.c_str(), (int)str.length());

    wstring wa = L"레벨 : " + to_wstring(player->LV);
    TextOut(hdc, (int)CENTER_X, 20, wa.c_str(), (int)wa.length());

    wstring rua1 = L"몬스터의 수 : " + to_wstring(pl_mon.size());
    TextOut(hdc, (int)CENTER_X, 40, rua1.c_str(), (int)rua1.length());

    if (fx->isActive)
    {
        if (plUI->slah_LV == 1)
        {
            fx->Render(hdc);
        }
        if (plUI->slah_LV == 2)
        {
            fx->Render(hdc);
            fx2->Render(hdc);
        }
        if (plUI->slah_LV == 3)
        {
            fx->Render(hdc);
            fx2->Render(hdc);
            fx3->Render(hdc);
        }
        if (plUI->slah_LV == 4)
        {
            fx->Render(hdc);
            fx2->Render(hdc);
            fx3->Render(hdc);
            fx4->Render(hdc);
        }
        if (plUI->slah_LV == 5)
        {
            fx->Render(hdc);
            fx2->Render(hdc);
            fx3->Render(hdc);
            fx4->Render(hdc);
            fx5->Render(hdc);
        }
    }

    {
        HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
        HGDIOBJ oldBrush = SelectObject(hdc, brush);

        Rectangle(hdc, -5, 677, 1285, 717);

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(0, 255, 0));
        oldBrush = SelectObject(hdc, brush);

        // 경험치바
        Rectangle(hdc, 0, 680, (0) + player->full_charge3, 714);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }    



    

    plUI->Render(hdc);
}

void SampleScene::Atk_position(vector<Plant_monster*> mon)
{
    player->atk_on = false;

    for (int i = 0; i < mon.size(); ++i)
    {
        if (player->_Left->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 1;
            player->atk_on = true;
        }
        if (player->_Left_Top->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 2;
            player->atk_on = true;
        }
        if (player->_Top->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 3;
            player->atk_on = true;
        }
        if (player->_Right_Top->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 4;
            player->atk_on = true;
        }
        if (player->_Right->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 5;
            player->atk_on = true;
        }
        if (player->_Right_Bottom->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 6;
            player->atk_on = true;
        }
        if (player->_Bottom->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 7;
            player->atk_on = true;
        }
        if (player->_Left_Bottom->IsRectCollision(mon[i]->hitsize))
        {
            Atk_po = 8;
            player->atk_on = true;
        }

        if (fx->IsRectCollision(mon[i]))
        {
            mon[i]->gethurt = true;
            ala++;

            //if (atk_del >= 0.1)
            {
                atk_del = 0;
                mon[i]->HP -= player->ATK_power;
            }

            mon[i]->play_atk = player->ATK_power;
        }
        if (fx2->IsRectCollision(mon[i]))
        {
            mon[i]->gethurt = true;
            ala++;

            //if (atk_del >= 0.1)
            {
                atk_del = 0;
                mon[i]->HP -= player->ATK_power;
            }

            mon[i]->play_atk = player->ATK_power;
        }
        if (fx3->IsRectCollision(mon[i]))
        {
            mon[i]->gethurt = true;
            ala++;

            //if (atk_del >= 0.1)
            {
                atk_del = 0;
                mon[i]->HP -= player->ATK_power;
            }

            mon[i]->play_atk = player->ATK_power;
        }
        if (fx4->IsRectCollision(mon[i]))
        {
            mon[i]->gethurt = true;
            ala++;

            //if (atk_del >= 0.1)
            {
                atk_del = 0;
                mon[i]->HP -= player->ATK_power;
            }

            mon[i]->play_atk = player->ATK_power;
        }
        if (fx5->IsRectCollision(mon[i]))
        {
            mon[i]->gethurt = true;
            ala++;

            //if (atk_del >= 0.1)
            {
                atk_del = 0;
                mon[i]->HP -= player->ATK_power;
            }

            mon[i]->play_atk = player->ATK_power;
        }
    }
}

void SampleScene::shield_eft()
{
    for (int i = 0; i < pl_mon.size(); ++i)
    {
        if (shield->hitsize->IsRectCollision(pl_mon[i]))
        {
            pl_mon[i]->monster_atk = 0;
        }
        else
        {
            pl_mon[i]->monster_atk = 15;
        }
    }
}