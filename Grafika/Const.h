#pragma once


//const int count_of_fields = 5; //���-�� ������ � ����� ����
const int size_of_input = 10; //������ �������� ������
const int max_players = 5; //������������ ���-�� �������
const int count_of_credit_plans = 5; //���-�� ��������� ���� ��������
const int money_for_circle = 200; //������ �� ����

const int size_of_price = 100;
const int size_of_buffer = 10000;

/*const char string_exit[] = "exit"; //������� ������ �� ���������
const char step[] = "cube"; //������� ������ ������
const char info[] = "info"; //������� ������ ���� ���������� � ������
const char user[] = "user"; //������� ������ ���������� � ������������
const char buy[] = "buy"; //������� ��� ������� ������
const char get_credit[] = "credit"; //������� ��� ��������� �������*/

/*const int type_bank = 4; //������ �����
const int type_prison = 3; //������ ������
const int type_not_prison = 2; //������ ������ �� ������
*/

const int type_bought = 1; //��������� ������
const int type_not_bought = 0; //�� ��������� ������
const int type_cannot_bought = -1; //�� ���������

const int count_of_types_cells = 12;
const int type_start = 0;  
const int type_bank = 1;
const int type_rest = 2;
const int type_prison = 3;
const int type_gold = 100;   
const int type_iron = 101;    
const int type_copper = 102;   
const int type_incident = 103;   
const int type_gas = 104;   
const int type_coal = 105;    
const int type_oil = 106; 
const int type_salt = 107;

const TCHAR name_start[] = L"�����";
const TCHAR name_bank[] = L"����";
const TCHAR name_rest[] = L"�����";
const TCHAR name_prison[] = L"������";
const TCHAR name_gold[] = L"����������� �������";
const TCHAR name_iron[] = L"������ �������";
const TCHAR name_copper[] = L"������� �������";
const TCHAR name_incident[] = L"����";
const TCHAR name_gas[] = L"���";
const TCHAR name_coal[] = L"�����";
const TCHAR name_oil[] = L"�����";
const TCHAR name_salt[] = L"����";


const int educ_cr_id = 1;
const int educ_infl_id = 2;


const int rule_step_id = 1;
const int rule_sb_id = 2;
