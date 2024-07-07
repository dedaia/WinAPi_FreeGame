#include "Framework.h"
#include "Slash_hit.h"

Slash_hit::Slash_hit(int vl)
{
    texture = Texture::Add(L"Textures/_char/Slash/Slash_bitmap.bmp", 8, 1);
    imageRect = new ImageRect(texture);
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    spawn_pos = vl;

    CreateAnimations();
    animations[curAction]->Play();
}

void Slash_hit::Start(Rect* source, int position)
{
    spawn_pos;
    SetPosition(source, position);
    isActive = true;
}

void Slash_hit::SetPosition(Rect* source, int position)
{
    float originX = source->pos.x;
    float originY = source->pos.y;

    float destX;
    float destY;

    if (position == 1) // 왼쪽
    {
        destX = originX - spawn_pos;
        destY = originY;
        SetAction(LEFT);
    }
    else if (position == 2) // 왼쪽 위
    {
        destX = originX - spawn_pos;
        destY = originY - spawn_pos;
        SetAction(LEFT_TOP);
    }
    else if (position == 3) // 위
    {
        destX = originX;
        destY = originY - spawn_pos;
        SetAction(TOP);
    }
    else if (position == 4) // 오른쪽 위
    {
        destX = originX + spawn_pos;
        destY = originY - spawn_pos;
        SetAction(RIGHT_TOP);
    }
    else if (position == 5) // 오른쪽
    {
        destX = originX + spawn_pos;
        destY = originY;
        SetAction(RIGTH);
    }
    else if (position == 6) // 오른쪽 아래
    {
        destX = originX + spawn_pos;
        destY = originY + spawn_pos;
        SetAction(RIGTH_BOTTOM);
    }
    else if (position == 7) // 아래
    {
        destX = originX;
        destY = originY + spawn_pos;
        SetAction(BOTTOM);
    }
    else if (position == 8) // 왼쪽 아래
    {
        destX = originX - spawn_pos;
        destY = originY + spawn_pos;
        SetAction(LEFT_BOTTOM);
    }

    this->pos.x = destX;
    this->pos.y = destY;
}

void Slash_hit::Update()
{
    if (isActive) currentTime += DELTA; //누적시간 더하기

    if (currentTime > timeSpan)
    {
        currentTime = 0; //시간리셋
        isActive = false;
    }

    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();
}

void Slash_hit::Render(HDC _hdc)
{
    // Rect::LineRender(_hdc);

    imageRect->Render(_hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());
}

void Slash_hit::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void Slash_hit::CreateAnimations()
{
    animations[LEFT] = new Animation(texture->GetFrame());
    animations[LEFT]->SetPart(0, 0, true);

    animations[LEFT_TOP] = new Animation(texture->GetFrame());
    animations[LEFT_TOP]->SetPart(1, 1, true);

    animations[TOP] = new Animation(texture->GetFrame());
    animations[TOP]->SetPart(2, 2, true);

    animations[RIGHT_TOP] = new Animation(texture->GetFrame());
    animations[RIGHT_TOP]->SetPart(3, 3, true);

    animations[RIGTH] = new Animation(texture->GetFrame());
    animations[RIGTH]->SetPart(4, 4, true);

    animations[RIGTH_BOTTOM] = new Animation(texture->GetFrame());
    animations[RIGTH_BOTTOM]->SetPart(5, 5, true);

    animations[BOTTOM] = new Animation(texture->GetFrame());
    animations[BOTTOM]->SetPart(6, 6, true);

    animations[LEFT_BOTTOM] = new Animation(texture->GetFrame());
    animations[LEFT_BOTTOM]->SetPart(7, 7, true);
}

int Slash_hit::slah_LEVEL(int LEVEL)
{
    if (LEVEL == 1)
    {
        return spawn_pos = 60;
    }
    else if (LEVEL == 2)
    {
        return spawn_pos = 120;
    }
    else if (LEVEL == 3)
    {
        return spawn_pos = 180;
    }
    else if (LEVEL == 4)
    {
        return spawn_pos = 240;
    }
    else if (LEVEL == 5)
    {
        return spawn_pos = 300;
    }
    else
    {

    }
}