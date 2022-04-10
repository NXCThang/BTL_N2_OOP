#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
  vector<int> ids;
  int maxSize = 200;


string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *gmtime(&now);
    tstruct.tm_hour += 7;
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

class ParkingTicket
{
private:
    bool statusthe;

public:
    string ticketNumber;
    int ticketId;
    string licenseNumber;
    string parkingspotId;

public:

    static bool checkID(int ticketId, vector<int> ids) // kiem tra id
    {
        if(ids.size() == 0)
        {
            return false;
        }
        for (int i = 0; i <= ids.size(); i++)
        {

            if (ticketId == ids[i])
            {
                return true;
            }
        }
        return false;
    }

    static int createID() // tao id the moi
    {
        int ticketId = (rand() % (999 - 1 + 1)) + 1;
        while (checkID(ticketId, ids) && ids.size() > 0)
        {
            ticketId = (rand() % (999 - 1 + 1)) + 1;
        }
        ids.push_back(ticketId);
        return ticketId;
    }
    string getticketNumber()
    {
        return this->ticketNumber;
    }
    void setticketNumber(string ticketNumber)
    {
        this->ticketNumber = ticketNumber;
    }
    int getticketid()
    {
        return this->ticketId;
    }
    void setticketId(int ticketId)
    {
        this->ticketId = ticketId;
    }
    string getlicenseNumber()
    {
        return this->licenseNumber;
    }
    void setlicenseNumber(string licenseNumber)
    {
        this->licenseNumber = licenseNumber;
    }
    string getparkingspotId()
    {
        return this->parkingspotId;
    }
    void setparkingspotId(string parkingspotId)
    {
        this->parkingspotId = parkingspotId;
    }
};
/* `theravao()` is a class that is used to store the information of the car that is parked. */
class theravao : public ParkingTicket
{
private:
    int id;

public:

    theravao()
    {
        string ticketNumber;
        string licenseNumber;
        string parkingspotId;
        cout << "Nhap thong tin ve xe" << endl;
        cout << "Nhap ID the: ";
        do {
            cin>>id;
            cout<<endl;
            if (checkID(id, ids))
            {
                cout << "ID da ton tai, nhap lai: ";
            }
        }
        while (checkID(id, ids) == true);
        ids.push_back(id);
        this->setticketId(id);
        cout << "Nhap so ve xe: ";
        cin >> ticketNumber;
        cin.ignore(1);
        this->setticketNumber(ticketNumber);
        cout << "Nhap bien so xe: ";
        cin>>licenseNumber;
        cin.ignore(1);
        this->setlicenseNumber(licenseNumber);
        cout << "Nhap vi tri do xe: ";
        cin >> parkingspotId;
        cin.ignore(1);
        this->setparkingspotId(parkingspotId);
    }
};

vector<theravao> dstheravao;

//A class to check and set the status of the, check the time that the car going in or out
class Logs

{
private:
    ParkingTicket parkingticket;
    string timeVao;
    string timeRa;
    bool status;
    bool statusthe;

public:
    Logs(ParkingTicket parkingticket, string timeVao)
    {
        this->parkingticket = parkingticket;
        this->timeVao = timeVao;
        this->timeRa = "xe chua Ra";
        this->status = false;
        this->statusthe = true;
    }
    void diRa()
    {
        this->timeRa = currentDateTime();
        this->status = true;
    }
    int getID()
    {

        return parkingticket.getticketid();
    }
    string getLicensenum()
    {
        return parkingticket.getlicenseNumber();
    }

    string getTimeVao()
    {
        return this->timeVao;
    }
    string getTimeRa()
    {
        return this->timeRa;
    }
    bool getStatus()
    {
        return this->status;
    }
    bool settrue()
    {
        this->statusthe = true;
        cout << "The da duoc mo. \n";
    }
    bool setfalse()
    {
        this->statusthe = false;
        cout << "The da dc khoa. \n";
    }
    bool getstatusthe()
    {
        return this->statusthe;
    }
};

class Barrier{ // Thanh barrier
    protected:
        bool status;
    public:
        Barrier(){
            status = false;
        }
        bool settrue(){
            this->status=true;
            return this->status;
        }
};

class Barriervao: public Barrier{ // Barrier vao ke thua Barrier
    public:
    void in(){
        if(this->status) cout<<"Barrier lan vao da mo! Mot xe dang di vao!!!\n";
        else cout<<"Barrier lan vao dang dong!\n";
    }
};

class Barrierra: public Barrier{ // Barrier ra ke thua Barrier
    public:
    void in(){
        if(this->status) cout<<"Barrier lan ra da mo! Mot xe dang di ra!!!\n";
        else cout<<"Barrier lan ra dang dong!\n";
    }
};
vector<Logs> logs;
// ham xac nhan xe di ra
void ra()
{
    Barrierra b;
    string biensoxe;
    cout << "Nhap bien so xe: ";
    cin >> biensoxe;
    int Id;
    int tg = 0;
    cout << "Nhap ID the: ";
    cin >> Id;

    /* This is checking if the ID of the ticket matches the ID of the ticket in the vector. */
    if (!ParkingTicket::checkID(Id, ids))
    {
        cout << "ID cua the khong ton tai. \n";
        b.in();
    }
    else if (logs.size() > 0)
    {
        /* This is a loop that iterates through the vector of logs. */
        for (int i = 0; i < logs.size(); i++)
        {

            if (Id == logs[i].getID() && logs[i].getstatusthe() == false)
            {
                cout << "The da bi khoa.\n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
                return;
            }

            if (Id == logs[i].getID() && logs[i].getStatus() == false && logs[i].getstatusthe() == true && biensoxe == logs[i].getLicensenum())
            {

                logs[i].diRa();
                cout << "The da duoc mo. \n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
                return;
            }

               /*  ids.erase(ids.begin() + i);
                logs.erase(logs.begin() + i); */
                if (Id == ids[i] && biensoxe == dstheravao[i].licenseNumber)
                {
                b.settrue();
                b.in();
                 logs[i].diRa();
                cout << "Xac nhan xe di ra.\n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
                return;
                }
                else if (biensoxe != dstheravao[i].licenseNumber && i == logs.size() - 1) {
                    cout << "Bien so xe khong dung"<<endl;
                    b.in();
                    cout << "Press Enter to Continue"<<endl;
                }


        }
    }
}
// ham xac nhan xe di vao
void vao()
{
    int Id;

    dstheravao.push_back(theravao());
    ParkingTicket parkingticket;
    /* A loop that iterates through the vector of theravao. */
    for (theravao i : dstheravao)
    {

        /* Checking if the ID of the ticket matches the ID of the ticket in the vector. */
        if (Id == i.getticketid())
        {
            parkingticket = i;
        }
    }
    if (logs.size() < maxSize) {
    logs.push_back(Logs(parkingticket, currentDateTime()));
    cout << "Xac nhan xe di vao.\n";
    }
    else
    {
        cout << "So luong xe da vuot qua gioi han. \n";
    }
    cout << "Press Enter to Continue \n";

    cin.ignore();
}

void danhsach()
{
    cout << "ID ve xe\t\\Bien so xe\t\tGio vao\t\t\t\t\t\t\\Gio ra\n";
    for (int i = 0; i < logs.size(); i++)
    {
        cout << ids[i] << "\t\t" << dstheravao[i].licenseNumber << "\t\t" << logs[i].getTimeVao() << "\t\t\t\t\t\t" << logs[i].getTimeRa() << endl;
    }

    cout << "Press Enter to Continue";
    cin.ignore();
}

void capnhap()
{
    int Id;
    cout << "Nhap Id the can cap nhap: ";
    cin >> Id;
    if (!ParkingTicket::checkID(Id, ids))
    {
        cout << "ID the khong ton tai. \n";
    }
    else if (logs.size() > 0)
    {
        for (int i = 0; i <= logs.size(); ++i)
        {
            if (Id == logs[i].getID())
            {
                if (logs[i].getstatusthe() == true)
                {
                    logs[i].setfalse();
                }
                else
                {
                    logs[i].settrue();
                }
            }
        }
    }
    cout << "Press Enter to Continue \n";
    cin.ignore();
};

//Kiem soat dieu khien ra vao
class ioReport
{
public:
    int carIn = 0;
    int CarOut = 0;
    int remainingCar = 0;
    //ham kiem tra so xe con lai trong bai
    void checkRemain()
    {
        remainingCar = carIn - CarOut;
    };
    //ham bao cao so xe ra, vao va con lai trong bai
    void statusReport()
    {
        cout << "So xe vao: " << carIn << endl;
        cout << "So xe ra: " << CarOut << endl;
        cout << "So xe con lai: " << remainingCar<< endl;
    };
};
int main()
{
    ioReport IRT;
    int total = 0;
    int input;
    while (true)
    {
        cout << "1- Xe Ra \n";
        cout << "2- danh sach xe ra vao\n";
        cout << "3- cap nhap trang thai the\n";
        cout << "4- Xe vao\n";
        cout << "5- Thong ke\n";
        cout << "6- Thoat\n";
        cin >> input;
        cin.ignore(1);

        switch (input)
        {
        case 1:
            ra();
            IRT.CarOut++;
            IRT.remainingCar--;
            break;
        case 2:
            danhsach();
            break;
        case 3:
            capnhap();
            break;
        case 4:
            vao();
            IRT.carIn++;
            break;
        case 5:
            IRT.checkRemain();
            IRT.statusReport();
            break;
        case 6:
            break;
        }
    }
}
