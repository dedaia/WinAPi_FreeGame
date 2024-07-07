#include "Framework.h"

void StageManager::Update()
{
    if (!isPlay) return;

    if (isAutoScroll)
    {
        for (pair<string, Objects> objects : totalObjects)
        {
            for (GameObject* object : objects.second)
            {
                object->Update();

                ImageRect* rect = (ImageRect*)object;

                rect->pos.x -= speed * DELTA;

                if (rect->Right() <= 0.0f)
                {
                    rect->isActive = true;
                    rect->pos.x += width * tileSize.x;
                }
            }
        }
    }
}

void StageManager::Render(HDC hdc)
{
    vector<GameObject*> grounds = totalObjects["Ground"];

    for (GameObject* ground : grounds)
    {
        ImageRect* rect = (ImageRect*)ground;
        rect->Render(hdc);
    }

    vector<GameObject*> pickups = totalObjects["Pickup"];

    for (GameObject* pickup : pickups)
    {
        pickup->Render(hdc);
    }

    vector<GameObject*> obstacles = totalObjects["Obstacle"];

    for (GameObject* obstacle : obstacles)
    {
        ImageRect* rect = (ImageRect*)obstacle;
        rect->Render(hdc);
    }

    SetTextColor(hdc, WHITE);

    
}

void StageManager::Move(float _x, float _y)
{
    for (pair<string, Objects> objects : totalObjects)
    {
        for (GameObject* object : objects.second)
        {
            object->Update();

            ImageRect* rect = (ImageRect*)object;

            rect->pos.x -= _x;
            rect->pos.y += _y;

            speed = _x;

            if (rect->Right() <= 0.0f) 
            {
                rect->isActive = true; 
                rect->pos.x += width * tileSize.x;
            }
            if (rect->Left() >= WIN_WIDTH)
            {
                rect->isActive = true;
                rect->pos.x -= width * tileSize.x;
            }

            if (rect->Bottom() <= 0.0f)
            {
                rect->isActive = true; 
                rect->pos.y += height * tileSize.y;
                //rect->pos.y = WIN_HEIGHT + (tileSize.y / 2);
            }

            if (rect->Top() >= WIN_HEIGHT)
            {
                rect->isActive = true; 
                rect->pos.y -= height * tileSize.y; 

                //rect->pos.y = 0 - (tileSize.y / 2);
            }
        }
    }
}

float StageManager::GetGroundHeight(Vector2 pos)
{
    vector<GameObject*> grounds = totalObjects["Ground"];

    float minHeight = WIN_HEIGHT;

    for (GameObject* ground : grounds)
    {
        ImageRect* rect = (ImageRect*)ground;
        
        if (pos.x < rect->Left() || pos.x > rect->Right())
            continue;

        if (pos.y >= rect->Top())
            continue;

        if (rect->Top() < minHeight)
            minHeight = rect->Top();
    }

    return minHeight;
}

void StageManager::CollisionPickup(GameObject* object)
{
    vector<GameObject*> pickups = totalObjects["Pickup"];

    for (GameObject* pickup : pickups)
    {
        if (pickup->IsCollision(object))
        {
            pickup->isActive = false;
            score++;
            return;
        }
    }
}

bool StageManager::CollisionObstacle(GameObject* object)
{
    vector<GameObject*> obstacles = totalObjects["Obstacle"];

    for (GameObject* obstacle : obstacles)
    {
        if (obstacle->IsCollision(object))
        {            
            return true;
        }
    }

    return false;
}

void StageManager::LoadTileData(string file)
{
    ifstream loadFile(file);

    string temp;

    while (true)
    {
        loadFile >> temp;

        vector<string> datas = SplitString(temp, ",");

        width = datas.size();

        vector<TileType> rowDatas;
        rowDatas.reserve(width);

        for (string data : datas)
        {
            rowDatas.push_back((TileType)stoi(data));
        }

        tileData.push_back(rowDatas);
        height++;

        if (loadFile.eof())
            break;
    }

    //tileSize = { WIN_WIDTH / (float)width * 2.0f, WIN_HEIGHT / (float)height };

    float asdf = WIN_WIDTH / (float)width * 2.0f;
    tileSize = { asdf , asdf };

    CreateTile();
}

void StageManager::CreateTile()
{
    vector<GameObject*> grounds;
    vector<GameObject*> pickups;
    vector<GameObject*> obstacles;

    grounds.reserve(width);
    pickups.reserve(width);
    obstacles.reserve(width);

    Vector2 startOffset = tileSize * 0.5f;

    for (UINT y = 0; y < height; y++)
    {
        for (UINT x = 0; x < width; x++)
        {
            TileType type = tileData[y][x];

            switch (type)
            {
            case StageManager::GROUND:
            {
                ImageRect* ground = new ImageRect(L"Textures/_SampleScene/Ground.bmp");
                ground->pos = startOffset + tileSize * Vector2(x, y);
                grounds.push_back(ground);
            }
                break;
            case StageManager::PICKUP:
            {
                //집어드는 아이템이 있으면 여기에 코드 넣기
                // 
                // * 스테이지 매니징 방식에서, 기본적으로
                // 집어드는 아이템이나 장애물은 "땅"과
                // 같은 방식으로 만들면 됩니다.
            }
                break;
            case StageManager::OBSTACLE:
            {
                //장애물이 있으면 여기에 코드 넣기
                // 
                // * 스테이지 매니징 방식에서, 기본적으로
                // 집어드는 아이템이나 장애물은 "땅"과
                // 같은 방식으로 만들면 됩니다.
            }
                break;
            default:
                break;
            }
        }
    }

    totalObjects["Ground"] = grounds;
    totalObjects["Pickup"] = pickups;
    totalObjects["Obstacle"] = obstacles;
}
