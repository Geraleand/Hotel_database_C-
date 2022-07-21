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

int i;  // �������
int k;  // ���������� ������
int j;  // �������
int kolvo_usl; // ���������� �����
string vr_nazv; // ���������� ��� ��������� �������� �����
string vr_category; // ���������� ��� ��������� ��������� ������
int kolvo_gost; // ���������� ������
int counter[7]; // ������ ��������� ��� �����
int countrr[7] = {0,0,0,0,0,0,0}; // ������ ������� ���������� ������� � �����

struct hotels{
int id;                 //������������� ���������
int total_room[20];         //���-�� ������� ������������� ���� � ���������
int free_room;          //���-�� ��������� ������� ������������� ���� � ���������
int price[20];              //���� ������
int r_number[20];       //����� �������
string name;            //�������� ���������
string h_category;      //��������� �����
string r_category[20];      //��������� ������
string usluga[10];         // ������, ����������� ������
}hotel[20];

struct gosty{
string fio;         // ��� �����
string arrival;     // ���� ������
string departure;   // ���� ������
string extra_serv;  // ��������� ��� ������
int gr_number;      // ��������� ������ �����
int kolvo;          // ���������� ����
}gost[100];



void menu()
{
    cout << "������� ����\n";  // ����� �������� ����
    cout << "----------------\n";
    cout << "�������� � ���������� (1)\n";
    cout << "�������� � ������ (2)\n";
    cout << "������������� ����� (3)\n";
    cout << "����� � ����������� ����� (4)\n";
    cout << "����� ������� ������������� ���� (5)\n";
    cout << "���������� ��������� (0)\n";
}


void baza_hotel()
{
    cout << "\n������ �������� \n";       // ����� ������ ��������
    cout << "------------------\n";
    cout << "��������\t" << "���������\n";
    for(int i = 0; i < k; i++)
    {
        if(hotel[i].name != hotel[i+1].name)
        {
            cout << hotel[i].name << '\t' << '\t' << hotel[i].h_category << endl;
        }
    }
    cout << "\n������� �������� ���������, ����� �������� ����� ��������� �������� � ���\n";
    cin >> vr_nazv;
    cout << "��� ������\t" << "����\t" << "���������� �������\t" << endl;   // ����� ������ �������, � ��������� ���������
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
    cout << "\n�������������� ������, ��������������� ����������\n";  // ����� �������������� �����, ��������������� ����������
    for(i = 0; i < counter[l]; i++)
    {
        cout << hotel[l].usluga[i] << endl;
    }
    cout << "\n---------------------------\n";
    cout << "������������ � ������� ����\n";
    cout << "---------------------------\n";
}

void baza_gosty(){
    cout << "����� �������\t" << "������� �.�.\n\n";  // ����� ���� ������ �����
    for(i = 0; i < kolvo_gost; i ++)
    {
        cout << gost[i].gr_number << "\t\t" << gost[i].fio << "\n";
    }
    cout << "������� ��� �����, ����� ������ ��������� �������� � ��� \n";
    string vr_fio;
    cin >> vr_fio;
    cout << "�����\t" << "������� �.�.\t" << "���-�� ����\t" << "���� ������\t" << "���� ������\t" << "��� ������\t\n";
    for(i = 0; i < kolvo_gost; i ++)
    {
        if(vr_fio == gost[i].fio)
        {
            cout << gost[i].gr_number << "\t" << gost[i].fio << "\t" << gost[i].kolvo << "\t\t" << gost[i].arrival << "\t" << gost[i].departure << "   " << gost[i].extra_serv << '\n';
        }
    }
    cout << "---------------------------\n";
    cout << "������������ � ������� ����\n";
    cout << "---------------------------\n";
}

void booking()
{
        cout << "�������� ��������� �� ������ \n";
        cout << "------------------\n";
        cout << "��������\t" << "���������\n";
        for(int i = 0; i < k; i++)
        {
            if(hotel[i].name != hotel[i+1].name)
            {
                cout << hotel[i].name << '\t' << '\t' << hotel[i].h_category << endl; //����� ������ ��������
            }
        }
        string vybor;
        cin >> vybor;
        int l;
        for(i = 0; i < 6; i++)
        {
            if(vybor == hotel[i].name)   // ������� ������ ��� ������� �������� ���������
            {
                l = i;
            }
        }

        string vr_data_zaezda;
        cout << "������� ���� ������ � ������� ����.��.��\n";
        cin >> vr_data_zaezda;
        string vr_data_vyezda;
        cout << "������� ���� ������ � ������� ����.��.��\n";
        cin >> vr_data_vyezda;
        int non_free[30]; // ������� ������
        j = 0;
        for(i = 0; i < kolvo_gost; i++)
        {
            if(vr_data_zaezda > gost[i].arrival and vr_data_zaezda < gost[i].departure) // ���������� ������, ����������� � ������������
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
        cout << "\n��������� ������ �� ��������� ����\n";
        int vr_nom[20];
        for(i = 0; i < countrr[l]; i++)
        {
            vr_nom[i] = hotel[l].r_number[i]; // ��������� ������ ��������� �� ��������� ������, ����� �� �������� ��������
        }
        for(i = 0; i < countrr[l]; i++)
        {
            for(t = 0; t < j; t++)
            {
                if(hotel[l].r_number[i] == non_free[t])
                {
                    vr_nom[i] = 0;                       // ���� ����� �����, �� �������� ��� �����
                }
            }

        }
        for(i = 0; i < countrr[l]; i++)
        {
            if(vr_nom[i] != 0) // ������� ��������� ������(!=0)
            {
                cout << hotel[l].name << "\t" << hotel[l].h_category << "\t" << hotel[l].r_number[i] << "\t" << hotel[l].r_category[i] << "\t" << hotel[l].price[i] << endl;
            }
        }
        cout << "������� ����� ������, ������� �� �� ������ �������������\n"; // ��������� ������ � �����
        cin >> gost[kolvo_gost].gr_number;
        cout << "������� ��������.�.\n";
        cin >> gost[kolvo_gost].fio;
        cout << "������� ���������� ����\n";
        cin >> gost[kolvo_gost].kolvo;
        cout << "������ ������� �������������� ������, ���� �� ���������, ������� \"���\" \n";
        cout << "\n�������������� ������, ��������������� ����������\n";  // ����� �������������� �����, ��������������� ����������, ����� ������
        for(i = 0; i < counter[l]; i++)
        {
            cout << hotel[l].usluga[i] << endl;
        }
        cin.ignore();
        getline(cin, vr_nazv);
        gost[kolvo_gost].extra_serv = vr_nazv;  // ������ ������
        gost[kolvo_gost].arrival = vr_data_zaezda; // ������ ��������� ����� ����
        gost[kolvo_gost].departure = vr_data_vyezda;
        cout << "����� ������� ������������\n";
        cout << "�����\t" << "������� �.�.\t" << "���-�� ����\t" << "���� ������\t" << "���� ������\t" << "��� ������\t\n";
        cout << gost[kolvo_gost].gr_number << "\t" << gost[kolvo_gost].fio << "\t" << gost[kolvo_gost].kolvo << "\t\t" << gost[kolvo_gost].arrival << "\t" << gost[kolvo_gost].departure << "   " << gost[kolvo_gost].extra_serv << '\n';
        cout << "\n---------------------------\n";
        cout << "������������ � ������� ����\n";
        cout << "---------------------------\n";
        kolvo_gost++;
}


void minimum()
{
    int mini = 10000000;
    int index1; // ���������� ��� ���� ����� ��������� ������� ������������ ��������
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
    cout << "����� ������� �����\n";
    cout << "��������\t" << "���������\t" << "��� ������\t" << "����\t\n";
    cout << hotel[index1].name << "\t\t" << hotel[index1].h_category << "\t\t" << hotel[index1].r_category[index2] << "\t" << hotel[index1].price[index2] << "\n";
    cout << "\n---------------------------\n";
    cout << "������������ � ������� ����\n";
    cout << "---------------------------\n";
}

void category()
{
    cout << "������� ��� ������ \n";
    string type;
    cin >> type;
    int l = 0;
    cout << "��������\t" << "���������\t" << "�����\t" << "��� ������\t" << "����\t\n";
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < countrr[i]; j++)
        {
            if(hotel[i].r_category[j] == type)  //������� ������������ � ��������� � ������� ������
            {
                cout << hotel[i].name << "\t\t" << hotel[i].h_category << "\t\t" << hotel[i].r_number[j] << "\t" << hotel[i].r_category[j] << "\t\t" << hotel[i].price[j] << "\n";
            }
        }
    }
    cout << "\n---------------------------\n";
    cout << "������������ � ������� ����\n";
    cout << "---------------------------\n";
}



int main()
{   SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream hot("gostiniza.txt"); // ��������� ����� �� ����������
    ifstream gos("gosty.txt");
    ifstream usl("uslugy.txt");
    ifstream nom("nomera.txt");
    k = 0;
    int vr_id;
    int l;

    while(!hot.eof()) //��������� ������ �� ��������� ����������
    {
        hot >> hotel[k].id >> hotel[k].name >> hotel[k].h_category;
        k++;
    }

    int vr_numb;  // �������� ��������� ����������
    string vr_cat;
    int vr_price;
    int j = 0;
    int sum_hotel = 0; // ����� ������� �� ���� ������
    while(!nom.eof()) // �������� ����������� �������� �� ������
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
    while(!gos.eof())   // ������ ������ � ������
    {
        string name, surname;
        gos >> gost[kolvo_gost].gr_number >> surname >> name >> gost[kolvo_gost].kolvo >> gost[kolvo_gost].arrival >> gost[kolvo_gost].departure;
        getline(gos, vr_usl);
        gost[kolvo_gost].extra_serv = vr_usl;
        gost[kolvo_gost].fio = surname + name;
        kolvo_gost++;   // ������� ���������� ������
    }

    int c;
    do
    {
    menu();  // ����� �������� ����
    cin >> c;
    switch(c)
    {
    case 1:
        baza_hotel(); // ���� ������
        break;
    case 2:
        baza_gosty(); // ���� ������
        break;
    case 3:
        booking(); // ������������ ���������
        break;
    case 4:
        minimum(); // ���������� ������ �������� ������
        break;
    case 5:
        category(); // ����� ������� ������������ ���������
        break;
    }
    }while(c!=0);
    cout << "���������� ���������";

    hot.close(); // ��������� ������
    gos.close();
    usl.close();
    nom.close();
    return 0;
}
