#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<cctype>
#include<bits/stdc++.h>
using namespace std;

class PhoneBook 
{
    int srno;
    char n[28];
    char m[17];
    char e[40];
    char g[30];

public:
    int getSrNo() { return srno; }

    int storeData()
    {
        cout << "\n.......CREATE NEW PHONE RECORD.........\n";
        cout << "Enter Serial Number : ";
        cin >> srno; cin.ignore();

        // Validate and input name
        bool validName = false;
        do {
            cout << "Enter Full Name   : ";
            cin.getline(n, 28);
            validName = true;
            for (int i = 0; n[i] != '\0'; i++) {
                if (isdigit(n[i])) {
                    cout << "Invalid name! Please enter a name without numbers.\n";
                    validName = false;
                    break;
                }
            }
        } while (!validName);


        bool validMobile = false;
        do {
            cout << "Enter Mobile Number : ";
            cin.getline(m, 17);
            validMobile = (strlen(m) == 10 && isdigit(m[0]));
            if (!validMobile) {
                cout << "Invalid mobile number! Please enter a 10-digit number.\n";
            }
        } while (!validMobile);

    
        bool validEmail = false;
        do {
            cout << "Enter E-Mail I. D.  : ";
            cin.getline(e, 40);
            size_t atPos = string(e).find('@');
            size_t dotComPos = string(e).find(".com");

            validEmail = (atPos != string::npos && dotComPos != string::npos && dotComPos > atPos);
            if (!validEmail) {
                cout << "Invalid email! Please enter a valid email with '@' and '.com'.\n";
            }
        } while (!validEmail);

    }

    int showData()
    {
        cout << "\n...............PHONE BOOK RECORD...............\n";
        cout << "Sr. No.    : " << srno << endl;
        cout << "Name       : " << n << endl;
        cout << "Mobile No. : " << m << endl;
        cout << "Email ID   : " << e << endl;
    }
};

PhoneBook x;

int NumberSum()
{
    ofstream fout;
    fout.open("PhonBook.dat", ios::out | ios::binary | ios::app);
    x.storeData();
    fout.write((char*)&x, sizeof(x));
    fout.close();
    cout << "\nRecord Saved to File......\n";
}

int Show_Records()
{
    ifstream fin;
    fin.open("PhonBook.dat", ios::out | ios::binary | ios::app);
    while (fin.read((char*)&x, sizeof(x)))
    {
        x.showData();
    }
    fin.close();
    cout << "\nReading of Data File Completed......\n";
}

int SearchWithSerialNumber()
{
    ifstream fin;
    int n, flag = 0;
    fin.open("PhonBook.dat", ios::out | ios::binary | ios::app);
    cout << "Enter Serial Number of Record To Display: ";
    cin >> n;
    while (fin.read((char*)&x, sizeof(x)))
    {
        if (n == x.getSrNo())
        {
            x.showData();
            flag++;
            cout << "\n\n.....Record Found and Displayed......\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in the file....\n";
    cout << "\nReading of Data File Completed......\n";
}

int Record_Deletion()
{
    ifstream fin;
    ofstream fout;
    int n, flag = 0;

    fin.open("PhonBook.dat", ios::in | ios::binary); // Open for input only
    fout.open("temp.dat", ios::out | ios::binary);   // Open for output only

    if (!fin || !fout)
    {
        cout << "Error opening files for deletion.\n";
        return -1; // Indicate failure
    }

    cout << "Enter Serial Number of Record To Delete : ";
    cin >> n;

    while (fin.read((char*)&x, sizeof(x)))
    {
        if (n == x.getSrNo())
        {
            cout << "\nThe Following record is deleted....\n";
            x.showData();
            flag++;
        }
        else
        {
            fout.write((char*)&x, sizeof(x));
        }
    }

    fin.close();
    fout.close();

    if (flag == 0)
    {
        cout << "\nThe Record of Serial Number " << n << " is not in the file....\n";
    }
    else
    {
        cout << "\nReading of Data File Completed......\n";
        remove("PhonBook.dat");
        rename("temp.dat", "PhonBook.dat");
    }
    return 0; 
}


int Update_Record()
{
    fstream fio;
    int n, flag = 0, pos;
    fio.open("PhonBook.dat", ios::out | ios::binary | ios::in);

    cout << "Enter Serial Number of Record To Modify : ";
    cin >> n;
    while (fio.read((char*)&x, sizeof(x)))
    {
        pos = fio.tellg();
        if (n == x.getSrNo())
        {
            cout << "\nThe Following record will be modified....\n";
            x.showData();
            flag++;
            cout << "\nRe-Enter the New Details.....\n";
            x.storeData();
            fio.seekg(pos - sizeof(x));
            fio.write((char*)&x, sizeof(x));
            cout << "\n....Data Modified Successfully....\n";
        }
    }
    fio.close();
    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in the file....\n";
    cout << "\nReading of Data File Completed......\n";
}

void menu()
{
    int ch;
    do
    {
        //clrscr();
        cout << "............................................\n";
        cout << "           PHONE BOOK MANAGEMENT\n";
        cout << "............................................\n\n";
        cout << "::::::::::::::: PROGRAM MENU :::::::::::::::\n";
        cout << "0. Exit\n";
        cout << "1. Enter New Phone Record\n";
        cout << "2. Display All Saved Records\n";
        cout << "3. Search Specific Record\n";
        cout << "4. Delete Specific Record\n";
        cout << "5. Modify Existing Record\n";
        cout << "Enter Your Choice  ";
        cin >> ch;
        //clrscr();
        switch (ch)
        {
        case 1: NumberSum(); break;
        case 2: Show_Records();
            break;
        case 3: SearchWithSerialNumber();
            break;
        case 4: Record_Deletion();
            break;
        case 5: Update_Record();
            break;
        }
        getch();
    } while (ch);
}

int main()
{
    menu();
    return 0;
}
