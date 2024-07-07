#include "Framework.h"
#include "Physics.h"

bool Physics::IsRectCollision(PlayerChar* play, Rect* rect)
{
    if (!play->isActive) return false;
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

bool Physics::IsRectCollision(Rect* play, Rect* rect)
{
    if (!play->isActive) return false;
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

void Physics::AllCollision(vector<Plant_monster*> pla)
{
    plantCollision(pla);
}

void Physics::plantCollision(vector<Plant_monster*> pla)
{
    for (int i = 0; i < pla.size(); ++i)
    {
        for (int j = i + 1; j < i; ++j)
        {
            if (GetCollisionDirection(pla[i]->hitsize, pla[j]->hitsize) == LEFT)
            {
                pla[i]->pos.x += 1;
            }
            else if (GetCollisionDirection(pla[i]->hitsize, pla[j]->hitsize) == RIGHT)
            {
                pla[i]->pos.x -= 1;
            }
            else if (GetCollisionDirection(pla[i]->hitsize, pla[j]->hitsize) == ABOVE)
            {
                pla[i]->pos.y += 1;
            }
            else if (GetCollisionDirection(pla[i]->hitsize, pla[j]->hitsize) == BENEATH)
            {
                pla[i]->pos.y -= 1;
            }
        }
    }
}