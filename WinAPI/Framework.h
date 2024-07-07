#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 100
#define WIN_START_Y 100

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

// PI ratio (with misspelling)
#define PI 3.141592f
#define PHI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <functional>

using namespace std;

//Framework Header
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Keyboard.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

//Renderer Header
#include "Framework/Render/Texture.h"
#include "Framework/Render/Animation.h"

// Basic Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"

// Objects Manager Header
#include "Manager/PoolingManager.h"

// Inherited Object Header

#include "Objects/Angle/Cannon.h"

#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"
#include "Objects/Shooting/Plane.h"
#include "Objects/Shooting/Enemy.h"
#include "Objects/Shooting/EnemyManager.h"

//Scene and Scene Specifics Header
#include "Scenes/Scene.h"

#include "Scenes/_SampleScene/Landscape.h"
#include "Scenes/_SampleScene/StageManager.h"
#include "Objects/_SampleCharacter/SampleCharacter.h"
#include "Objects/_PlayerC/PlayerChar.h"
#include "Objects/_PlayerC/Slash_hit.h"
#include "Objects/_Monster/Plant_monster.h"
#include "Objects/_PlayerC/PlayUI.h"
#include "Objects/_PlayerC/Shield.h"

//Game Manager Header
#include "Manager/GameManager.h"
#include "Manager/Physics.h"
#include "Scenes/_SampleScene/SampleScene.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;