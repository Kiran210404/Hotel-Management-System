#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

void login()
{
    char id[5],pass[7];
    cout<<"\n\n\t\t\t\tusername : ";
    cin>>id;
    cout<<"\n\t\t\t\tpassword : ";
    cin>>pass;
    cout<<"\n\n\t";
    cout<<"\t";
    if(strcmp(id,"AK0406")==0 && strcmp(pass,"Ak2115")==0)
        cout<<"\n\n\t\t\t  !!!Login Successfull!!!";
    else {
        cout<<"\n\n\t\t\t!!!INVALID CREDENTIALS!!!\n\t\t\tTRY AGAIN";
        login();
        getch();
    }
}

class hotelmanagement
{
    public:
    virtual void menu()=0;
};

class hotel {
    private:
            int room_no;
            char name[30];
            char address[50];
            char phone[15];
            int days;
            float fare;
            static int total_rooms;
            
    public:
    static void head()
{
    cout<<"\n*******************************************************************";
    cout<<"\t";
    cout<<" \n\t\t\tAK Group of Hotels";
    cout<<"\t";
    cout<<"\n*******************************************************************";
}
void menu()
    {
    int choice;
    while(choice!=5) {
        hotel::head();
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\t\t\t\t* MAIN MENU *";
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\n\n\t\t\t1.Book A Room";
        cout<<"\n\t\t\t2.Customer Record";
        cout<<"\n\t\t\t3.Rooms Allotted";
        cout<<"\n\t\t\t4.Edit Record";
        cout<<"\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;
        switch(choice) {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: rooms();
                    break;
            case 4: edit();
                    break;
            case 5: break;
            default: {
                cout<<"\n\n\t\t\tWrong choice.....!!!";
                cout<<"\n\t\t\tPress any key to continue....!!";
                getch();
            }
        }
    }
}       //to display the main menu
            void add();             //to book a room
            void display();         //to display the customer record
            void rooms();           //to display allotted rooms
            void edit();            //to edit the customer record
            int check(int);         //to check room status
            void modify(int);       //to modify the record
            void delete_rec(int);   //to delete the record
};
 int hotel:: total_rooms=100;

void hotel::add()
{
     hotel:: head();
    int r,flag;
    ofstream fout("Record.dat",ios::app |ios::binary);
    cout<<"\n Enter Customer Details";
    cout<<"\n ----------------------";
    cout<<"\n\n Room no: ";
    cin>>r;
    flag=check(r);
    if(flag)
        cout<<"\n Sorry..!!!Room is already booked";
    else {
        room_no=r;
        cout<<" Name: ";
         cin.ignore(0);
        cin>>name;
        cout<<" Address: ";
        // cin.ignore(10);
        cin>>address;
        cout<<" Phone No: ";
        // gets(phone);
        // cin.ignore(10);
        cin>>phone;
        cout<<" No. of Days for a stay: ";
        cin>>days;
        fare=days*1000;                     
                                            
        fout.write((char*)this,sizeof(hotel));
        cout<<"\n Room is booked...!!!";
    }

    cout<<"\n Press any key to continue.....!!";
    getch();
    fout.close();
}
void hotel::display() {
    hotel::head();
    ifstream fin("Record.dat",ios::in);
    int r,flag;
    cout<<"\n Enter room no: ";
    cin>>r;
    while(!fin.eof()) {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r) {
            // hotel::head();
            cout<<"\n Customer Details";
            cout<<"\n ----------------";
            cout<<"\n\n Room no: "<<room_no;
            cout<<"\n Name: "<<name;
            cout<<"\n Address: "<<address;
            cout<<"\n Phone no: "<<phone;
            cout<<"\n Days: "<<days;
            cout<<"\n Total Fare: "<<fare;
            flag=1;
        }
    }
    if(flag==0)
        cout<<"\n Sorry Room no. not found or vacant....!!";
    cout<<"\n\n Press any key to continue....!!";
    getch();
    fin.close();
}
void hotel::rooms() {
    hotel::head();
    ifstream fin("Record.dat",ios::binary |ios::in );
    cout<<"\n\t\t\t    List Of Rooms Allotted";
    cout<<"\n\t\t\t    ----------------------";
    while(!fin.eof()) {
        fin.read((char*)this,sizeof(hotel));
        cout<<"\n Room no: "<<room_no<<"\n Name: "<<name;
        cout<<"\n Address: "<<address<<"\n Phone: "<<phone;
        cout<<"\n Days: "<<days<<"\n Total: "<<fare;
        cout<<"\n------------------------------------";
    }
    cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
    getch();
    fin.close();
}

int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::binary |ios::in);

    if (!fin) {
        cout << "Error opening file" << endl;
        return flag;
    }

    hotel tempHotel; // Temporary variable to read data into the file

    while (fin.read((char*)&tempHotel, sizeof(hotel))) {
        if (tempHotel.room_no == r) {
            flag = 1;
            break;
        }
    }

    fin.close();
    return flag;
}

void hotel::modify(int r) {
   hotel::head();
    long position;
    int flag = 0;

    fstream file("Record.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Error opening file" << endl;
        return;
    }

    hotel tempHotel;

    while (file.read((char*)&tempHotel, sizeof(hotel))) {
        position = file.tellg();

        if (tempHotel.room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin.ignore(); // Ignore any previous newline in the input buffer
            cin.getline(tempHotel.name, sizeof(tempHotel.name)); // Assuming name is a char array
            cout << " Address: ";
            cin.getline(tempHotel.address, sizeof(tempHotel.address));
            cout << " Phone no: ";
            cin.getline(tempHotel.phone, sizeof(tempHotel.phone));
            cout << " Days: ";
            cin >> tempHotel.days;

            tempHotel.fare = tempHotel.days * 900;

            file.seekp(position - sizeof(hotel)); // Move the write pointer back to the beginning of the record
            file.write((char*)&tempHotel, sizeof(hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        cout << "Record not found" << endl;
    }

    file.close();
}

void hotel::delete_rec(int r)
 {
    hotel::head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::binary |ios::in);
    ofstream fout("temp.dat", ios::out | ios::binary);

    if (!fin || !fout) 
    {
        cout << "Error opening file" << endl;
        return;
    }

    hotel tempHotel;

    while (fin.read((char*)&tempHotel, sizeof(hotel))) {
        if (tempHotel.room_no == r) {
            cout << "\n Name: " << tempHotel.name;
            cout << "\n Address: " << tempHotel.address;
            cout << "\n Phone No: " << tempHotel.phone;
            cout << "\n Days: " << tempHotel.days;
            cout << "\n Total Fare: " << tempHotel.fare;
            cout << "\n\n Do you want to delete this record(y/n): ";
            cin >> ch;
            if (ch == 'n') {
                fout.write((char*)&tempHotel, sizeof(hotel));
            }
            flag = 1;
        } else {
            fout.write((char*)&tempHotel, sizeof(hotel));
        }
    }

    fin.close();
    fout.close();

    if (flag == 0) {
        cout << "\n Sorry room no. not found or vacant...!!";
    } else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
        cout << "\n Record deleted successfully!";
    }
}

void hotel::edit() 
{
    hotel::head();
    int choice,r;
    cout<<"\n EDIT MENU";
    cout<<"\n ---------";
    cout<<"\n\n 1.Modify Customer Record";
    cout<<"\n 2.Delete Customer Record";
    cout<<"\n Enter your choice: ";
    cin>>choice;

    hotel::head();
    cout<<"\n Enter room no: " ;
    cin>>r;
    switch(choice) {
        case 1: modify(r);
                break;
        case 2: delete_rec(r);
                break;
        default: cout<<"\n Wrong Choice.....!!";
    }
    cout<<"\n Press any key to continue....!!!";
    getch();
}

int main()
{
    hotel h;
    cout<<"\n\n\n";
    cout<<"\n\n\n\t\t\tPress any key to continue....!!";

    getch();
    h.head();
    login();
    h.menu();
    getch();
    
    return 0;
}
