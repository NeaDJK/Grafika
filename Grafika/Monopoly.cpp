#include <iostream>
#include <string>

class cell
{
private:
    int number; //порядковый номер поля
    std::string name; //название
    std::string discription; //описание клетки
    double price; //цена
    double tax; //налог 
    int type_cell; //тип клетки
    int owner; //владелец

public:
    //конструктор
    cell() 
    {
        number = 1;
        name = "Китай-Город";
        discription = "станция метро";
        price = 100;
        tax = 10;
        type_cell = 0;
        owner = 1;
    }

    //функция присвоения данных
    void set(int num, std::string nm, std::string disc, double prc, double tx, int tpc, int own) 
    {
        number = num;
        name = nm;
        discription = disc;
        price = prc;
        tax = tx;
        type_cell = tpc;
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
    
    void set_owner(int own)
    {
        owner = own;
    }

    //функция для добавления описания
    void set_discription(std::string disc)
    {
        discription = disc;
    }

    //функции получения данных
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

    //метод вывода всей информации
    void print_info()
    {
        std::cout << "Название: " << name << std::endl;
        std::cout << "Описание: " << discription << std::endl;
        std::cout << "Цена: " << price << std::endl;
        std::cout << "Налог: " << tax << std::endl;
        std::cout << "Тип клетки: " << type_cell << std::endl;
        std::cout << "Номер клетки: " << number << std::endl;

    }

    //~cell();
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
        if (sum == 0) {
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
            std::cout << "Схема номер " << num << std::endl;
        }

        if (type_of_credit == 0)
        {
            std::cout << "Форма платежа - " << "аннуитетная" << std::endl;

        }
        else
        {
            std::cout << "Форма платежа - " << "дифференцированная" << std::endl;
        }

        std::cout << "Сумма - " << sum << std::endl << \
            "Срок кредита - " << count_of_steps << std::endl << \
            "Процент - " << percent << std::endl;

        if (type_of_credit == 0)
        {
            std::cout << "Платеж - " << payment << std::endl;
        }
        else
        {
            std::cout << "Первый платеж - " << payment << std::endl;
            current_payment(count_of_steps);
            std::cout << "Последний платеж - " << payment << std::endl;
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
    credit debt;

    player()
    {
        name = "Player";
        money = 200;
        own_size = 0;
        position = 0;
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
        std::cout << "Имя пользователя: " << name << std::endl;
        std::cout << "Баланс: " << money << std::endl;
        std::cout << "Позиция: " << position << std::endl;
        std::cout << "Во владении: " << own_size << std::endl;

        for (int i = 0; i < own_size; i++)
        {
            std::cout << "Владение номер " << i + 1 << ": " << own[i] << std::endl;
        }
    }
};

const int size_of_field = 20; //размер игрового поля
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

//int current_pos = 0; //текущая позиция
int count_of_players = 2; //кол-во игроков
cell field[size_of_field]; //поле
player players[max_players]; //игроки

void print_field() //вывод поля
{
    //system("cls");

    int pl; //кол-во раз когда встретили пользователя

    
    for (int j = 0; j < size_of_field; j++)
    {
        pl = 0;

        for (int k = 0; k < count_of_players; k++)
        {
            if (players[k].get_position() == field[j].get_number())
            {
                pl++;
            }
        }

        if (pl > 0)
        {
            std::cout << pl;
        }

        else
        {
            switch (field[j].get_type_cell())
            {
            case type_not_bought:
                std::cout << 'N';
                break;
            case type_bought:
                std::cout << 'Y';
                break;
            case type_bank:
                std::cout << 'B';
                break;
            case type_prison:
                std::cout << 'P';
                break;
            default:
                std::cout << 'x';
                break;
            }
        }

        if (j % count_of_fields == (count_of_fields - 1))
        {
            std::cout << '\n';
        }
    }
}



int main()
{
    setlocale(LC_CTYPE, "rus");

    char input[size_of_input]; //вводимая команда
    int cube; //результат броска кубика
    int current_position;
    int current_player = -1;

    strcpy_s(input, 5, "cube");

    /*std::cout << input << std::endl;
    std::cout << strcmp(input, string_exit);*/

    
    for (int j = 0; j < size_of_field; j++)
    {
        field[j].set_type_cell(rand() % 5);
        field[j].set_number(j);
    }
    

    //field[current_x][current_y].set_type_cell(char(1));

    while (strcmp(input, string_exit) != 0) //условие выхода
    {
        if (strcmp(input, step) == 0) //ход
        {
            current_player = (current_player + 1) % (count_of_players);
            cube = rand() % 12 + 1;
            std::cout << cube << std::endl;

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
            print_field(); //вывод поля

            /*field[current_x][current_y].set_type_cell(char(0));

            //движение фишки
            if (current_y == 0)
                current_x += cube;
            else if (current_y == size_of_field - 1)
                current_x -= cube;
            else if (current_x == 0)
                current_y -= cube;
            else if (current_x == size_of_field - 1)
                current_y += cube;

            //проверка на выход с поля
            if (current_x >= size_of_field)
            {
                current_y = current_x - size_of_field + 1;
                current_x = size_of_field - 1;
            }

            if (current_x < 0)
            {
                current_y = size_of_field - 1 + current_x;
                current_x = 0;
            }

            if (current_y >= size_of_field)
            {
                current_x = size_of_field - 1 - (current_y - size_of_field + 1);
                current_y = size_of_field - 1;
            }

            if (current_y < 0)
            {
                current_x = - current_y;
                current_y = 0;
            }*/


            //field[current_x][current_y].set_type_cell(char(1));

            //if (field[current_x][current_y].)
        }

        if (strcmp(input, info) == 0) //вывод иформации о клетке
            field[current_position].print_info();

        if (strcmp(input, user) == 0) //вывод иформации о пользователе
            players[current_player].print_info();

        if (strcmp(input, buy) == 0) //покупка клетки
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

        if (strcmp(input, get_credit) == 0)
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

                    std::cin >> input;

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

        std::cin >> input;
    };

    /*for (int i = 0; i < 256; i++)
        std::cout << char(i);*/
}
