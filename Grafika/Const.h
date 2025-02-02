#pragma once


//const int count_of_fields = 5; //кол-во клеток в одном ряду
const int size_of_input = 10; //размер вводимых команд
const int max_players = 5; //максимальное кол-во игроков
const int count_of_credit_plans = 5; //кол-во вариантов схем кредитов
const int money_for_circle = 200; //деньги за круг
const int def_arrest_time = 3;

const int size_of_price = 100;
const int size_of_buffer = 10000;
const int size_of_wchar = 10000;

/*const char string_exit[] = "exit"; //команда выхода из программы
const char step[] = "cube"; //команда броска кубика
const char info[] = "info"; //команда вывода всей информации о клетке
const char user[] = "user"; //команда выводы информации о пользователе
const char buy[] = "buy"; //команда для покупки клетки
const char get_credit[] = "credit"; //команда для получения кредита*/

/*const int type_bank = 4; //клетка банка
const int type_prison = 3; //клетка тюрьмы
const int type_not_prison = 2; //клетка выхода из тюрьмы
*/

const int type_bought = 1; //купленная клетка
const int type_not_bought = 0; //не купленная клетка
const int type_cannot_bought = -1; //не продается

const int count_of_types_cells = 12;
const int count_of_types_res = 7;
const int type_start = 0;  
const int type_bank = 1;
const int type_rest = 2;
const int type_prison = 3;
const int type_incident = 4;
const int type_gold = 100;   
const int type_iron = 101;    
const int type_copper = 102;   
const int type_gas = 103;   
const int type_coal = 104;    
const int type_oil = 105; 
const int type_salt = 106;

const WCHAR name_start[] = L"Старт";
const WCHAR name_bank[] = L"Банк";
const WCHAR name_rest[] = L"Отдых";
const WCHAR name_prison[] = L"Тюрьма";
const WCHAR name_gold[] = L"Драгоценные металлы";
const WCHAR name_iron[] = L"Черные металлы";
const WCHAR name_copper[] = L"Цветные металлы";
const WCHAR name_incident[] = L"Шанс";
const WCHAR name_gas[] = L"Газ";
const WCHAR name_coal[] = L"Уголь";
const WCHAR name_oil[] = L"Нефть";
const WCHAR name_salt[] = L"Соль";


const int educ_cr_id = 1;
const int educ_infl_id = 2;


const int rule_step_id = 1;
const int rule_sb_id = 2;


const int chance_ext_id = 0;
const int chance_new_tecnology_id = 1;
const int chance_add_money_id = 2;
const int chance_fine_id = 3;
const int chance_rand_move_id = 4;
const int chance_defl_id = 5;
const int chance_sanctions_id = 6;
