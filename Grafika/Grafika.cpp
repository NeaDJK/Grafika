// Grafika.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Grafika.h"
#include "Class.h"
#include "Const.h"
#include <fstream>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int count_of_players = 2;                       //кол-во игроков
int size_of_field = 32;                         //размер игрового поля (Кратно четырем!!!) 
cell* field;                                    //поле
type_cell type_field[count_of_types_cells];     //типы клеток поля
player players[max_players];                    //игроки
credit cr[count_of_credit_plans];
int cube;                                       //результат броска кубика
int current_position;
int current_player = -1;
HGDIOBJ colorPlayer[max_players];

HWND hWnd;
HWND info_dialog;
WCHAR info_buffer[size_of_buffer];

int count_of_res;
int count_of_start;
int count_of_prisons;
int count_of_banks;
int count_of_incidents;
int count_of_rests;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                Init(); // определение начальных условий поля

int Transform(int n, POINT* p)
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

void ToLPWSTR(int num, LPWSTR* njn)
{


}

void Paint(HDC hdc, WPARAM wParam, LPARAM lParam)
{
	POINT point;

	point.x = 0;
	point.y = 0;

	/*LPWSTR njn;
	LPWSTR prn;
	WCHAR wch[100];
	njn = LPWSTR("");
	prn = new WCHAR[100];
	wsprintf(prn, L"%d", 25);
	//ToLPWSTR(25, &njn);
	wsprintf(wch, L"%d", 25);
	njn = LPWSTR(wch);

	TextOut(hdc, 500, 500, prn, 5);*/

	WCHAR price[size_of_price];

	for (int i = 0; i < size_of_field; i++)
	{
		Transform(field[i].get_number(), &point);
		point.x = point.x * scale + indent;
		point.y = point.y * scale + indent;

		swprintf(price, size_of_price, L"%8.2f", field[i].get_price());

		/*LPWSTR prn;
		WCHAR wch[100];
		wsprintf(wch, L"%d %d %d", point.x, point.y, field[i].get_number());
		prn = (LPWSTR)wch;

		TextOut(hdc, 100, 100 + i * 50, prn, wcslen(prn));*/


		switch (field[i].get_type_cell())
		{
		case type_start:
			PaintStart(hdc, &colorStart, &tobj, point, scale);
			break;
		case type_bank:
			PaintBank(hdc, &colorBank, &tobj, point, scale);
			break;
		case type_prison:
			PaintPrison(hdc, &colorPrison, &tobj, point, scale);
			break;
		case type_incident:
			PaintIncident(hdc, &colorIncident, &tobj, point, scale);
			break;
		case type_rest:
			PaintRest(hdc, &colorRest, &tobj, point, scale);
			break;
		case type_gold:
			PaintBuySell(hdc, &colorGold, &tobj, point, scale, L"Золото", name_gold, &price[0]);
			break;
		case type_iron:
			PaintBuySell(hdc, &colorIron, &tobj, point, scale, L"Железо", name_iron, &price[0]);
			break;
		case type_copper:
			PaintBuySell(hdc, &colorCopper, &tobj, point, scale, L"Медь", name_copper, &price[0]);
			break;
		case type_gas:
			PaintBuySell(hdc, &colorGas, &tobj, point, scale, L"Газ", name_gas, &price[0]);
			break;
		case type_coal:
			SetTextColor(hdc, RGB(255, 255, 255));
			PaintBuySell(hdc, &colorCoal, &tobj, point, scale, L"Уголь", name_coal, &price[0]);
			break;
		case type_oil:
			SetTextColor(hdc, RGB(255, 255, 255));
			PaintBuySell(hdc, &colorOil, &tobj, point, scale, L"Нефть", name_oil, &price[0]);
			break;
		case type_salt:
			PaintBuySell(hdc, &colorSalt, &tobj, point, scale, L"Соль", name_salt, &price[0]);
			break;
		default:
			break;
		}

		SetTextColor(hdc, RGB(0, 0, 0));
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
	field = new (cell[size_of_field]);
	Init();

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GRAFIKA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
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

	return (int)msg.wParam;
}

void InitField()
{
	count_of_res = int(size_of_field * 0.7) / 7;
	count_of_start = 1;
	count_of_prisons = int(size_of_field * 0.09);
	count_of_banks = int(size_of_field * 0.09);
	count_of_incidents = int(size_of_field * 0.09);
	count_of_rests = size_of_field - count_of_res - count_of_start - count_of_prisons - count_of_banks - count_of_incidents;
	type_field[0].set_values(type_start, count_of_start, &name_start[0]);
	type_field[1].set_values(type_bank, count_of_banks, &name_bank[0]);
	type_field[2].set_values(type_rest, count_of_rests, &name_rest[0]);
	type_field[3].set_values(type_prison, count_of_prisons, &name_prison[0]);
	type_field[4].set_values(type_gold, count_of_res, &name_gold[0]);
	type_field[5].set_values(type_iron, count_of_res, &name_iron[0]);
	type_field[6].set_values(type_copper, count_of_res, &name_copper[0]);
	type_field[7].set_values(type_incident, count_of_incidents, &name_incident[0]);
	type_field[8].set_values(type_coal, count_of_res, &name_coal[0]);
	type_field[9].set_values(type_oil, count_of_res, &name_oil[0]);
	type_field[10].set_values(type_salt, count_of_res, &name_salt[0]);
	type_field[11].set_values(type_gas, count_of_res, &name_gas[0]);
}

int GetTypeField(TCHAR str[100])
{
	for (int i = 0; i < count_of_types_cells; i++)
	{
		if (_tcscmp(type_field[i].name, str) == 0)
		{
			return type_field[i].number;
		}
	}

	return -1;
}

void Init() // определение начальных условий поля
{
	InitField();
	type_cell temp[count_of_types_cells];
	for (size_t i = 0; i < count_of_types_cells; i++)
	{
		temp[i] = (type_field[i]);
	}

	field[0].set_type_cell(type_start);
	field[0].set_number(0);
	temp[0].count = 0;

	std::wfstream fin;
	int file_num;
	WCHAR file_str[100];
	std::wstring file_name;
	std::wstring file_dscp;

	int count;

	fin.open("fuel.dat", std::ios::in);

	if (fin.is_open())
	{				
		fin >> count;
	}

	for (int j = 1; j < size_of_field; j++)
	{
		int flag = 1;

		while (flag)
		{
			int rc = rand() % (count_of_types_cells);

			if (temp[rc].count > 0)
			{
				field[j].set_type_cell(temp[rc].number);
				field[j].set_number(j);

				if (fin.is_open())
				{
					/*fin >> file_num;
					fin.getline(&file_str[0]);
					fin >> file_name;
					fin >> file_dscp;*/
				}

				temp[rc].count--;

				flag = 0;
			}
		}

		/*while (temp)
		{
			int r = rand() % size_of_field;

			if (r < count_of_res)
			{
				field[j].set_type_cell(type_not_bought);
			}
		}*/

	}

	colorPlayer[0] = colorPlayer0;
	colorPlayer[1] = colorPlayer1;
	colorPlayer[2] = colorPlayer2;
	colorPlayer[3] = colorPlayer3;
	colorPlayer[4] = colorPlayer4;


	for (int i = 0; i < count_of_players; i++)
	{
		players[i].color = colorPlayer[i];
	}

	if (fin.is_open())
	{
		fin.close();
	}
}

//void PrintCellInfo(cell* cl)
//{
//	swprintf(&info_buffer[0], size_of_buffer, L"Название: %s \nОписание: %s \nЦена: %8.2f \nНалог: %8.2f \nТип клетки: %d \nНомер клетки: %d \nВладелец: %d \n",
//		(cl->get_name()).c_str(), (cl->get_discription()).c_str(), cl->get_price(), cl->get_tax(), cl->get_type_cell(), cl->get_number(), cl->get_owner());
//}
//
//void PrintPlayerInfo(player* pl)
//{
//	swprintf(&info_buffer[0], size_of_buffer, L"Имя пользователя: %s \nБаланс: %8.2f \nПозиция: %d \nВо владении: %d \n",
//		(pl->get_name()).c_str(), pl->get_money(), pl->get_position(), pl->get_own_size());
//	
//	/*for (int i = 0; i < pl->get_own_size(); i++)
//	{
//		std::cout << "Владение номер " << i + 1 << ": " <<  << std::endl;
//
//	}*/
//
//	if (pl->debt.get_sum() == 0)
//	{
//		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, L"Кредитов нет. \n");
//	}
//
//	else
//	{
//		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, L"\nИнформация по кредиту: \n");
//		pl->debt.info_credit();
//		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, pl->debt.buffer);
//	}
//}

void Step(cell* cl)
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

	switch (field[current_position].is_bought())
	{
	case type_bought:
		if (field[current_position].get_owner() != current_player)
		{
			players[current_player].subtract_money(field[current_position].get_tax());
			players[field[current_position].get_owner()].add_money(field[current_position].get_tax());
			//std::cout << "Перевод: " << field[current_position].get_tax() << " рублей игроку " << field[current_position].get_owner() << std::endl;
			swprintf(&info_buffer[0], size_of_buffer, L"Перевод: %8.2f  рублей игроку %d", field[current_position].get_tax(), field[current_position].get_owner());
		}
		break;
	default:
		break;
	}

	swprintf(&info_buffer[0], size_of_buffer, L"%d игрок перемещается на %d клеток \nБаланс: % 8.2f \nПозиция : % d \n", current_player, cube, players[current_player].get_money(), players[current_player].get_position());

	if (players[current_player].debt.get_sum() == 0)
	{
		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, L"Кредитов нет. \n");
	}

	else
	{
		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, L"\nИнформация по кредиту: \n");
		players[current_player].debt.info_credit();
		swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, players[current_player].debt.buffer);
	}

	swprintf(&info_buffer[_tcslen(info_buffer)], size_of_buffer, L"\nНазвание: %s \nОписание: %s \nЦена: %8.2f \nНалог: %8.2f \nТип клетки: %d \nНомер клетки: %d \nВладелец: %d \n",
		(cl->get_name()).c_str(), (cl->get_discription()).c_str(), cl->get_price(), cl->get_tax(), cl->get_type_cell(), cl->get_number(), cl->get_owner());
}

void Buy()
{
	if (field[current_position].is_bought() == type_not_bought)
	{
		if (players[current_player].add_ownship(field[current_position].get_number(), field[current_position].get_price()) == 0)
		{
			field[current_position].set_bought(type_bought);
			//std::cout << "Продано!" << std::endl;
			swprintf(&info_buffer[0], size_of_buffer, L"Продано!");
		}

		else
		{
			//std::cout << "Не хватает средств!" << std::endl;
			swprintf(&info_buffer[0], size_of_buffer, L"Не хватает средств!");
		}
	}
	else
	{
		//std::cout << "Клетка не продается!" << std::endl;
		swprintf(&info_buffer[0], size_of_buffer, L"Клетка не продается!");
	}
}

void PrintCreditPlans() 
{
	//if (field[players[current_player].get_position()].get_type_cell() == type_bank)
	{
		if (players[current_player].debt.get_sum() == 0)
		{
			//std::cout << "Выберите схему кредита:" << std::endl;
			swprintf(&info_buffer[0], size_of_buffer, L"Выберите схему кредита: \n");

			for (int i = 0; i < count_of_credit_plans; i++)
			{
				cr[i].new_credit();
				
				cr[i].info_credit(i + 1);
				swprintf(&info_buffer[_tcslen(&info_buffer[0])], size_of_buffer, L"%s \n", cr[i].buffer);
			}
		}

		else
		{
			//std::cout << "С тебя хватит" << std::endl;
			swprintf(&info_buffer[0], size_of_buffer, L"Больше одного кредита нельзя!");
		}
			
	}

	//else
		//swprintf(&info_buffer[0], size_of_buffer, L"Здесь кредит не выдают!");
}

void GetCredit(int value)
{
	//if (field[players[current_player].get_position()].get_type_cell() == type_bank)
	{
		if (players[current_player].debt.get_sum() == 0)
		{
			/*std::cout << "Выберите схему кредита:" << std::endl;

			credit cr[count_of_credit_plans];


			for (int i = 0; i < count_of_credit_plans; i++)
			{
				cr[i].new_credit();
				cr[i].info_credit(i + 1);
			}*/

			players[current_player].add_money(cr[value - 1].get_sum());
			players[current_player].debt = cr[value - 1];

			swprintf(&info_buffer[0], size_of_buffer, L"Кредит %d выдан!", value);

			/*char input[100]; std::cin >> input;

			int value = atoi(input);

			if (value <= count_of_credit_plans and value > 0)
			{
				players[current_player].add_money(cr[value - 1].get_sum());
				players[current_player].debt = cr[value - 1];
			}

			else
				std::cout << "Некорректный ввод!" << std::endl;*/
		}

		//else
		//	//std::cout << "С тебя хватит" << std::endl;		
	}

	/*else
		std::cout << "Денег нет, но вы держитесь..." << std::endl;*/
}

void Rules(int rl_id)
{
	switch (rl_id)
	{
	case rule_step_id:
		swprintf(&info_buffer[0], size_of_buffer, L"Ход - основное действие в игре. Для того, чтобы передать ход следующему игроку, нажмите кнопку 'Бросок'. После этого выпадет случайное число от 2 до 12 и фишка игрока переместится на указанное количество клеток. Также ниже выведется вся информация об игроке и клетке, на которой он находится. \n");
		break;
	default:
		break;
	}
}

void Education(int ed_id) 
{
	switch (ed_id)
	{
	case educ_cr_id:
		swprintf(&info_buffer[0], size_of_buffer, L"Кредит — это предоставление денежных средств или иных ресурсов кредитором заёмщику во временное пользование. \n \nЧтобы взять кредит, нажмите кнопку 'Кредит', находясь на клетке банка. Далее выберите с помощью соответсующих кнопок интересующую Вас схему кредита. Кредит постепенно выплачивается автоматически, при прохождении через клетку 'Старт'.");
		break;
	case educ_infl_id:
		swprintf(&info_buffer[0], size_of_buffer, L"Инфляция — это темп устойчивого повышения общего уровня цен на товары и услуги за определённый промежуток времени, а также степень обесценивания денег. \n");
		break;
	default:
		break;
	}
	
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAFIKA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GRAFIKA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, scale * (size_of_field / 4 + 1) + indent * 2 + 15, scale * (size_of_field / 4 + 1) + indent * 2 + 50, nullptr, nullptr, hInstance, nullptr);
		
	info_dialog = CreateWindowW(L"static", &info_buffer[0], WS_VISIBLE | WS_CHILD, indent + scale * 2, indent + scale * 2, scale * (size_of_field / 4 - 3), scale * (size_of_field / 4 - 4), hWnd, (HMENU)(2001 + 1), hInstance, NULL);
	HWND info_button[10];
	info_button[0] = CreateWindowW(L"button", L"Бросок", WS_VISIBLE | WS_CHILD, indent * 2.5 + scale * 2, indent + scale * 7.5, 100, 30, hWnd, (HMENU)(1001 + 1), hInstance, NULL);
	info_button[1] = CreateWindowW(L"button", L"Кредит", WS_VISIBLE | WS_CHILD, indent + scale * 4, indent + scale * 7.5, 100, 30, hWnd, (HMENU)(1001 + 2), hInstance, NULL);
	info_button[2] = CreateWindowW(L"button", L"Купить", WS_VISIBLE | WS_CHILD, indent * 3 + scale * 5, indent + scale * 7.5, 100, 30, hWnd, (HMENU)(1001 + 3), hInstance, NULL);
	info_button[3] = CreateWindowW(L"button", L"Продать (?)", WS_VISIBLE | WS_CHILD, indent + scale * 4, indent + scale * 6.5, 100, 30, hWnd, (HMENU)(1001 + 4), hInstance, NULL);
	//info_button[4] = CreateWindowW(L"button", L"Инфо", WS_VISIBLE | WS_CHILD, indent + scale * 3, indent + scale * 7, 100, 30, hWnd, (HMENU)(1001 + 5), hInstance, NULL);
	//info_button[5] = CreateWindowW(L"button", L"Игрок", WS_VISIBLE | WS_CHILD, indent + scale * 5, indent + scale * 7, 100, 30, hWnd, (HMENU)(1001 + 6), hInstance, NULL);
		
	HWND credit_button[5];
	credit_button[0] = CreateWindowW(L"button", L"1", WS_VISIBLE | WS_CHILD, indent + scale * 2, indent + scale * 1.5, scale, scale / 3, hWnd, (HMENU)(3001 + 1), hInstance, NULL);
	credit_button[1] = CreateWindowW(L"button", L"2", WS_VISIBLE | WS_CHILD, indent + scale * 3, indent + scale * 1.5, scale, scale / 3, hWnd, (HMENU)(3001 + 2), hInstance, NULL);
	credit_button[2] = CreateWindowW(L"button", L"3", WS_VISIBLE | WS_CHILD, indent + scale * 4, indent + scale * 1.5, scale, scale / 3, hWnd, (HMENU)(3001 + 3), hInstance, NULL);
	credit_button[3] = CreateWindowW(L"button", L"4", WS_VISIBLE | WS_CHILD, indent + scale * 5, indent + scale * 1.5, scale, scale / 3, hWnd, (HMENU)(3001 + 4), hInstance, NULL);
	credit_button[4] = CreateWindowW(L"button", L"5", WS_VISIBLE | WS_CHILD, indent + scale * 6, indent + scale * 1.5, scale, scale / 3, hWnd, (HMENU)(3001 + 5), hInstance, NULL);

	HWND education_button[10];
	education_button[0] = CreateWindowW(L"button", L"Кредит", WS_VISIBLE | WS_CHILD, indent + scale, indent + scale * 2, scale, scale / 3, hWnd, (HMENU)(4001 + 1), hInstance, NULL);
	education_button[1] = CreateWindowW(L"button", L"Инфляция", WS_VISIBLE | WS_CHILD, indent + scale, indent + scale * 2.5, scale, scale / 3, hWnd, (HMENU)(4001 + 2), hInstance, NULL);
	
	HWND rule_button[10];
	rule_button[0] = CreateWindowW(L"button", L"Ход", WS_VISIBLE | WS_CHILD, indent + scale * 7, indent + scale * 2, scale, scale / 3, hWnd, (HMENU)(5001 + 1), hInstance, NULL);

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
		auto type = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 1001 + 1:
			Step(&field[0]);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			InvalidateRect(hWnd, NULL, false);
			break;
		case 1001 + 2:
			PrintCreditPlans();
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 1001 + 3:
			Buy();
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 1001 + 5:
			//PrintCellInfo(&field[0]);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 1001 + 6:
			//PrintPlayerInfo(&players[0]);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 3001 + 1:
			GetCredit(1);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 3001 + 2:
			GetCredit(2);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 3001 + 3:
			GetCredit(3);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 3001 + 4:
			GetCredit(4);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 3001 + 5:
			GetCredit(5);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 4001 + 1:
			Education(educ_cr_id);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 4001 + 2:
			Education(educ_infl_id);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case 5001 + 1:
			Rules(rule_step_id);
			SetWindowTextW(info_dialog, &info_buffer[0]);
			break;
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			Step(&field[0]);
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
		SetBkMode(hdc, TRANSPARENT);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		Paint(hdc, wParam, lParam);
		//PaintInfo();
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		default:
			break;
		}
		break;
	}
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
