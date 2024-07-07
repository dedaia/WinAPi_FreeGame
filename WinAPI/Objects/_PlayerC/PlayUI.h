#pragma once
class PlayUI : public Rect
{
public:
	PlayUI();
	~PlayUI();

	bool UI_on;

	int ui_center_x;
	int ui_center_y;

	int ui_size_x;
	int ui_size_y;

	int ui_LV_size_x;
	int ui_LV_size_y;

	float atk;
	float hp;
	float speed;

	bool Dragon_on_off = false;

	int slah_LV = 1;
	int shield_LV = 0;	

	void Update();
	void Render(HDC hdc) ;

	void player_level_up(HDC hdc, bool level_up);

	void GetUp();
};

