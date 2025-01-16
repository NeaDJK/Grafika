#pragma once

#include "resource.h"
#include "Const.h"

int scale = 100;
int indent = 30;

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

HGDIOBJ tobj = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"");

HGDIOBJ colorPlayer0 = CreateSolidBrush(RGB(0, 0, 0));
HGDIOBJ colorPlayer1 = CreateSolidBrush(RGB(255, 0, 0));
HGDIOBJ colorPlayer2 = CreateSolidBrush(RGB(255, 255, 0));
HGDIOBJ colorPlayer3 = CreateSolidBrush(RGB(0, 0, 255));
HGDIOBJ colorPlayer4 = CreateSolidBrush(RGB(255, 255, 255));

void PaintStart(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_start[0], -1, & r, DT_VCENTER);
}

void PaintBank(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_bank[0], -1, &r, DT_VCENTER);
}

void PaintBuySell(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR name, LPCWSTR type, LPCWSTR cost)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, name, -1, &r, DT_VCENTER);
    SetRect(&r, p.x, p.y + 20, p.x + scale, p.y + scale);
    DrawTextW(hdc, type, -1, &r, DT_VCENTER);
    SetRect(&r, p.x+20, p.y + 50, p.x + scale, p.y + scale);
    DrawTextW(hdc, cost, -1, &r, DT_VCENTER);
}

void PaintIncident(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_incident[0], -1, &r, DT_VCENTER);
}

void PaintPrison(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_prison[0], -1, &r, DT_VCENTER);
}

void PaintRest(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, &name_rest[0], -1, &r, DT_VCENTER);
}

void PaintPlayer(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, int num)
{
    SelectObject(hdc, *obj);
    Ellipse(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    //DrawTextW(hdc, ToLPWSTR(num), -1, &r, DT_VCENTER);
}
