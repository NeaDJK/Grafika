#pragma once
#include <iostream>
class cell
{
private:
    int number; //���������� ����� ����
    std::string name; //��������
    std::string discription; //�������� ������
    double price; //����
    double tax; //����� 
    int type_cell; //��� ������
    int bought; // ���������/�� ���������/�������
    int owner; //��������
    

public:
    //�����������
    cell()
    {
        number = 1;
        name = "�����-�����";
        discription = "������� �����";
        price = 100;
        tax = 10;
        type_cell = 0;
        bought = 0;
        owner = 1;
    }

    //������� ���������� ������
    void set(int num, std::string nm, std::string disc, double prc, double tx, int tpc, int bg, int own)
    {
        number = num;
        name = nm;
        discription = disc;
        price = prc;
        tax = tx;
        type_cell = tpc;
        bought = bg;
        owner = own;
    }

    void set_number(int num)
    {
        number = num;
    }

    void set_bame(std::string nm)
    {
        name = nm;
    }

    void set_price(double prc)
    {
        price = prc;
    }

    void set_tax(double tx)
    {
        tax = tx;
    }

    void set_type_cell(char tpc)
    {
        type_cell = tpc;
    }

    void set_bought(int bg) 
    {
        bought = bg;
    }

    void set_owner(int own)
    {
        owner = own;
    }

    //������� ��� ���������� ��������
    void set_discription(std::string disc)
    {
        discription = disc;
    }

    //������� ��������� ������
    int get_number()
    {
        return number;
    }

    std::string get_name()
    {
        return name;
    }

    std::string get_discription()
    {
        return discription;
    }

    double get_price()
    {
        return price;
    }

    double get_tax()
    {
        return tax;
    }

    char get_type_cell()
    {
        return type_cell;
    }

    int get_owner()
    {
        return owner;
    }

    int is_bought()
    {
        return bought;
    }

    //����� ������ ���� ����������
    void print_info()
    {
        std::cout << "��������: " << name << std::endl;
        std::cout << "��������: " << discription << std::endl;
        std::cout << "����: " << price << std::endl;
        std::cout << "�����: " << tax << std::endl;
        std::cout << "��� ������: " << type_cell << std::endl;
        std::cout << "����� ������: " << number << std::endl;

    }

    //~cell();
};

class type_cell
{
public:
    int number; //�������� ���������
    int count; //���-�� ������
    TCHAR name[100]; //�������� ���� ������

    type_cell() {
        number = 0;
        count = 40;
        lstrcpyW(&name[0], L"�����");
    }

    void set_values(int num, int con, const TCHAR *nam)
    {
        number = num;
        count = con;
        lstrcpyW(&name[0], nam);
    }
};

class credit
{
private:
    int sum;
    int count_of_steps;
    int percent;
    double coef_percent;
    int type_of_credit;
    double payment;
    int current_circle;

public:
    credit()
    {
        sum = 0;
        count_of_steps = 0;
        percent = 0;
        coef_percent = 1;
        type_of_credit = 0;
        payment = 0;
        current_circle = 0;
    }

    void end_credit()
    {
        if (current_circle > count_of_steps)
        {
            credit();
        }
    }

    int get_sum()
    {
        return sum;
    }

    void new_credit(int s_min = 1000, int s_max = 10000, int n_min = 3, int n_max = 10, int p_min = 11, int p_max = 15)
    {
        sum = rand() % 9001 + 1000;
        count_of_steps = rand() % 8 + 3;
        percent = rand() % 11 + 5;
        coef_percent = 1 + percent / 100.;
        type_of_credit = rand() % 2;
        current_payment();
        current_circle = 0;
    }

    void current_payment(int i = 1)
    {
        if (sum == 0)
        {
            payment = 0;
        }
        else
        {
            if (type_of_credit == 0)
            {
                payment = sum * 1. * powf(coef_percent, count_of_steps) * (coef_percent - 1) / (powf(coef_percent, count_of_steps) - 1);

            }
            else
            {
                if ((i <= count_of_steps) and (i > 0))
                {
                    payment = sum * 1. / count_of_steps * (coef_percent * (count_of_steps - i + 1) - (count_of_steps - i));
                }
                else
                    payment = -1;
            }
        }
    }

    double current_payment_for_circle()
    {
        current_payment(current_circle);
        return payment;
    }

    void info_credit(int num = -1)
    {
        if (num != -1)
        {
            std::cout << "����� ����� " << num << std::endl;
        }

        if (type_of_credit == 0)
        {
            std::cout << "����� ������� - " << "�����������" << std::endl;

        }
        else
        {
            std::cout << "����� ������� - " << "������������������" << std::endl;
        }

        std::cout << "����� - " << sum << std::endl << \
            "���� ������� - " << count_of_steps << std::endl << \
            "������� - " << percent << std::endl;

        if (type_of_credit == 0)
        {
            std::cout << "������ - " << payment << std::endl;
        }
        else
        {
            std::cout << "������ ������ - " << payment << std::endl;
            current_payment(count_of_steps);
            std::cout << "��������� ������ - " << payment << std::endl;
            current_payment();
        }

    }

    void add_current_circle(int count = 1)
    {
        current_circle += count;
    }

    void set_current_circle(int count)
    {
        current_circle = count;
    }

    int get_current_circle()
    {
        return current_circle;
    }
};

class player
{
private:
    std::string name;
    double money;
    int own[100];
    int own_size;
    int position;
     
    bool check_price(double price)
    {
        if (money >= price)
            return true;

        else
            return false;
    }

public:
    HGDIOBJ color;
    credit debt;

    player()
    {
        name = "Player";
        money = 200;
        own_size = 0;
        position = 0;
        color = CreateSolidBrush(RGB(255, 255, 255));
    }

    void set_name(std::string nm)
    {
        name = nm;
    }

    void set_money(double mn)
    {
        money = mn;
    }

    void set_position(int pos)
    {
        position = pos;
    }

    std::string get_name()
    {
        return name;
    }

    double get_money()
    {
        return money;
    }

    int get_position()
    {
        return position;
    }
        
    int get_own_size()
    {
        return own_size;
    }

    int add_ownship(int wn, double price)
    {
        if (check_price(price))
        {
            own_size++;
            own[own_size - 1] = position;
            money -= price;

            return 0;
        }

        else
            return -1;
    }

    void add_money(double mn)
    {
        money += mn;
    }

    void subtract_money(double mn)
    {
        money -= mn;
    }

    void print_info()
    {
        std::cout << "��� ������������: " << name << std::endl;
        std::cout << "������: " << money << std::endl;
        std::cout << "�������: " << position << std::endl;
        std::cout << "�� ��������: " << own_size << std::endl;

        for (int i = 0; i < own_size; i++)
        {
            std::cout << "�������� ����� " << i + 1 << ": " << own[i] << std::endl;
        }
    }
};

