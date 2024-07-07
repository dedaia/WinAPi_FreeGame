#include "Framework.h"

Landscape::Landscape(wstring file, bool autoPlay)
{
    for (int i = 0; i < 2; i++)
    {
        ImageRect* bg = new ImageRect(file);
        bg->pos = { bg->Half().x + bg->size.x * i, bg->Half().y};        
        bgs.push_back(bg);
    }

    autoScroll = autoPlay;
}

Landscape::~Landscape()
{
    for (ImageRect* bg : bgs)
        delete bg;
}

void Landscape::Update()
{
    if (autoScroll)
    {
        for (ImageRect* bg : bgs)
        {
            bg->pos.x -= bgSpeed * DELTA;

            if (bg->Right() <= 0.0f)
            {
                bg->pos.x += bg->size.x * 2.0f;
            }
        }
    }
}

void Landscape::Render(HDC hdc)
{
    for (ImageRect* bg : bgs)
        bg->Render(hdc, { 0, 0 }, false);
}
