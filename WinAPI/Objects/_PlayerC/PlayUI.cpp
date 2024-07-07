#include "Framework.h"
#include "PlayUI.h"

PlayUI::PlayUI()
{
	UI_on = false;

	ui_center_x = 1090;
	ui_center_y = 325;

	ui_size_x = 40;
	ui_size_y = 20;

	ui_LV_size_x = 5;
	ui_LV_size_y = 5;
}

PlayUI::~PlayUI()
{

}

void PlayUI::Update()
{
	mousePos.x;
	mousePos.y;

	atk;
	hp;
	speed;
	slah_LV;

	if (UI_on)
	{
		// 공격력 상승
		if ((mousePos.x >= (980) - ui_size_x &&
			mousePos.y >= (105) - ui_size_y &&
			mousePos.x <= (980) + ui_size_x &&
			mousePos.y <= (105) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			atk = atk * 1.1;
		}

		// 체력 상승
		if ((mousePos.x >= (1090) - ui_size_x &&
			mousePos.y >= (105) - ui_size_y &&
			mousePos.x <= (1090) + ui_size_x &&
			mousePos.y <= (105) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			hp = hp * 1.1;
		}

		// 걷기 스피드 상승
		if ((mousePos.x >= (1199) - ui_size_x &&
			mousePos.y >= (105) - ui_size_y &&
			mousePos.x <= (1199) + ui_size_x &&
			mousePos.y <= (105) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			speed = speed * 1.1;
		}

		// 슬래셔 레벨 상승
		if ((mousePos.x >= (980) - ui_size_x &&
			mousePos.y >= (165) - ui_size_y &&
			mousePos.x <= (980) + ui_size_x &&
			mousePos.y <= (165) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			slah_LV++;

			if (slah_LV > 5)
			{
				slah_LV = 5;
			}
		}

		// 쉴드월 레벨 상승
		if ((mousePos.x >= (1090) - ui_size_x &&
			mousePos.y >= (165) - ui_size_y &&
			mousePos.x <= (1090) + ui_size_x &&
			mousePos.y <= (165) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			shield_LV++;

			if (shield_LV > 4)
			{
				shield_LV = 4;
			}
		}

		// 드래곤 길들이기
		if ((mousePos.x >= (1199) - ui_size_x &&
			mousePos.y >= (225) - ui_size_y &&
			mousePos.x <= (1199) + ui_size_x &&
			mousePos.y <= (225) + ui_size_y) &&
			KEY_DOWN(VK_LBUTTON))
		{
			if (!Dragon_on_off)
			{
				Dragon_on_off = true;
			}
		}
	}

	
}

void PlayUI::GetUp()
{

}

void PlayUI::Render(HDC hdc)
{
	if ((mousePos.x >= 1200 &&
		mousePos.x <= 1250 && 
		mousePos.y >= 50 && 
		mousePos.y <= 100) || KEY_DOWN(VK_HOME))
	{
		if (KEY_DOWN(VK_LBUTTON) || KEY_DOWN(VK_HOME))
		{
			if (!UI_on)
			{
				UI_on = true;
			}
			else
			{
				UI_on = false;
			}
		}
	}

	if (mousePos.x <= 900)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (UI_on)
			{
				UI_on = false;
			}
		}
	}

	

	if (UI_on)
	{
		StageManager::Get()->Stop();

		Rectangle(hdc, 900, 0, 1280, 650);

		//HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//HGDIOBJ oldPen = SelectObject(hdc, pen);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HGDIOBJ oldBrush = SelectObject(hdc, brush);

		Rectangle(hdc, 905, 5, 1275, 645);

		//SelectObject(hdc, oldPen);
		//DeleteObject(pen);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

		// 1층 주민
		// 공격력 업
		Rectangle(hdc, (980) - ui_size_x, (105) - ui_size_y, (980) + ui_size_x, (105) + ui_size_y);
		
		// 체력 업
		Rectangle(hdc, (1090) - ui_size_x, (105) - ui_size_y, (1090) + ui_size_x, (105) + ui_size_y);
		
		// 스피드 업
		Rectangle(hdc, (1199) - ui_size_x, (105) - ui_size_y, (1199) + ui_size_x, (105) + ui_size_y);

		// 2층 주민
		// 더블 슬레시
		Rectangle(hdc, (980) - ui_size_x, (165) - ui_size_y, (980) + ui_size_x, (165) + ui_size_y);
		if (slah_LV == 1)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (950) - ui_LV_size_x, (175) - ui_LV_size_y, (950) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (slah_LV == 2)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (950) - ui_LV_size_x, (175) - ui_LV_size_y, (950) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (962) - ui_LV_size_x, (175) - ui_LV_size_y, (962) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (slah_LV == 3)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (950) - ui_LV_size_x, (175) - ui_LV_size_y, (950) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (962) - ui_LV_size_x, (175) - ui_LV_size_y, (962) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (974) - ui_LV_size_x, (175) - ui_LV_size_y, (974) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (slah_LV == 4)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (950) - ui_LV_size_x, (175) - ui_LV_size_y, (950) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (962) - ui_LV_size_x, (175) - ui_LV_size_y, (962) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (974) - ui_LV_size_x, (175) - ui_LV_size_y, (974) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (986) - ui_LV_size_x, (175) - ui_LV_size_y, (986) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (slah_LV == 5)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (950) - ui_LV_size_x, (175) - ui_LV_size_y, (950) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (962) - ui_LV_size_x, (175) - ui_LV_size_y, (962) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (974) - ui_LV_size_x, (175) - ui_LV_size_y, (974) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (986) - ui_LV_size_x, (175) - ui_LV_size_y, (986) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (998) - ui_LV_size_x, (175) - ui_LV_size_y, (998) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		
		// 방패벽
		Rectangle(hdc, (1090) - ui_size_x, (165) - ui_size_y, (1090) + ui_size_x, (165) + ui_size_y);
		if (shield_LV == 1)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (1060) - ui_LV_size_x, (175) - ui_LV_size_y, (1060) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (shield_LV == 2)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (1060) - ui_LV_size_x, (175) - ui_LV_size_y, (1060) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1072) - ui_LV_size_x, (175) - ui_LV_size_y, (1072) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (shield_LV == 3)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (1060) - ui_LV_size_x, (175) - ui_LV_size_y, (1060) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1072) - ui_LV_size_x, (175) - ui_LV_size_y, (1072) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1084) - ui_LV_size_x, (175) - ui_LV_size_y, (1084) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		if (shield_LV == 4)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			Rectangle(hdc, (1060) - ui_LV_size_x, (175) - ui_LV_size_y, (1060) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1072) - ui_LV_size_x, (175) - ui_LV_size_y, (1072) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1084) - ui_LV_size_x, (175) - ui_LV_size_y, (1084) + ui_LV_size_x, (175) + ui_LV_size_y);
			Rectangle(hdc, (1096) - ui_LV_size_x, (175) - ui_LV_size_y, (1096) + ui_LV_size_x, (175) + ui_LV_size_y);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		
		wstring Hea = L"체력 : " + to_wstring((int)hp);
		TextOut(hdc, (int)0, 60, Hea.c_str(), (int)Hea.length());

		wstring str = L"공격력 : " + to_wstring((int)atk);
		TextOut(hdc, (int)0, 80, str.c_str(), (int)str.length());

		wstring spd = L"스피드 : " + to_wstring((int)speed);
		TextOut(hdc, (int)0, 100, spd.c_str(), (int)spd.length());
	}
	else
	{
		StageManager::Get()->Play();

		Rectangle(hdc, 1200, 50, 1250, 100);
		Rectangle(hdc, 1205, 55, 1245, 95);
	}
	
}

void PlayUI::player_level_up(HDC hdc, bool level_up)
{
	if (level_up)
	{
		Rectangle(hdc, 300, 300, 980, 500);
	}
}

// 스킬
// 더블 슬레시 (우선 착수)
// 방패벽
// 방패 돌진
// 초토화
// 
// 용용이 소환
//