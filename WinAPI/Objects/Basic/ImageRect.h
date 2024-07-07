#pragma once

class ImageRect : public Rect
{
public:
    ImageRect(wstring file, UINT frameX = 1, UINT frameY = 1,
        COLORREF transColor = MAGENTA);
    ImageRect(Texture* texture);
    ~ImageRect() = default;

    void Render(HDC hdc, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, bool isLeft, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

protected:
    Texture* texture;
};