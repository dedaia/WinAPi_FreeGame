#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;
bool Texture::isDebugMode = false;

Texture::Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY)
    : imageFrame{ (long)frameX, (long)frameY }, transfColor(transColor)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    stretchDC = CreateCompatibleDC(hdc);
    alphaMemDC = CreateCompatibleDC(hdc);
    hBitmap = (HBITMAP)LoadImage(hInst, file.c_str(),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);    

    SelectObject(memDC, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    imageSize = { bitmap.bmWidth, bitmap.bmHeight };    

    cutSize = { imageSize.x / imageFrame.x, imageSize.y / imageFrame.y };    

    hStretchBitmap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);
    hAlphaBitmap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);

    SelectObject(stretchDC, hStretchBitmap);
    SelectObject(alphaMemDC, hAlphaBitmap);

    ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteDC(stretchDC);
    DeleteDC(alphaMemDC);
    DeleteObject(hBitmap);
    DeleteObject(hStretchBitmap);
    DeleteObject(hAlphaBitmap);
}

Texture* Texture::Add(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Texture(file, transColor, frameX, frameY);
    textures[file] = texture;

    return texture;
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
    {
        delete texture.second;
    }
}

void Texture::Render(HDC hdc, Rect* rect, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,            
            SRCCOPY
        );
        return;
    }

    GdiTransparentBlt(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );
}

void Texture::Render(HDC hdc, Rect* rect, int alpha, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    blendFunc.SourceConstantAlpha = alpha;

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,
            SRCCOPY
        );
        return;
    }

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );

    GdiAlphaBlend(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        blendFunc
    );
}

void Texture::Render(HDC hdc, Rect* rect, bool isLeft, int alpha, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    blendFunc.SourceConstantAlpha = alpha;
    int leftMult = isLeft ? -1 : 1 ;

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,
            SRCCOPY
        );
        return;
    }

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        SRCCOPY
    );

    StretchBlt(
        stretchDC,
        0, 0,
        cutSize.x, cutSize.y,
        memDC,
        cutSize.x * (curFrame.x + (int)isLeft) - (int)isLeft,
        cutSize.y * curFrame.y,
        cutSize.x * leftMult, cutSize.y,
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        stretchDC,
        0, 0,
        //cutSize.x * curFrame.x,
        //cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );

    GdiAlphaBlend(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        blendFunc
    );
}