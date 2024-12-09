//{{NO_DEPENDENCIES}}
// Включаемый файл, созданный в Microsoft Visual C++.
// Используется Grafika.rc

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_GRAFIKA_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_GRAFIKA			107
#define IDI_SMALL				108
#define IDC_GRAFIKA			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif
// Следующие стандартные значения для новых объектов
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif



const int size_of_field = 32; //размер игрового поля (% 4 == 0)
const int count_of_fields = 5; //кол-во клеток в одном ряду
const int size_of_input = 10; //размер вводимых команд
const int max_players = 4; //максимальное кол-во игроков
const int count_of_credit_plans = 5; //кол-во вариантов схем кредитов
const int money_for_circle = 200; //деньги за круг

const char string_exit[] = "exit"; //команда выхода из программы
const char step[] = "cube"; //команда броска кубика
const char info[] = "info"; //команда вывода всей информации о клетке
const char user[] = "user"; //команда выводы информации о пользователе
const char buy[] = "buy"; //команда для покупки клетки
const char get_credit[] = "credit"; //команда для получения кредита

const int type_bank = 4; //клетка банка
const int type_prison = 3; //клетка тюрьмы
const int type_not_prison = 2; //клетка выхода из тюрьмы
const int type_bought = 1; //купленная клетка
const int type_not_bought = 0; //не купленная клетка

LPWSTR ToLPWSTR(int num)
{
    LPWSTR prn;
    WCHAR wch[100];
    wsprintf(wch, L"%d", num);
    prn = (LPWSTR)wch;
    return prn;
}