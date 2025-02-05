    #pragma once

#include "resource.h"
#include "Const.h"

int scale = 100;
int indent = 30;
int frameWidth = 6;

HGDIOBJ tobj = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"");

HGDIOBJ penDef = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HGDIOBJ penPlayer0 = CreatePen(PS_SOLID, frameWidth,RGB(0, 0, 0));
HGDIOBJ penPlayer1 = CreatePen(PS_SOLID, frameWidth,RGB(255, 0, 0));
HGDIOBJ penPlayer2 = CreatePen(PS_SOLID, frameWidth,RGB(255, 255, 0));
HGDIOBJ penPlayer3 = CreatePen(PS_SOLID, frameWidth,RGB(0, 0, 255));
HGDIOBJ penPlayer4 = CreatePen(PS_SOLID, frameWidth,RGB(255, 255, 255));

HGDIOBJ colorDef = CreateSolidBrush(RGB(0, 0, 0));

LOGBRUSH hollowBrush = { BS_HOLLOW, RGB(0, 0, 0), NULL };
HGDIOBJ colorHollow = CreateBrushIndirect(&hollowBrush);

HGDIOBJ colorStart = CreateSolidBrush(RGB(210, 10, 200));
HGDIOBJ colorBank = CreateSolidBrush(RGB(10, 150, 20));
HGDIOBJ colorIncident = CreateSolidBrush(RGB(255, 20, 147));
HGDIOBJ colorPrison = CreateSolidBrush(RGB(145, 54, 160));
HGDIOBJ colorRest = CreateSolidBrush(RGB(60, 89, 182));

HGDIOBJ colorGold = CreateSolidBrush(RGB(200, 120, 10));
HGDIOBJ colorCopper = CreateSolidBrush(RGB(203, 92, 13));
HGDIOBJ colorIron = CreateSolidBrush(RGB(120, 120, 150));
HGDIOBJ colorSalt = CreateSolidBrush(RGB(255, 240, 255));
HGDIOBJ colorGas = CreateSolidBrush(RGB(80, 250, 250));
HGDIOBJ colorCoal = CreateSolidBrush(RGB(0, 0, 0));
HGDIOBJ colorOil = CreateSolidBrush(RGB(100, 50, 50));

HGDIOBJ colorPlayer0 = CreateSolidBrush(RGB(0, 0, 0));
HGDIOBJ colorPlayer1 = CreateSolidBrush(RGB(255, 0, 0));
HGDIOBJ colorPlayer2 = CreateSolidBrush(RGB(255, 255, 0));
HGDIOBJ colorPlayer3 = CreateSolidBrush(RGB(0, 0, 255));
HGDIOBJ colorPlayer4 = CreateSolidBrush(RGB(255, 255, 255));

void PaintFrame(HDC hdc, HGDIOBJ* obj, HGDIOBJ* pobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    SelectObject(hdc, *pobj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, penDef);
    SelectObject(hdc, colorDef);
}

void PaintStart(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR id)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_start[0], -1, & r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintBank(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR id)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_bank[0], -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintBuySell(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR name, LPCWSTR type, LPCWSTR cost, LPCWSTR id)
{
    HDC bmpdc = CreateCompatibleDC(hdc);
    HBITMAP hBmp = (HBITMAP)LoadImage(hInst, id, IMAGE_BITMAP, scale, scale, LR_COPYFROMRESOURCE);
    if (hBmp)
    {
        SelectObject(bmpdc, hBmp);
        BitBlt(hdc, p.x, p.y, p.x + scale, p.y + scale, bmpdc, 0, 0, SRCCOPY);
    }
    else
    {
        SelectObject(hdc, *obj);
        Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
        SelectObject(hdc, *tobj);
    }
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, name, -1, &r, DT_VCENTER);
    SetRect(&r, p.x, p.y + 20, p.x + scale, p.y + scale);
    DrawTextW(hdc, type, -1, &r, DT_VCENTER);
    SetRect(&r, p.x+20, p.y + 50, p.x + scale, p.y + scale);
    DrawTextW(hdc, cost, -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintIncident(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR id)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_incident[0], -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintPrison(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR id)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_prison[0], -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintRest(HINSTANCE hInst, HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR id)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_rest[0], -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}

void PaintPlayer(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, int num)
{
    SelectObject(hdc, *obj);
    Ellipse(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    //DrawTextW(hdc, ToLPWSTR(num), -1, &r, DT_VCENTER);
    SelectObject(hdc, colorDef);
}
