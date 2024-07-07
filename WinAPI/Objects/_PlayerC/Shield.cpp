#include "Framework.h"
#include "Shield.h"

Shield::Shield()
{
    srand(GetTickCount64());

    texture = Texture::Add(L"Textures/_char/Shild.bmp", 7, 2);
    imageRect = new ImageRect(texture);
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    

    float sizeX = 200;
    float sizeY = 200;
    float posX = CENTER_X;
    float posY = CENTER_Y + sizeY / 2;

    hitsize = new Rect(Vector2(posX, posY), Vector2(sizeX, sizeY));

    CreateAnimations();
    animations[curAction]->Play();
}

Shield::~Shield()
{
    delete imageRect;


    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;
}

void Shield::HitBox()
{
    hitsize->pos = Vector2(pos.x, pos.y);
}

void Shield::Update()
{
    if (shield_number == 1)
    {
        SetAction(shi1);
    }
    else if (shield_number == 2)
    {
        SetAction(shi2);
    }
    else if (shield_number == 3)
    {
        SetAction(shi3);
    }
    else if (shield_number == 4)
    {
        SetAction(shi4);
    }
    else if (shield_number == 5)
    {
        SetAction(shi5);
    }
    else if (shield_number == 6)
    {
        SetAction(shi6);
    }
    else if (shield_number == 7)
    {
        SetAction(shi7);
    }
    else if (shield_number == 8)
    {
        SetAction(shi8);
    }
    else if (shield_number == 9)
    {
        SetAction(shi9);
    }
    else if (shield_number == 10)
    {
        SetAction(shi10);
    }
    else if (shield_number == 11)
    {
        SetAction(shi11);
    }
    else if (shield_number == 12)
    {
        SetAction(shi12);
    }
    else if (shield_number == 13)
    {
        SetAction(shi13);
    }
    else if (shield_number == 14)
    {
        SetAction(shi14);
    }

    if (KEY_PRESS(VK_UP) )
    {
        pos.y += player_speed * DELTA;
    }
    if (KEY_PRESS(VK_DOWN) )
    {
        pos.y -= player_speed * DELTA;
    }
    if (KEY_PRESS(VK_LEFT) )
    {
        pos.x += player_speed * DELTA;
    }
    if (KEY_PRESS(VK_RIGHT) )
    {
        pos.x -= player_speed * DELTA;
    }

    HitBox();

    hitsize->Update();

    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();
}

void Shield::Use(Rect* source)
{
    pos_aaaa = rand() % 4 + 1;
    pos_wi = rand() % 100 + 1;

    shield_number = rand() % 14 + 1;

    SetPos(source, pos_aaaa, pos_wi);
}

void Shield::Render(HDC hdc)
{
    // Rect::LineRender(hdc); 

    // hitsize->Render(hdc);

    imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());
}

void Shield::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void Shield::SetPos(Rect* source, int pos, int pos_wi)
{
    if (!life)
    {
        float originX = source->pos.x;
        float originY = source->pos.y;

        float destX;
        float destY;

        if (pos == 1)
        {
            destX = originX + 200;
            destY = originY;
        }
        else if (pos == 2)
        {
            destX = originX;
            destY = originY + 200;
        }
        else if (pos == 3)
        {
            destX = originX - 200;
            destY = originY;
        }
        else if (pos == 4)
        {
            destX = originX;
            destY = originY - 200;
        }

        this->pos.x = destX;
        this->pos.y = destY;

        life = true;
    }

    
}

void Shield::CreateAnimations()
{
    animations[shi1] = new Animation(texture->GetFrame());
    animations[shi1]->SetPart(0, 0, true);

    animations[shi2] = new Animation(texture->GetFrame());
    animations[shi2]->SetPart(1, 1, true);

    animations[shi3] = new Animation(texture->GetFrame());
    animations[shi3]->SetPart(2, 2, true);

    animations[shi4] = new Animation(texture->GetFrame());
    animations[shi4]->SetPart(3, 3, true);

    animations[shi5] = new Animation(texture->GetFrame());
    animations[shi5]->SetPart(4, 4, true);

    animations[shi6] = new Animation(texture->GetFrame());
    animations[shi6]->SetPart(5, 5, true);

    animations[shi7] = new Animation(texture->GetFrame());
    animations[shi7]->SetPart(6, 6, true);

    animations[shi8] = new Animation(texture->GetFrame());
    animations[shi8]->SetPart(7, 7, true);

    animations[shi9] = new Animation(texture->GetFrame());
    animations[shi9]->SetPart(8, 8, true);

    animations[shi10] = new Animation(texture->GetFrame());
    animations[shi10]->SetPart(9, 9, true);

    animations[shi11] = new Animation(texture->GetFrame());
    animations[shi11]->SetPart(10, 10, true);

    animations[shi12] = new Animation(texture->GetFrame());
    animations[shi12]->SetPart(11, 11, true);

    animations[shi13] = new Animation(texture->GetFrame());
    animations[shi13]->SetPart(12, 12, true);

    animations[shi14] = new Animation(texture->GetFrame());
    animations[shi14]->SetPart(13, 13, true);
}