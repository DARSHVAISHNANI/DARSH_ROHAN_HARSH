
/*this code contains books data stored in file name book.data which is already uploaded on git.
it also has student data stored in file name student.data which is also uploaded on git
for running this program it is pre-requisite
here by default the password is admin*/
#include <fstream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <iostream>

using namespace std;

class book
{
    char book_number[30];
    char book_name[50];
    char author_name[20];

public:
    void create_book()
    {
        cout << "\nEnter The Book Number: ";
        cin >> book_number;
        cout << "\nEnter The Name of The Book: ";
        cin.ignore();
        cin.getline(book_name, 50);
        cout << "\nEnter The Author's Name: ";
        cin.ignore();
        cin.getline(author_name, 50);
        cout << "\t\t\n\nBook Created Successfully...";
    }

    void show_book()
    {
        cout << "\nBook Number: " << book_number;
        cout << "\nBook Name: " << book_name;
        cout << "\nAuthor's Name: " << author_name;
    }
    void modify_book()
    {
        cout << "\nBook number : " << book_number;
        cout << "\nModify Book Name : ";
        cin.ignore();
        cin.getline(book_name, 50);
        cout << "\nModify Author's Name: ";
        cin.ignore();
        cin.getline(author_name, 50);
    }
    char *getbooknumber()
    {
        return book_number;
    }
    void report()
    {
        cout << book_number << setw(30) << book_name << setw(30) << author_name << endl;
    }
};

class student
{
    char ID_number[20];
    char Student_name[20];
    char stbno[6];
    int token;

public:
    void create_student()
    {
        cout << "\nEnter The ID Number ";
        cin >> ID_number;
        cout << "\n\nEnter The Name of The Student: ";
        cin >> Student_name;
        token = 0;
        stbno[0] = '/0';
        cout << "\t\t\n\nStudent Record Created Successfully...";
    }
    void show_student()
    {
        cout << "\nID Number: " << ID_number;
        cout << "\nStudent Name: ";
        puts(Student_name);
        cout << "\nNo of Book issued: " << token;
        if (token == 1)
            cout << "\nBook No " << stbno;
    }
    void modify_student()
    {
        cout << "\nID Number: " << ID_number;
        cout << "\nModify Student Name: ";
        cin.ignore();
        cin.getline(Student_name, 50);
    }
    char *get_ID_number()
    {
        return ID_number;
    }
    char *retstbno()
    {
        return stbno;
    }
    int rettoken()
    {
        return token;
    }
    void addtoken()
    {
        token = 1;
    }
    void resettoken()
    {
        token = 0;
    }
    void getstbno(char t[])
    {
        strcpy(stbno, t);
    }
    void report()
    {
        cout << "\t" << ID_number << setw(20) << Student_name << setw(10) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;
void write_book()
{
    system("cls");
    int more_or_main;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char *)&bk, sizeof(book));
        cout << "\nPress 1 to add more books.";
        cout << "\nPress 2 to return to main menu.\n";
        cout << "Enter: ";
        cin >> more_or_main;
    } while (more_or_main == 1);
    fp.close();
}
void write_student()
{
    system("cls");
    int more_or_main;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char *)&st, sizeof(student));
        cout << "\nPress 1 to add more students.";
        cout << "\nPress 2 to return to main menu.\n";
        cout << "Enter: ";
        cin >> more_or_main;
    } while (more_or_main == 1);
    fp.close();
}
void display_a_book(char n[])
{
    system("cls");
    cout << "\nBOOK DETAILS\n";
    int check = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.getbooknumber(), n) == 0)
        {
            bk.show_book();
            check = 1;
        }
    }
    fp.close();
    if (check == 0)
        cout << "\n\nBook does not exist";
    getch();
}
void display_a_student(char n[])
{
    system("cls");
    cout << "\nSTUDENT DETAILS\n";
    int check = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if ((strcmpi(st.get_ID_number(), n) == 0))
        {
            st.show_student();
            check = 1;
        }
    }
    fp.close();
    if (check == 0)
        cout << "\n\nStudent does not exist";
    getch();
}
void modify_book()
{
    system("cls");
    char n[20];
    int found = 0;
    cout << "\n\n\tMODIFY BOOK";
    cout << "\n\n\tEnter The book number: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmpi(bk.getbooknumber(), n) == 0)
        {
            bk.show_book();
            cout << "\nEnter The New Details of book" << endl;
            bk.modify_book();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(book));
            cout << "\n\n\t Record Updated Successfully...";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}
void modify_student()
{
    system("cls");
    char n[20];
    int found = 0;
    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter Student's ID number: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.get_ID_number(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter The New Details of student" << endl;
            st.modify_student();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\n\n\t Record Updated Successfully...";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}

void intro()
{
    system("color 03");
    system("cls");
    cout<<"\t\t********* WELCOME TO LIBRARY MANAGEMENT SYSTEM : ********* "<<endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(6) << (char)004 << setw(3) << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(1) << (char)004 << setw(4) << (char)004 << setw(1) << (char)004 << setw(3) << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(2) << (char)004 << setw(2) << (char)004 << setw(2) << (char)004 << setw(3) << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(3) << (char)004 << setw(3) << (char)004 << setw(3) << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(6) << (char)004 << setw(5) << "          " << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(11) << (char)004 << setw(6) << (char)004 << setw(5) << "          " << (char)004 << endl;
    cout << "\t\t\t" << (char)004 << setw(2) << (char)004 << setw(2) << (char)004 << setw(2) << (char)004 << setw(2) << (char)004 << setw(3) << (char)004 << setw(6) << (char)004 << setw(3) << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << " " << (char)004 << endl;
}
void book_menu()
{
    int option;
    for (int i = 0; i < 70; i++)
    {
        cout << "*";
    }
    cout << endl
         << "\t\t*********** WELCOME TO BOOK EDITION : ***********" << endl;
    cout << "\n\t\t1). Press 1 :: CREATE BOOKS" << endl;
    cout << "\n\t\t2). Press 2 :: DISPLAY ALL BOOKS" << endl;
    cout << "\n\t\t3). Press 3 :: DISPLAY SPECIFIC BOOK" << endl;
    cout << "\n\t\t4). Press 4 :: MODIFY BOOKS" << endl;
    cout << "\n\t\t5). Press 5 :: DELETE BOOKS" << endl;
    cout << "\n\t\t6). Press 6 :: GO BACK TO MAIN MENU" << endl;

    cout << "\n\t\tOption: ";
    cin >> option;
    switch (option)
    {
    case 1:
        system("cls");
        write_book();
        break;
    case 2:
        display_allb();
        break;
    case 3:
        char num[20];
        system("cls");
        cout << "\n\n\tPlease Enter The book No. ";
        cin >> num;
        display_a_book(num);
        break;
    case 4:
        modify_book();
        break;
    case 5:
        delete_book();
        break;
    case 6:
        system("cls");
        break;
    default:
        cout << "\a";
    }
}
void student_menu()
{
    int option;
    for (int i = 0; i < 70; i++)
        cout << "*";
    cout << endl
         << "\t\t*********** WELCOME TO STUDENT EDITION : ***********" << endl;
    cout << "\n\t\t1). Press 1 :: CREATE STUDENT RECORD" << endl;
    cout << "\n\t\t2). Press 2 :: DISPLAY ALL STUDENTS RECORD" << endl;
    cout << "\n\t\t3). Press 3 :: DISPLAY SPECIFIC STUDENT RECORD" << endl;
    cout << "\n\t\t4). Press 4 :: MODIFY STUDENT RECORD" << endl;
    cout << "\n\t\t5). Press 5 :: DELETE STUDENT RECORD" << endl;
    cout << "\n\t\t6). Press 6 :: GO BACK TO MAIN MENU\n"<< endl;
    for (int i = 0; i < 70; i++)
        cout << "*";
    cout << "\n\t\tOption: ";
    cin >> option;
    switch (option)
    {
    case 1:
        system("cls");
        write_student();
        break;
    case 2:
        system("cls");

        display_all_students();
        break;
    case 3:
        char num[20];
        system("cls");
        cout << "\n\n\tPlease Enter The ID Number: ";
        cin >> num;
        display_a_student(num);
        break;
    case 4:
        system("cls");
        modify_student();
        break;
    case 5:
        system("cls");
        delete_student();
        break;
    case 6:
        break;
    default:
        cout << "\a";
    }
}
int main()
{
    string pass;

    for (int i = 0; i < 5; i++)
    {
        cout << "Enter the password : ";
        cin >> pass;

        if (pass == "admin")
        {
            int option = 0;
            for (;;)
            {
                intro();

                for (int i = 0; i < 70; i++)
                    cout << "*";
                cout << endl
                     << "\t\t*********** WELCOME ADMIN : ***********" << endl;
                cout << "\n\t\t1). Press 1 :: ISSUE BOOKS" << endl;
                cout << "\n\t\t2). Press 2 :: RETURN BOOKS" << endl;
                cout << "\n\t\t3). Press 3 :: UPDATE STUDENT RECORDS" << endl;
                cout << "\n\t\t4). Press 4 :: UPDATE BOOK RECORDS" << endl;
                cout << "\n\t\t5). Press 5 :: TO EXIT" << endl;
                for (int i = 0; i < 70; i++)
                    cout << "*";
                cout << "\n\t\tOption: ";
                cin >> option;
                switch (option)
                {
                case 1:
                    system("cls");
                    issue_book();
                    break;
                case 2:
                    system("cls");
                    book_return();
                    break;
                case 3:
                    system("cls");
                    student_menu();
                    break;
                case 4:
                    system("cls");
                    book_menu();
                    break;
                case 5:
                    exit(0);
                    break;
                default:
                    cout << "\a";
                    exit(0);
                }
            }
        }
        else
        {
            if (i == 4)
                cout << "The system has been locked " << endl;
            else
            {
                cout << "Wrong password" << endl;
                cout << "Now you have " << 4 - i << endl;
            }
        }
    }
}
