#pragma once

class Landscape
{
public:
    Landscape(wstring file, bool autoPlay);
    ~Landscape();

    void Update();
    void Render(HDC hdc);

    void SetSpeed(float speed) { bgSpeed = speed; }

private:
    vector<ImageRect*> bgs;

    float bgSpeed = 100.0f;
    bool autoScroll = false;
};