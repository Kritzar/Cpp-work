#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

// Prototypes
void cost_calculation();
void check_route();
void metro_map();
void customer_menu();
int farecost = 10;
class CreditCard;
int check_validity(long long Input);
void newCard();
void delCard();
class admin;
vector<admin> users;
string encryption(string s);
string decryption(string s);
vector<CreditCard> C;

admin *adminlogin();
// CREDIT CARD CLASS -
class CreditCard
{
    string username;
    long long cred;
    float balance;

public:
    void create(string n, long long num, float bal)
    {
        cred = num;
        username = n;
        balance = bal;
    }
    void update_amount(float bill)
    {
        cout << "CURRENT AMOUNT : " << balance<<endl;
        cout << "CHARGES : " << bill<<endl;
        if (bill > balance)
        {
            cout << "NOT ENOUGH BALANCE IN ACCOUNT! PAYMENT FAILED!\n";
            return;
        }
        balance -= bill;
        cout << "BALANCE LEFT : " << balance<<endl;
        ofstream re;
        re.open("creditCards.txt");
        for (CreditCard o : C)
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance() << endl;
        }
        re.close();
    }
    void printCred()
    {
        cout << "\t\t\t\t\tCREDIT CARD - " << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "CARD HOLDER : " << username << endl;
        cout << "CREDIT CARD NUMBER : " << cred << endl;
        cout << "BALANCE : " << balance << endl;
        cout << "------------------------------------------------------------------" << endl;
    }

    void card_Recharge()
    {
        float recharge;
        cout << "ENTER AMOUNT TO BE TOPPED-UP : ";
        cin >> recharge;
        balance += recharge;
        cout << "CURRENT BALANCE : " << balance;
        ofstream re;
        re.open("creditCards.txt");
        for (CreditCard o : C)
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance() << endl;
        }
        re.close();
    }

    void check_balance()
    {
        cout << "BALANCE IN CARD IS : " << balance;
    }

    string info_name()
    {
        return username;
    }
    long long info_cred()
    {
        return cred;
    }
    float info_balance()
    {
        return balance;
    }
};

// ADMIN CLASS -
class admin
{
    string username;
    string password;

public:
    void printCardDetails(vector<CreditCard> C)
    {
        for (CreditCard temp : C)
        {
            temp.printCred();
        }
    }
    void setData(string n, string p)
    {
        username = n;
        password = p;
    }
    void newUser(vector<admin> &l)
    {

        admin obj;
        cout << "CREATING NEW USER...." << endl;
        cout << "ENTER USERNAME : ";
        cin >> username;
        string encryp;
        cout << "ENTER PASSWORD : ";
        cin >> encryp;
        password = encryption(encryp);

        obj.setData(username, password);
        l.push_back(obj);

        ofstream f2;
        f2.open("admins.txt");
        for (admin o : l)
        {
            f2 << o.username_info() << endl;
            f2 << o.password_info() << endl;
        }
        f2.close();

        /*ofstream f;
        f.open("ADMIN_INFO.dat", ios::binary | ios::app);

        f.write(reinterpret_cast<char *>(&obj), sizeof(admin));
        cout << "NEW USER SUCCESSFULLY CREATED! " << endl;
        cout << "DETAILS WILL BE REFLECTED WHEN PROGRAM IS RUN AGAIN!" << endl;
        f.close();*/
    }

    int check(string u, string p)
    {
        if (username == u && password == encryption(p))
        {
            return 1;
        }
        return 0;
    }

    void changePassword()
    {
        system("CLS");

        string test;
        cout << "ENTER CURRENT PASSWORD : ";
        cin >> test;
        if (test != decryption(password))
        {
            cout << "INCORRECT PASSWORD ENTERED! PERMISSION TO CHANGE PASSWORD DENIED!" << endl;
            return;
        }
        cout << "CURRENT PASSWORD CORRECTLY ENTERED!" << endl;
        vector<admin>::iterator q = users.begin();
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].username_info() == username)
            {
                users.erase(users.begin() + i);
                break;
            }
        }
        cout << "ENTER NEW PASSWORD : ";
        cin >> test;
        password = encryption(test);
        cout << "PASSWORD SUCCESSFULLY CHANGED!" << endl;
        users.push_back(*this);
        ofstream f2;
        f2.open("admins.txt");
        for (admin o : users)
        {
            f2 << o.username_info() << endl;
            f2 << o.password_info() << endl;
        }
        f2.close();
    }
    string username_info()
    {
        return username;
    }
    string password_info()
    {
        return password;
    }
    void change_fare_price();
    void new_STATION_registration();
    void print_all_metro_details();
    void print_metro_map();
};

// STATION CLASS -
class station
{
    string station_name;
    int station_number;

public:
    static int count;
    station *next;
    station *previous;
    station()
    {
        cout << "Enter station name" << endl;
        cin >> station_name;
        count++;
        station_number = count;
        next = NULL;
        previous = NULL;
    }
    station(string n, int sn)
    {
        station_name = n;
        station_number = sn;
        count++;
        next = NULL;
        previous = NULL;
    }
    string getsName()
    {
        return station_name;
    }
    int getsNumber()
    {
        return station_number;
    }
    void IncreaseStationNumber()
    {
        station_number++;
    }
    void DecreaseStationNumber()
    {
        station_number--;
    }
};

int station::count = 0;
admin *adminlogin()
{
    system("CLS");
    cout << "ADMIN LOGIN PORTAL - " << endl;
    string name, pass;
    cout << "ENTER admin username : ";
    cin >> name;
    cout << "Enter password : ";
    cin >> pass;
    admin *now;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].check(name, pass))
        {
            now = &users[i];
            return now;
            cout << "LOGIN SUCCESSFUL!" << endl;
            break;
        }
        if (i == users.size() - 1)
        {
            cout << "NO SUCH USER FOUND! CHECK USERNAME OR PASSWORD!" << endl;
            return NULL;
        }
    }
    return NULL;
}
void AddNode(station **list, string n, int sn)
{
    station *s = new station(n, sn);
    if (*list == NULL)
    {
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL)
    {
        (*list)->next = s;
        s->previous = *list;
    }
    else
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        p->next = s;
        s->previous = p;
    }
}
void readFile(station **list)
{
    ifstream f1;
    f1.open("stations.txt");
    while (!f1.eof())
    {
        string s;
        f1 >> s;
        int i;
        f1 >> i; // 1
        AddNode(list, s, i);
    }
    f1.close();
}
void AddNodeByAdmin(station **list, int pos)
{
    cout << "Enter station name\n";
    string s1;
    cin >> s1;
    station *s = new station(s1, pos);
    if (*list == NULL && pos == 1)
    {
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL && pos == 1)
    {
        (*list)->previous = s;
        s->next = *list;
        (*list)->IncreaseStationNumber();
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL && pos == 2)
    {
        (*list)->next = s;
        s->previous = *list;
    }
    else if ((*list)->previous != NULL && (*list)->next != NULL && pos == 1)
    {
        s->next = *list;
        (*list)->previous = s;
        station *p = *list;
        *list = s;
        while (p != NULL)
        {
            p->IncreaseStationNumber();
            p = p->next;
        }
    }
    else if (pos == station::count)
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        p->next = s;
        s->previous = p;
    }
    else
    {
        station *p;
        for (p = *list; p != NULL; p = p->next)
        {
            if (p->getsNumber() == pos)
            {
                break;
            }
        }
        (p->previous)->next = s;
        s->previous = p->previous;
        s->next = p;
        p->previous = s;
        while (p != NULL)
        {
            p->IncreaseStationNumber();
            p = p->next;
        }
    }
}
void DeleteNode(station **list, int pos)
{
    station::count--;
    if (*list == NULL)
    {
        station::count = 0;
        cout << "There are no stations\n";
    }
    else if ((*list)->next == NULL && pos == 1)
    {
        delete *list;
        *list = NULL;
    }
    else if (pos == 1)
    {
        station *p = (*list)->next;
        delete *list;
        *list = p;
        while (p != NULL)
        {
            p->DecreaseStationNumber();
            p = p->next;
        }
    }
    else if ((*list)->next == NULL && pos != 1)
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        (p->previous)->next = NULL;
        delete p;
    }
    else
    {
        station *p, *p1;
        for (p = *list; p != NULL; p = p->next)
        {
            if (p->getsNumber() == pos)
                break;
        }
        (p->previous)->next = p->next;
        (p->next)->previous = p->previous;
        p1 = p->next;
        delete p;
        while (p1 != NULL)
        {
            p1->DecreaseStationNumber();
            p1 = p1->next;
        }
    }
}

void writefile(station *list)
{
    ofstream f1;
    f1.open("stations.txt");
    for (station *p = list; p != NULL; p = p->next)
    {
        f1 << p->getsName() << endl;
        if (p->next == NULL)
            f1 << p->getsNumber();
        else
            f1 << p->getsNumber() << endl;
    }
    f1.close();
}
/* void writefile1()
{
    ofstream f1;
    f1.open("stations.txt");
    f1<<"Noida"<<endl;
    f1<<1<<endl;
    f1<<"Delhi"<<endl;
    f1<<2<<endl;
    f1.close();
} */
void displayList(station *list)
{
    for (station *p = list; p != NULL; p = p->next)
    {
        cout << "Station Number:" << p->getsNumber() << endl;
        cout << "Station Name:" << p->getsName() << endl
             << endl;
    }
}
int cost_calculation(station *list, string s1, string s2)
{
    int ssn = 0, esn = 0;
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    station *p;
    for (p = list; p != NULL; p = p->next)
    {
        string s3 = p->getsName();
        transform(s3.begin(), s3.end(), s3.begin(), ::toupper);
        if (s1 == s3)
            ssn = p->getsNumber();
        if (s2 == s3)
            esn = p->getsNumber();
    }
    int tcost = (esn - ssn > 0 ? esn - ssn : ssn - esn) * farecost;
    return tcost;
}
void deletecompletelist(station *list)
{
    station *p = list;
    list = p->next;
    while (p != NULL)
    {
        delete p;
        p = list;
        list = list->next;
    }
}
int check_station_Validity(station *list, string s1)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    for (station *p = list; p != NULL; p = p->next)
    {
        string s2 = p->getsName();
        transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
        if (s1 == s2)
            return (p->getsNumber());
    }
    return -1;
}
void check_route(station *list, string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    station *p;
    bool b = false;
    int n1 = check_station_Validity(list, s1), n2 = check_station_Validity(list, s2);
    if (n1 == n2 || n1 == -1 || n2 == -1)
    {
        cout << "Invalid Input" << endl;
        return;
    }
    else if (n1 < n2)
    {
        for (p = list; p != NULL; p = p->next)
        {
            string s3 = p->getsName();
            transform(s3.begin(), s3.end(), s3.begin(), ::toupper);
            if (s1 == s3)
            {
                b = true;
                cout << "STARTING POINT:" << endl
                     << endl;
            }
            if (b)
            {
                cout << "Station Number:" << p->getsNumber() << endl;
                cout << "Station Name:" << p->getsName() << endl
                     << endl;
            }
            if (s2 == s3)
            {
                b = false;
                cout << "ENDING POINT:" << endl;
            }
        }
    }
    else
    {
        for (p = list; p != NULL; p = p->next)
        {
            if (n1 == p->getsNumber())
                break;
        }
        cout << "STARTING POINT:" << endl
             << endl;
        while (p->getsNumber() != n2)
        {
            cout << "Station Number:" << p->getsNumber() << endl;
            cout << "Station Name:" << p->getsName() << endl
                 << endl;
            p = p->previous;
        }
        cout << "Station Number:" << p->getsNumber() << endl;
        cout << "Station Name:" << p->getsName() << endl;
        cout << "ENDING POINT:" << endl;
    }
}
void book_a_ticket(station *list)
{
    cout << "Please enter the name of your current station" << endl;
    string s1;
    cin >> s1;
    cout << "Please enter your destination\n";
    string s2;
    cin >> s2;
    int n1 = check_station_Validity(list, s1);
    int n2 = check_station_Validity(list, s2);
    if (n1 == -1 || n2 == -1)
    {
        cout << "INVALID INPUT\n";
        return;
    }
    else
    {
        system("cls");
        check_route(list, s1, s2);
        cout << "Number of stations to travel:" << ((n1 > n2) ? n1 - n2 : n2 - n1) << endl;
        cout << "Total Cost:" << cost_calculation(list, s1, s2) << endl;
        cout << "Do you wish to proceed?Enter Y or N\n";
        char ch;
        cin >> ch;
        if (ch == 'Y')
        {
            system("cls");
            cout << "How do you wish to make the payment\n";
            cout << "1.Cash\n";
            cout << "2.Metro Card" << endl;
            cout << "3.Exit" << endl;
            cout << "Enter your choice" << endl;
            int choice1;
            cin >> choice1;
            ofstream er;
            CreditCard *temp = NULL;
            int flag = 0;
            switch (choice1)
            {
            case 1:
                cout << "Booking successful\n";
                cout << "Press Enter\n";
                getch();
                break;
            case 2: // metro card fuctions
                system("CLS");

                long long test;
                cout << "ENTER METRO CARD NUMBER : ";
                cin >> test;

                // vector<CreditCard>::iterator q = C.begin();
                for (int i = 0; i < C.size(); i++)
                {

                    if (C[i].info_cred() == test)
                    {
                        flag = 1;
                        cout << "CARD FOUND IN SYSTEM!" << endl;
                        int cost = cost_calculation(list, s1, s2);
                        temp = &C[i];
                        temp->update_amount(cost);
                        cout << "PAYMENT SUCCESSFULLY DONE! THANK YOU FOR USING NON-CONTACT METHOD OF PAYMENT." << endl;
                        getch();
                        system("cls");
                        break;
                    }
                }
                if (flag == 0)
                {
                    cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
                    return;
                }

                er.open("creditCards.txt");
                for (CreditCard o : C)
                {
                    er << o.info_name() << endl;
                    er << o.info_cred() << endl;
                    er << o.info_balance() << endl;
                }
                er.close();
                break;
            case 3:
                break;
            default:
                cout << "Invalid Input\n";
            }
        }
        else if (ch == 'N')
        {
            cout << "BOOKING CANCELLED\n";
            getchar();
            return;
        }
        else
        {
            cout << "INVALID INPUT\n";
            return;
        }
    }
}
void customer_menu(station *list)
{
    cout << "\t\t\t\t\t*****CUSTOMER MENU*****\n\n\n";
    cout << "\t\t\t\t\t1.Book a ticket\n";
    cout << "\t\t\t\t\t2.See the Metro map\n";
    cout << "\t\t\t\t\t3.Check Route\n";
    cout << "\t\t\t\t\t4.Check metro card balance\n";
    cout << "\t\t\t\t\t5.New Card Registration\n";
    cout << "\t\t\t\t\t6.Recharge metro card\n";
    cout << "\t\t\t\t\t7.Help\n";
    cout << "\t\t\t\t\t8.About us\n";
    cout << "\t\t\t\t\t9.Exit\n";
    cout << "\t\t\t\t\tENTER YOUR CHOICE\n";
    int choice;
    string m1, m2;
    long long test;
    int flag = 0;
    cin >> choice;
    switch (choice)
    {
    case 1:
        book_a_ticket(list);
        break;
    case 2:
        displayList(list);
        getch();
        system("cls");
        break;
    case 3:
        cout << "Enter station number 1:";
        cin >> m1;
        cout << "Enter station 2: ";
        cin >> m2;
        check_route(list, m1, m2);
        getch();
        system("cls");
        break;
    case 4:
        system("CLS");

        cout << "ENTER METRO CARD NUMBER : ";
        cin >> test;
        flag = 0;
        // vector<CreditCard>::iterator q = C.begin();
        for (int i = 0; i < C.size(); i++)
        {

            if (C[i].info_cred() == test)
            {
                flag = 1;
                C[i].check_balance();
                break;
            }
        }
        if (flag == 0)
        {
            cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        }
        getch();
        system("CLS");
        break;
    case 5:
        newCard();
        getch();
        system("CLS");
        break;
    case 6:
        long long test;
        cout << "ENTER METRO CARD NUMBER : ";
        cin >> test;
        // vector<CreditCard>::iterator q = C.begin();
        for (int i = 0; i < C.size(); i++)
        {

            if (C[i].info_cred() == test)
            {
                flag = 1;
                C[i].card_Recharge();
                break;
            }
        }
        if (flag == 0)
        {
            cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        }
        getch();
        system("CLS");
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        cout << "YOU HAVE CHOSEN TO EXIT THE CUSTOMER PORTAL!" << endl;
        cout << "THANK YOU FOR USING OUR SERVICES, SEE U SOON!" << endl;
        cout << "RETURNING TO MAIN MENU" << endl;
        getch();
        system("CLS");
        break;
    default:
        cout << "Invalid Input\n";
    }
    system("cls");
}
void adminmenu(station **list, admin *now)
{
    cout << "\t\t\t\t****ADMIN MENU****" << endl;
    cout << "\t\t\t\t1.New Station Registration\n";
    cout << "\t\t\t\t2.Delete an existing station\n";
    cout << "\t\t\t\t3.Change fare price" << endl;
    cout << "\t\t\t\t4.Delete a Metro Card" << endl;
    cout << "\t\t\t\t5.Print Details of all existing metro cards in the system\n";
    cout << "\t\t\t\t6.Change Password\n";
    cout << "\t\t\t\t7.Exit" << endl;
    cout << "\t\t\t\tEnter your choice\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Enter the position which you want to add the station\n";
        int pos;
        cin >> pos;
        AddNodeByAdmin(list, pos);
        system("cls");
        cout << "Station Added successfully\n";
        writefile(*list);
        getch();
        break;
    case 2:
        cout << "Enter the station number which you want to delete\n";
        int pos1;
        cin >> pos1;
        DeleteNode(list, pos1);
        cout << "Station Deleted successfully\n";
        writefile(*list);
        getch();
        system("CLS");

        break;
    case 3:
        cout << "Current Fare Price = " << farecost << endl;
        cout << "Enter new fare price\n";
        cin >> farecost;
        cout << "Fare Price has been successfully changed!\n";
        getch();
        system("cls");
        break;
    case 4:
        delCard();
        getch();
        system("CLS");
        break;
    case 5:
        now->printCardDetails(C);
        getch();
        system("cls");
        break;
    case 6:
        now->changePassword();
        getch();
        system("CLS");
        break;
    case 7:
        cout << "YOU HAVE CHOSEN TO EXIT THE PROGRAM!" << endl;
        cout << "ADMIN HAS BEEN LOGGED OUT SUCCESSFULLY!" << endl;
        cout << "THANK YOU FOR USING ADMIN PORTAL" << endl;
        break;
    default:
        cout << "Invalid Input\nTRY AGAIN!\n";
        getch();
        system("CLS");
        break;
    }
}
void menu(station **list)
{

    while (true)
    {
        cout << "\t\t\t\t***********************************************************************************" << endl;
        cout << "\t\t\t\t***                        JAYPEE METRO SYSTEM                                  ***" << endl;
        cout << "\t\t\t\t***********************************************************************************\n\n\n\n";
        cout << "\t\t\t\t\t\t\tWelcome to Metropolis\n";
        cout << "\t\t\t\t\t\t\tAre you a..." << endl;
        cout << "\t\t\t\t\t\t\t1.Administrator" << endl;
        cout << "\t\t\t\t\t\t\t2.Customer" << endl;
        cout << "\t\t\t\t\t\t\t3.Exit the program\n";
        cout << "\t\t\t\t\t\t\tEnter your choice\n";
        int choice;
        cin >> choice;
        if (choice == 3)
            break;
        else if (!(choice >= 1 && choice <= 3))
        {
            cout << "INVALID INPUT! TRY AGAIN!" << endl;
            getch();
            system("CLS");
            continue;
        }
        else
        {
            if (choice == 1)
            {
                system("cls");
                admin *now = adminlogin();
                if (now == NULL)
                {
                    continue;
                }
                adminmenu(list, now);
            }
            if (choice == 2)
            {
                system("cls");
                customer_menu(*list);
            }
        }
    }
}

string encryption(string s)
{
    int l = s.length();
    int b = ceil(sqrt(l));
    int a = floor(sqrt(l));
    string encrypted;
    if (b * a < l)
    {
        if (min(b, a) == b)
        {
            b = b + 1;
        }
        else
        {
            a = a + 1;
        }
    }

    // Matrix to generate the
    // Encrypted String
    char arr[a][b];
    memset(arr, ' ', sizeof(arr));
    int k = 0;

    // Fill the matrix row-wise
    for (int j = 0; j < a; j++)
    {
        for (int i = 0; i < b; i++)
        {
            if (k < l)
            {
                arr[j][i] = s[k];
            }
            k++;
        }
    }

    // Loop to generate
    // encrypted string
    for (int j = 0; j < b; j++)
    {
        for (int i = 0; i < a; i++)
        {
            encrypted = encrypted +
                        arr[i][j];
        }
    }
    return encrypted;
}

// Function to decrypt the string
string decryption(string s)
{
    int l = s.length();
    int b = ceil(sqrt(l));
    int a = floor(sqrt(l));
    string decrypted;

    // Matrix to generate the
    // Encrypted String
    char arr[a][b];
    memset(arr, ' ', sizeof(arr));
    int k = 0;

    // Fill the matrix column-wise
    for (int j = 0; j < b; j++)
    {
        for (int i = 0; i < a; i++)
        {
            if (k < l)
            {
                arr[j][i] = s[k];
            }
            k++;
        }
    }

    // Loop to generate
    // decrypted string
    for (int j = 0; j < a; j++)
    {
        for (int i = 0; i < b; i++)
        {
            decrypted = decrypted +
                        arr[i][j];
        }
    }
    return decrypted;
}
void newCard()
{
    cout << "\t\t\t\tENTER DETAILS TO CREATE NEW CARD - ....\n";
    string name;
    long long credit;

    cout << "ENTER CARD HOLDER NAME : ";
    cin >> name;
    // PROMPTS THE USER TO ENTER A CREDIT CARD NUMBER
    cout << "PLEASE ENTER A CREDIT CARD NUMBER FOR VERIFICATION!\n";
    cin >> credit;
    cout << "YOUR CARD IS : ";
    if (check_validity(credit) == -1)
    {
        return;
    }
    float bal;
    cout << "ENTER BALANCE IN CARD : ";
    cin >> bal;
    CreditCard temp;
    temp.create(name, credit, bal);
    C.push_back(temp);

    ofstream re;
    re.open("creditCards.txt");
    for (CreditCard o : C)
    {
        re << o.info_name() << endl;
        re << o.info_cred() << endl;
        re << o.info_balance() << endl;
    }
    re.close();
}

void delCard()
{
    system("CLS");

    long long test;
    cout << "ENTER METRO CARD NUMBER : ";
    cin >> test;
    int flag = 0;
    vector<CreditCard>::iterator q = C.begin();
    for (int i = 0; i < C.size(); i++)
    {
        if (C[i].info_cred() == test)
        {
            flag = 1;
            C.erase(C.begin() + i);
            cout << "CARD SUCCESSFULLY DELETED!" << endl;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        return;
    }
    ofstream re;
    re.open("creditCards.txt");
    for (CreditCard o : C)
    {
        re << o.info_name() << endl;
        re << o.info_cred() << endl;
        re << o.info_balance() << endl;
    }
    re.close();
}

int check_validity(long long Input)
{
    int sumE = 0;
    int sumO = 0;
    long long credE = Input / 10;
    long long credO = Input;

    // final DESCRIBES THE VALUE WHEN THE SECOND LAST DIGIT IS SELECTED. IF IT IS MORE THAN 9,THEN ITS DIGITS ARE ADDED AS SHOWN BELOW

    int final = 0;

    do
    {
        // remE DESCRIBES THE REMAINDER OR THE SECOND TO LAST DIGIT IN EACH LOOP(STARTING FROM ORIGINAL INPUT VALUE)
        int remE = credE % 10;

        // multiple INDICATES THE DOUBLING OF THE SECOND TO LAST DIGIT ACCORDING TO LUHN'S ALGORITHM
        int multiple = remE * 2;

        // credE IS DIVIDED BY 100 TO PROCEED TO THE SECOND TO SECOND TO LAST DIGIT AND SO ON
        credE = credE / 100;

        // AN IF-ELSE STATEMENT TO ADD UP THE DIGITS OF FACTOR IF IT IS A DOUBLE DIGIT NUMBER
        if (multiple < 10)
        {
            final = multiple;
        }
        else
        {
            // ones AND tens DESCRIBE(OBVIOUSLY) THE ONES AND TENS DIGITS OF multiple IF IT IS A DOUBLE DIGIT NUMBER
            int ones = multiple % 10;
            int tens = multiple / 10;
            final = ones + tens;
        }
        // THE SUM OF OPERATIONS ON EVEN VALUES FROM END OF NUMBER ACCORDING TO ALGORITHM
        sumE += final;
    } while (credE > 0);

    do
    {
        int remO = credO % 10;
        credO = credO / 100;
        sumO += remO;
    } while (credO > 0);

    int sum = sumE + sumO;
    int checksum = sum % 10;

    // CALCULATING THE NUMBER OF DIGITS

    int count = 0;
    long long length = Input;
    do
    {
        length /= 10;
        count += 1;
    } while (length > 0);

    // CALCULATING THE FIRST DIGIT OF CREDIT CARD
    long long length_1 = Input;
    long long length_2 = Input;
    long long first_digit;
    long long second_digit;

    do
    {
        first_digit = length_1;
        length_1 /= 10;
    } while (length_1 > 0);

    do
    {
        second_digit = length_2;
        length_2 /= 10;
    } while (length_2 > 9);

    // TO CHECK WHICH TYPE OF CREDIT CARD NUMBER WAS THE INPUT IF IT IS EVEN VALID AT ALL.
    if (checksum == 0 && count == 13 && first_digit == 4)
    {
        cout << "VISA\n";
        return 0;
    }
    else if (checksum == 0 && count == 15 && (second_digit == 34 || second_digit == 37))
    {
        cout << "AMEX\n";
        return 0;
    }
    else if (checksum == 0 && count == 16 && first_digit == 4)
    {
        cout << "VISA\n";
        return 0;
    }
    else if (checksum == 0 && count == 16 && second_digit > 50 && second_digit < 56)
    {
        cout << "MASTERCARD\n";
        return 0;
    }
    else
    // IF THE INPUT DOESN'T EVEN PASS THE CHECKSUM,THEN OBVIOUSLY IT IS AN INVALID CREDIT CARD NUMBER
    {
        cout << "INVALID\n";
        return -1;
    }
}

void load()
{
    ifstream card;
    card.open("creditCards.txt");
    // cout << "1";
    if (!card)
    {
        cout << "FILE DOESN'T EXIST!" << endl;
        card.close();
        goto next;
    }
    while (card.eof() == false)
    {
        // cout << "2";
        CreditCard o;
        string s;
        card >> s;
        long long i;
        card >> i;
        float b;
        card >> b;
        o.create(s, i, b);
        C.push_back(o);
    }
    card.close();
next:
    // cout << "3";
    // newCard();
    ifstream a1;
    a1.open("admins.txt");
    if (!a1)
    {
        cout << "FILE DOESN'T EXIST!" << endl;
        a1.close();
        goto next2;
    }
    while (!a1.eof())
    {
        // j++;
        admin o;
        string s;
        a1 >> s;
        string i;
        a1 >> i; // 1
        o.setData(s, i);
        users.push_back(o);
        // AddNode(vector,s,i);
    }
    // cout << j << endl;
    a1.close();
next2:
    cout << "HI!" << endl;
    /*admin use;
    use.newUser(users);*/
}

int main()
{
    load();

    station *list = NULL;
    readFile(&list);
    menu(&list);
    deletecompletelist(list);
    return 0;
}
