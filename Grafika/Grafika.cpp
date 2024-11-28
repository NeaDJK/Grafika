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
    DrawTextW(hdc, LPCWSTR(L"Стартыжвкрпшгывкрдпшфаыупвкаепнгрхзщдшлгонрк"), -1, &r,  DT_VCENTER);
    //TextOut(hdc, p.x + 5, p.y + 20, LPCWSTR(L"Стартыжвкрпшгывкрдпшфаыупвкаепнгрхзщдшлгонрк"), 100);
}

void PaintBank(HDC hdc, HGDIOBJ obj, HGDIOBJ objdef, int x1, int y1, int x2, int y2)
{
    SelectObject(hdc, obj);
    Rectangle(hdc, x1, y1, x2, y2);
    SelectObject(hdc, objdef);
}

void PaintBuySell(HDC hdc, HGDIOBJ obj, HGDIOBJ objdef, int x1, int y1, int x2, int y2)
{
    SelectObject(hdc, obj);
    Rectangle(hdc, x1, y1, x2, y2);
    SelectObject(hdc, objdef);
}

void PaintPrison(HDC hdc, HGDIOBJ obj, HGDIOBJ objdef, int x1, int y1, int x2, int y2)
{
    SelectObject(hdc, obj);
    Rectangle(hdc, x1, y1, x2, y2);
    SelectObject(hdc, objdef);
}

void PaintIncident(HDC hdc, HGDIOBJ obj, HGDIOBJ objdef, int x1, int y1, int x2, int y2)
{
    SelectObject(hdc, obj);
    Rectangle(hdc, x1, y1, x2, y2);
    SelectObject(hdc, objdef);
}

HGDIOBJ obj = CreateSolidBrush(RGB(210, 10, 200));
HGDIOBJ tobj = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"");

void Paint(HDC hdc, WPARAM wParam, LPARAM lParam) 
{
    HGDIOBJ objdef = CreateSolidBrush(RGB(132, 45, 200));
    POINT point;
    
    for (size_t i = 0; i < 13; i++)
    {
        point.x = 100 + i * 100;
        point.y = 100 + i * 100;
        PaintStart(hdc, &obj, &tobj, point, 80);
        
    }
    //HGDIOBJ* obj = (HGDIOBJ*)malloc(sizeof(HGDIOBJ));
    //objdef = &CreateSolidBrush(RGB(132, 45, 200));
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
