#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int i;  // счетчик
int k;  // количество отелей
int j;  // счетчик
int kolvo_usl; // количество услуг
string vr_nazv; // переменная для сравнения название отеля
string vr_category; // переменная для сравнения категория номера
int kolvo_gost; // количество гостей
int counter[7]; // массив счетчиков для услуг
int countrr[7] = {0,0,0,0,0,0,0}; // массив счетчик количества номеров в отеле

struct hotels{
int id;                 //идентификатор гостиницы
int total_room[20];         //кол-во номеров определенного типа в гостинице
int free_room;          //кол-во свободных номеров определенного типа в гостинице
int price[20];              //цена номера
int r_number[20];       //номер комнаты
string name;            //название гостиницы
string h_category;      //категория отеля
string r_category[20];      //категория номера
string usluga[10];         // услуги, оказываемые отелем
}hotel[20];

struct gosty{
string fio;         // фио гостя
string arrival;     // дата заезда
string departure;   // дата выезда
string extra_serv;  // выбранные доп услуги
int gr_number;      // выбранный гостем номер
int kolvo;          // количество мест
}gost[100];



void menu()
{
    cout << "Главное меню\n";  // вывод главного меню
    cout << "----------------\n";
    cout << "Сведения о гостиницах (1)\n";
    cout << "Сведения о гостях (2)\n";
    cout << "Забронировать номер (3)\n";
    cout << "Номер с минимальной ценой (4)\n";
    cout << "Вывод номеров определенного типа (5)\n";
    cout << "Завершение программы (0)\n";
}


void baza_hotel()
{
    cout << "\nСписок гостиниц \n";       // вывод списка гостиниц
    cout << "------------------\n";
    cout << "Название\t" << "Категория\n";
    for(int i = 0; i < k; i++)
    {
        if(hotel[i].name != hotel[i+1].name)
        {
            cout << hotel[i].name << '\t' << '\t' << hotel[i].h_category << endl;
        }
    }
    cout << "\nВведите название гостиницы, чтобы получить более подробные сведения о ней\n";
    cin >> vr_nazv;
    cout << "Тип номера\t" << "Цена\t" << "Количество номеров\t" << endl;   // вывод списка номеров, в выбранной гостинице
    int l;
    for(i = 0; i < k; i++)
    {
        if(vr_nazv == hotel[i].name)
        {
                l = i;
                for(int j = 0; j < countrr[l]; j++)
                {
                    cout << hotel[l].r_category[j] << "\t" << hotel[l].price[j] << "\t" << hotel[l].total_room[j] << endl;
                }
        }
    }
    cout << "\nДополнительные услуги, предоставляемые гостиницей\n";  // вывод дополнительных услуг, предоставляемых гостиницей
    for(i = 0; i < counter[l]; i++)
    {
        cout << hotel[l].usluga[i] << endl;
    }
    cout << "\n---------------------------\n";
    cout << "Возвращаемся в главное меню\n";
    cout << "---------------------------\n";
}

void baza_gosty(){
    cout << "Номер комнаты\t" << "Фамилия И.О.\n\n";  // вывод базы данных гости
    for(i = 0; i < kolvo_gost; i ++)
    {
        cout << gost[i].gr_number << "\t\t" << gost[i].fio << "\n";
    }
    cout << "Введите ФИО гостя, чтобы узнать подробные сведения о нем \n";
    string vr_fio;
    cin >> vr_fio;
    cout << "Номер\t" << "Фамилия И.О.\t" << "Кол-во мест\t" << "Дата заезда\t" << "Дата выезда\t" << "Доп услуги\t\n";
    for(i = 0; i < kolvo_gost; i ++)
    {
        if(vr_fio == gost[i].fio)
        {
            cout << gost[i].gr_number << "\t" << gost[i].fio << "\t" << gost[i].kolvo << "\t\t" << gost[i].arrival << "\t" << gost[i].departure << "   " << gost[i].extra_serv << '\n';
        }
    }
    cout << "---------------------------\n";
    cout << "Возвращаемся в главное меню\n";
    cout << "---------------------------\n";
}

void booking()
{
        cout << "Выберите гостиницу из списка \n";
        cout << "------------------\n";
        cout << "Название\t" << "Категория\n";
        for(int i = 0; i < k; i++)
        {
            if(hotel[i].name != hotel[i+1].name)
            {
                cout << hotel[i].name << '\t' << '\t' << hotel[i].h_category << endl; //вывод списка гостиниц
            }
        }
        string vybor;
        cin >> vybor;
        int l;
        for(i = 0; i < 6; i++)
        {
            if(vybor == hotel[i].name)   // находим индекс под которым записана гостиница
            {
                l = i;
            }
        }

        string vr_data_zaezda;
        cout << "Введите дату заезда в формате ГГГГ.ММ.ДД\n";
        cin >> vr_data_zaezda;
        string vr_data_vyezda;
        cout << "Введите дату выезда в формате ГГГГ.ММ.ДД\n";
        cin >> vr_data_vyezda;
        int non_free[30]; // занятые номера
        j = 0;
        for(i = 0; i < kolvo_gost; i++)
        {
            if(vr_data_zaezda > gost[i].arrival and vr_data_zaezda < gost[i].departure) // Записываем номера, недоступные к бронированию
            {
               non_free[j] = gost[i].gr_number;
               //cout << non_free[j] << "in" << endl;
               j++;
            }
            else if(vr_data_vyezda > gost[i].arrival and vr_data_vyezda < gost[i].departure)
            {
                non_free[j] = gost[i].gr_number;
                //cout << non_free[j] << "out" << endl;
                j++;
            }
        }
        int t = 0;
        cout << "\nСвободные номера на введенные даты\n";
        int vr_nom[20];
        for(i = 0; i < countrr[l]; i++)
        {
            vr_nom[i] = hotel[l].r_number[i]; // переносим номера гостиницы во временный список, чтобы не изменять исходный
        }
        for(i = 0; i < countrr[l]; i++)
        {
            for(t = 0; t < j; t++)
            {
                if(hotel[l].r_number[i] == non_free[t])
                {
                    vr_nom[i] = 0;                       // если номер занят, то обнуляем его номер
                }
            }

        }
        for(i = 0; i < countrr[l]; i++)
        {
            if(vr_nom[i] != 0) // выводим свободные номера(!=0)
            {
                cout << hotel[l].name << "\t" << hotel[l].h_category << "\t" << hotel[l].r_number[i] << "\t" << hotel[l].r_category[i] << "\t" << hotel[l].price[i] << endl;
            }
        }
        cout << "Введите цифры номера, который вы бы хотели забронировать\n"; // заполняем данные о госте
        cin >> gost[kolvo_gost].gr_number;
        cout << "Введите ФамилиюИ.О.\n";
        cin >> gost[kolvo_gost].fio;
        cout << "Введите количество мест\n";
        cin >> gost[kolvo_gost].kolvo;
        cout << "Можете выбрать дополнительную услугу, если не требуются, введите \"нет\" \n";
        cout << "\nДополнительные услуги, предоставляемые гостиницей\n";  // вывод дополнительных услуг, предоставляемых гостиницей, выбор услуги
        for(i = 0; i < counter[l]; i++)
        {
            cout << hotel[l].usluga[i] << endl;
        }
        cin.ignore();
        getline(cin, vr_nazv);
        gost[kolvo_gost].extra_serv = vr_nazv;  // вносим услугу
        gost[kolvo_gost].arrival = vr_data_zaezda; // вносим введенные ранее даты
        gost[kolvo_gost].departure = vr_data_vyezda;
        cout << "Номер успешно забронирован\n";
        cout << "Номер\t" << "Фамилия И.О.\t" << "Кол-во мест\t" << "Дата заезда\t" << "Дата выезда\t" << "Доп услуги\t\n";
        cout << gost[kolvo_gost].gr_number << "\t" << gost[kolvo_gost].fio << "\t" << gost[kolvo_gost].kolvo << "\t\t" << gost[kolvo_gost].arrival << "\t" << gost[kolvo_gost].departure << "   " << gost[kolvo_gost].extra_serv << '\n';
        cout << "\n---------------------------\n";
        cout << "Возвращаемся в главное меню\n";
        cout << "---------------------------\n";
        kolvo_gost++;
}


void minimum()
{
    int mini = 10000000;
    int index1; // переменные для того чтобы сохранить индексы минимального элемента
    int index2;
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < countrr[i]; j++)
        {
            if(hotel[i].price[j] < mini)
            {
                mini = hotel[i].price[j];
                index1 = i;
                index2 = j;
            }
        }
    }
    cout << "Самый дешевый номер\n";
    cout << "Название\t" << "Категория\t" << "Тип номера\t" << "Цена\t\n";
    cout << hotel[index1].name << "\t\t" << hotel[index1].h_category << "\t\t" << hotel[index1].r_category[index2] << "\t" << hotel[index1].price[index2] << "\n";
    cout << "\n---------------------------\n";
    cout << "Возвращаемся в главное меню\n";
    cout << "---------------------------\n";
}

void category()
{
    cout << "Введите тип номера \n";
    string type;
    cin >> type;
    int l = 0;
    cout << "Название\t" << "Категория\t" << "Номер\t" << "Тип номера\t" << "Цена\t\n";
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < countrr[i]; j++)
        {
            if(hotel[i].r_category[j] == type)  //находим соответствие в структуре и выводим данные
            {
                cout << hotel[i].name << "\t\t" << hotel[i].h_category << "\t\t" << hotel[i].r_number[j] << "\t" << hotel[i].r_category[j] << "\t\t" << hotel[i].price[j] << "\n";
            }
        }
    }
    cout << "\n---------------------------\n";
    cout << "Возвращаемся в главное меню\n";
    cout << "---------------------------\n";
}



int main()
{   SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream hot("gostiniza.txt"); // открываем файлы на считывание
    ifstream gos("gosty.txt");
    ifstream usl("uslugy.txt");
    ifstream nom("nomera.txt");
    k = 0;
    int vr_id;
    int l;

    while(!hot.eof()) //считываем данные из текстовых документов
    {
        hot >> hotel[k].id >> hotel[k].name >> hotel[k].h_category;
        k++;
    }

    int vr_numb;  // создадим временные переменные
    string vr_cat;
    int vr_price;
    int j = 0;
    int sum_hotel = 0; // всего номеров во всех отелях
    while(!nom.eof()) // присвоим гостиничным комнатам их номера
    {
        nom >> vr_id >> vr_numb >> vr_cat >> vr_price;
        for(i = 0; i < 5; i++)
        {
            if(vr_id == hotel[i].id)
            {
               l = i;
            }

        }
        hotel[l].r_number[countrr[l]] = vr_numb;
        hotel[l].r_category[countrr[l]] = vr_cat;
        hotel[l].price[countrr[l]] = vr_price;
        hotel[l].total_room[countrr[l]] ++;
        //cout << hotel[l].r_number[countrr[l]] << "\t" << hotel[l].r_category[countrr[l]] << "\t" << hotel[l].price[countrr[l]] << endl;
        countrr[l]++;
        sum_hotel ++;
    }

    string vr_usl;
    while(!usl.eof())
    {
        usl >> vr_id;
        for(i = 0; i < 5; i++)
        {
            if(vr_id == hotel[i].id)
            {
                l = i;
            }
        }
        getline(usl, vr_usl);
        hotel[l].usluga[counter[l]] = vr_usl;
        counter[l]++;
    }

    kolvo_gost = 0;
    while(!gos.eof())   // вносим данные о гостях
    {
        string name, surname;
        gos >> gost[kolvo_gost].gr_number >> surname >> name >> gost[kolvo_gost].kolvo >> gost[kolvo_gost].arrival >> gost[kolvo_gost].departure;
        getline(gos, vr_usl);
        gost[kolvo_gost].extra_serv = vr_usl;
        gost[kolvo_gost].fio = surname + name;
        kolvo_gost++;   // считаем количество гостей
    }

    int c;
    do
    {
    menu();  // вывод главного меню
    cin >> c;
    switch(c)
    {
    case 1:
        baza_hotel(); // база отелей
        break;
    case 2:
        baza_gosty(); // база гостей
        break;
    case 3:
        booking(); // бронирование гостиницы
        break;
    case 4:
        minimum(); // нахождение самого дешевого номера
        break;
    case 5:
        category(); // вывод номеров определенной категории
        break;
    }
    }while(c!=0);
    cout << "Завершение программы";

    hot.close(); // закрываем потоки
    gos.close();
    usl.close();
    nom.close();
    return 0;
}
