// Grafika.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Grafika.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void PaintStart(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, LPCWSTR(L"Старт"), -1, &r,  DT_VCENTER);
}

void PaintBank(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, LPCWSTR(L"Банк"), -1, &r, DT_VCENTER);
}

void PaintBuySell(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale, LPCWSTR name)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, name, -1, &r, DT_VCENTER);
}

void PaintIncident(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, LPCWSTR(L"Событие"), -1, &r, DT_VCENTER);
}

void PaintPrison(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale)
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, LPCWSTR(L"Событие"), -1, &r, DT_VCENTER);
}

void PaintRest(HDC hdc, HGDIOBJ* obj, HGDIOBJ* tobj, POINT p, int scale) 
{
    SelectObject(hdc, *obj);
    Rectangle(hdc, p.x, p.y, p.x + scale, p.y + scale);
    SelectObject(hdc, *tobj);
    RECT r;
    SetRect(&r, p.x, p.y, p.x + scale, p.y + scale);
    DrawTextW(hdc, LPCWSTR(L"Отдых"), -1, &r, DT_VCENTER);
}

HGDIOBJ obj;
HGDIOBJ tobj = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"");

void Paint(HDC hdc, WPARAM wParam, LPARAM lParam) 
{
    HGDIOBJ objdef = CreateSolidBrush(RGB(132, 45, 200));
    POINT point;
    int scale = 75;
    int lenght = 10;
    point.x = 250;
    point.y = 10;

    for (int i = 0; i < lenght; i++)
    {
        point.x += scale + 10;
        
        switch (i)
        {
        case 0:
            obj = CreateSolidBrush(RGB(210, 10, 200));
            PaintStart(hdc, &obj, &tobj, point, scale);
            break;
        case 1:
            obj = CreateSolidBrush(RGB(10, 220, 100));
            PaintBank(hdc, &obj, &tobj, point, scale);
            break;
        case 2:
            obj = CreateSolidBrush(RGB(30, 120, 200));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Золото");
            break;
        case 3:
            obj = CreateSolidBrush(RGB(120, 120, 150));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Серебро");
            break;
        case 4:
            obj = CreateSolidBrush(RGB(124, 34, 93));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Медь");
            break;
        case 5:
            obj = CreateSolidBrush(RGB(0, 110, 0));
            PaintIncident(hdc, &obj, &tobj, point, scale);
            break;
        case 6:
            obj = CreateSolidBrush(RGB(200, 120, 10));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Газ");
            break;
        case 7:
            obj = CreateSolidBrush(RGB(0, 0, 0));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Уголь");
            break;
        case 8:
            obj = CreateSolidBrush(RGB(200, 158, 100));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Нефть");
            break;
        case 9:
            obj = CreateSolidBrush(RGB(60, 89, 182));
            PaintRest(hdc, &obj, &tobj, point, scale);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < lenght - 1; i++)
    {
        point.y += scale + 10;

        switch (i)
        {
        case 0:
            obj = CreateSolidBrush(RGB(210, 10, 200));
            PaintStart(hdc, &obj, &tobj, point, scale);
            break;
        case 1:
            obj = CreateSolidBrush(RGB(10, 220, 100));
            PaintBank(hdc, &obj, &tobj, point, scale);
            break;
        case 2:
            obj = CreateSolidBrush(RGB(30, 120, 200));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Золото");
            break;
        case 3:
            obj = CreateSolidBrush(RGB(120, 120, 150));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Серебро");
            break;
        case 4:
            obj = CreateSolidBrush(RGB(124, 34, 93));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Медь");
            break;
        case 5:
            obj = CreateSolidBrush(RGB(0, 110, 0));
            PaintIncident(hdc, &obj, &tobj, point, scale);
            break;
        case 6:
            obj = CreateSolidBrush(RGB(200, 120, 10));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Газ");
            break;
        case 7:
            obj = CreateSolidBrush(RGB(0, 0, 0));
            PaintBuySell(hdc, &obj, &tobj, point, scale, L"Уголь");
            break;
        
        default:
            break;
        }
    }
}   

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAFIKA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAFIKA));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; 
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAFIKA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAFIKA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            Paint(hdc, wParam, lParam);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
