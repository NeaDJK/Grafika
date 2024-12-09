// Grafika.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Grafika.h"
#include "Class.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int count_of_players = 5;                       //кол-во игроков
cell field[size_of_field];                      //поле
player players[max_players];                    //игроки
int cube;                                       //результат броска кубика
int current_position;
int current_player = -1;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                Init(); // определение начальных условий поля

int Transform(int n, POINT *p) 
{
    if (n < size_of_field / 4)
    {
        p->x = n;
        p->y = 0;

        return 0;
    }

    if (n < size_of_field / 2)
    {
        p->x = size_of_field / 4;
        p->y = n % (size_of_field / 4);

        return 0;
    }

    if (n < size_of_field / 4 * 3)
    {
        p->x = size_of_field / 4 - (n % (size_of_field / 4));
        p->y = size_of_field / 4;

        return 0;
    }

    if (n < size_of_field)
    {
        p->x = 0;
        p->y = size_of_field / 4 - (n % (size_of_field / 4));

        return 0;
    }
}



void Paint(HDC hdc, WPARAM wParam, LPARAM lParam)
{
    POINT point;

    point.x = 0;
    point.y = 0;

    
      
    for (int i = 0; i < size_of_field; i++)
    {
        Transform(field[i].get_number(), &point);
        point.x = point.x * scale + indent;
        point.y = point.y * scale + indent;

        /*LPWSTR prn;
        WCHAR wch[100];
        wsprintf(wch, L"%d %d %d", point.x, point.y, field[i].get_number());
        prn = (LPWSTR)wch;

        TextOut(hdc, 100, 100 + i * 50, prn, wcslen(prn));*/

        PaintStart(hdc, &colorStart, &tobj, point, scale);

        switch (field[i].get_type_cell())
        {
        case 0:
            PaintStart(hdc, &colorStart, &tobj, point, scale);
            break;
        case 1:
            PaintBank(hdc, &colorBank, &tobj, point, scale);
            break;
        case 2:
            PaintBuySell(hdc, &colorGold, &tobj, point, scale, L"Золото");
            break;
        case 3:
            PaintBuySell(hdc, &colorIron, &tobj, point, scale, L"Железо");
            break;
        case 4:
            PaintBuySell(hdc, &colorCopper, &tobj, point, scale, L"Медь");
            break;
        case 5:
            PaintIncident(hdc, &colorIncident, &tobj, point, scale);
            break;
        case 6:
            PaintBuySell(hdc, &colorFuel, &tobj, point, scale, L"Газ");
            break;
        case 7:
            PaintBuySell(hdc, &colorFuel, &tobj, point, scale, L"Уголь");
            break;
        case 8:
            PaintBuySell(hdc, &colorFuel, &tobj, point, scale, L"Нефть");
            break;
        case 9:
            PaintRest(hdc, &colorRest, &tobj, point, scale);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < count_of_players; i++)
    {
        Transform(players[i].get_position(), &point);
        point.x = point.x * scale + indent + scale * i / count_of_players;
        point.y = point.y * scale + indent;

        PaintPlayer(hdc, &(players[i].color), &tobj, point, scale / count_of_players, i);
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
    Init();

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

void Init() // определение начальных условий поля
{
    for (int j = 0; j < size_of_field; j++)
    {
        field[j].set_type_cell(rand() % 10);
        field[j].set_number(j);
    }

    /*players[1].color = colorPlayer1;
    players[2].color = colorPlayer2;
    players[3].color = colorPlayer3;
    players[4].color = colorPlayer4;*/ //пройтись forом
}

void Step() 
{
    current_player = (current_player + 1) % (count_of_players);
    cube = rand() % 12 + 1;
    //std::cout << cube << std::endl;

    current_position = (players[current_player].get_position() + cube);

    if (current_position >= size_of_field)
    {
        players[current_player].debt.add_current_circle();
        players[current_player].debt.end_credit();
        players[current_player].add_money(money_for_circle);
        players[current_player].subtract_money(players[current_player].debt.current_payment_for_circle());
    }

    current_position = current_position % (size_of_field);
    players[current_player].set_position(current_position);

    switch (field[current_position].get_type_cell())
    {
    case type_bought:
        if (field[current_position].get_owner() != current_player)
        {
            players[current_player].subtract_money(field[current_position].get_tax());
            players[field[current_position].get_owner()].add_money(field[current_position].get_tax());
            std::cout << "Перевод: " << field[current_position].get_tax() << " рублей игроку " << field[current_position].get_owner() << std::endl;
        }
        break;
    default:
        break;
    }
}

void Buy() 
{
    if (field[current_position].get_type_cell() == type_not_bought)
    {
        if (players[current_player].add_ownship(field[current_position].get_number(), field[current_position].get_price()) == 0)
        {
            field[current_position].set_type_cell(type_bought);
            std::cout << "Продано!" << std::endl;
        }

        else
            std::cout << "Не хватает средств!" << std::endl;
    }
    else
        std::cout << "Клетка не продается!" << std::endl;
}

void GetCredit() 
{
    if (field[players[current_player].get_position()].get_type_cell() == type_bank)
    {
        if (players[current_player].debt.get_sum() == 0)
        {
            std::cout << "Выберите схему кредита:" << std::endl;

            credit cr[count_of_credit_plans];


            for (int i = 0; i < count_of_credit_plans; i++)
            {
                cr[i].new_credit();
                cr[i].info_credit(i + 1);
            }

            char input[100]; std::cin >> input;

            int value = atoi(input);

            if (value <= count_of_credit_plans and value > 0)
            {
                players[current_player].add_money(cr[value - 1].get_sum());
                players[current_player].debt = cr[value - 1];
            }

            else
                std::cout << "Некорректный ввод!" << std::endl;
        }

        else
            std::cout << "С тебя хватит" << std::endl;
    }

    else
        std::cout << "Денег нет, но вы держитесь..." << std::endl;
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
      CW_USEDEFAULT, 0, scale * (size_of_field / 4 + 1) + indent * 2 + 15, scale * (size_of_field / 4 + 1) + indent * 2 + 50, nullptr, nullptr, hInstance, nullptr);

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
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                Step();
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
