#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include<iomanip>
using namespace std;

vector<string> ids;

std::string currentdateTime()
{ // tao chuoi ngay gio
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];

    tstruct = *gmtime(&now);
    tstruct.tm_hour += 7;
    strftime(buf, sizeof(buf), "%Y/%m/%d     %X", &tstruct);

    return buf;
};

struct HOUR_MIN_SEC
{ // Tao struct Gio,phut,giay
    int Hour;
    int Min;
    int Sec;
};

struct HOUR_MIN_SEC currentHourTime()
{ // Tao ham tra ve Struct HOUR_MIN_SEC
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);
    HOUR_MIN_SEC h;

    h.Hour = localTime->tm_hour;
    h.Min = localTime->tm_min;
    h.Sec = localTime->tm_sec;
    // std::cout<<h.Hour<<":"<<h.Min<<":"<<h.Sec<<std::endl;
    return h;
}

bool isNumber(std::string s) // kiem tra xem kieu co phai la so nguyen
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false) // kiem tra tung phan tu trong string co phai so nguyen
            return false;

    return true;
}

class Revenue
{ // class Doanh thu
public:
    static int revenue; // Doanh thu(revenue)
public:
    static int getRevenue()
    { // Tra ve gia tri Doanh Thu
        return revenue;
    }
    static void update(int money)
    { // cap nhat gia tri Doanh Thu
        revenue += money;
    }
    friend void sale(int);
};

int Revenue::revenue = 0;

class Hoadon
{ // class Hoa Don
private:
    int PhiGuiXe = 0;
    int TienKhachTra = 0;
    int TienThua = 0;
    std::string CurTime;

public:
    void InHoaDon(string biensoxe, string Id)
    {                                            // In Hoa Don
        std::string CurTime = currentdateTime(); // In thoi gian hien tai
        std::cout << "Hoa Don: " << std::endl;
        std::cout << CurTime << std::endl;
        std::cout << "Phi Gui Xe: " << PhiGuiXe << " dong" << std::endl;
        std::cout << "Bien so xe: " << biensoxe << std::endl;
        std::cout << "ID the: " << Id << std::endl;
        std::cout << "Tien Khach Tra: " << TienKhachTra << " dong" << std::endl;
        std::cout << "Tien Tra Lai:  " << TienKhachTra - PhiGuiXe << " dong" << std::endl;
    }
    int Inp()
    { // Nhap Tien Khach Tra
        std::cout << "Tien Khach Dua: ";
        std::string str;
        std::cin >> str;
        if (!isNumber(str))
        {
            std::cout << "Khong hop le. Vui long nhap lai." << std::endl; // kiem tra so nhap vao co phai la so nguyen
            return 1;
        }
        if (check(str))
        {
            std::cout << "Tien khach dua khong du. Vui long tra them!" << std::endl; // kiem tra so tien khach tra co du hay khong
            return 1;
        }
        TienKhachTra = std::stoi(str, nullptr, 10);
        return 0;
    }
    void setPhiGuiXe(int set)
    { // Dat phi gui xe ( phan nay co the tuy chinh them de thay doi gia gui xe theo dieu kien nhat dinh)
        PhiGuiXe = set;
    }
    int check(std::string str)
    {
        if (std::stoi(str) >= PhiGuiXe)
            return 0;
        else
            return 1;
    }
    friend void sale(int);
};

void sale(int money)
{ // cap nhat Doanh thu
    Revenue::update(money);
};

void inHoaDon(string biensoxe, string Id)
{
    system("cls");
    Hoadon *temp = new Hoadon; // tao hoa don moi
    int ticket_price = 10000;
    HOUR_MIN_SEC hour = currentHourTime(); // lay ngay gio hien tai
    if ((hour.Hour > 18) || (hour.Hour == 18 && hour.Min >= 30))
        ticket_price = 20000; // Dat phi gui xe
    temp->setPhiGuiXe(ticket_price);
    while (temp->Inp())
    { // Nhap tien khach tra
    }
    temp->InHoaDon(biensoxe, Id); // In Hoa don
    cout << endl;
    sale(ticket_price); // Tang danh thu len
    delete temp;
}

// extern void INHOADONVATONGDOANHTHU();

class ParkingTicket
{
private:
    bool statusthe;

public:
    string ticketId;
    string licenseNumber;
    string parkingspotId;

public:
    static bool checkID(string ticketId, vector<string> ids) // kiem tra id
    {
        if (ids.size() == 0)
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

    static string createID() // tao id the moi
    {
        int temp = (rand() % (999 - 1 + 1)) + 1;
        string ticketId = to_string(temp);

        while (checkID(ticketId, ids) && ids.size() > 0)
        {
            temp = (rand() % (999 - 1 + 1)) + 1;
            ticketId = to_string(temp);
        }
        ids.push_back(ticketId);
        return ticketId;
    }
    string getticketid()
    {
        return this->ticketId;
    }
    void setticketId(string ticketIdString)
    {
        this->ticketId = ticketIdString;
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
vector<string> checkBienSoXe;
vector<string> checkVitriDoXe;
class theravao : public ParkingTicket
{
private:
    string id;

public:
    theravao()
    {
        string licenseNumber;
        string parkingspotId;
        cout << "Nhap thong tin ve xe" << endl;
        cout << "Nhap ID the: ";
        do {
            cin>>id;
            if (checkID(id, ids))
            {
                cout << "ID da ton tai, nhap lai: ";
            }
        }
        while (checkID(id, ids) == true);
        ids.push_back(id);
        this->setticketId(id);
        cout << "Nhap bien so xe: ";
        int k;
        do{
            cin >> licenseNumber;
            k=1;
            for(int i=0;i<checkBienSoXe.size();i++){
                if(checkBienSoXe[i]==licenseNumber) {
                    cout << "Trung bien so xe, nhap lai: ";
                    k=0;
                }
            }
        }while(!k);

        cin.ignore(1);
        this->setlicenseNumber(licenseNumber);
        checkBienSoXe.push_back(licenseNumber);
        cout << "Nhap vi tri do xe: ";
        do{
            cin>>parkingspotId;
            k=1;
            for(int i=0;i<checkVitriDoXe.size();i++){
                if(checkVitriDoXe[i]==parkingspotId){
                    cout<<"Trung vi tri do xe, nhap lai: ";
                    k=0;
                }
            }
        }while(!k);
        this->setparkingspotId(parkingspotId);
        checkVitriDoXe.push_back(parkingspotId);
    }
};

vector<theravao> dstheravao;

// A class to check and set the status of the, check the time that the car going in or out
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
        this->timeRa = currentdateTime();
        this->status = true;
    }

    string getID()
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
    void settrue()
    {
        this->statusthe = true;
        cout << "The da duoc mo. \n";
    }
    void setfalse()
    {
        this->statusthe = false;
        cout << "The da dc khoa. \n";
    }
    bool getstatusthe()
    {
        return this->statusthe;
    }
};

class Barrier
{ // Thanh barrier
protected:
    bool status;

public:
    Barrier()
    {
        status = false;
    }
    bool settrue()
    {
        this->status = true;
        return this->status;
    }
};

class Barriervao : public Barrier
{ // Barrier vao ke thua Barrier
public:
    void in()
    {
        if (this->status)
            cout << "Barrier lan vao da mo! Mot xe dang di vao!!!\n";
        else
            cout << "Barrier lan vao dang dong!\n";
    }
};

class Barrierra : public Barrier
{ // Barrier ra ke thua Barrier
public:
    void in()
    {
        if (this->status)
            cout << "Barrier lan ra da mo! Mot xe dang di ra!!!\n";
        else
            cout << "Barrier lan ra dang dong!\n";
    }
};
vector<Logs> logs;
// ham xac nhan xe di ra
bool ra()
{
    Barrierra b;
    string biensoxe;
    string Id;
    cout << "Nhap ID the: ";
    cin >> Id;
    cout << "Nhap bien so xe: ";
    cin >> biensoxe;

    /* This is checking if the ID of the ticket matches the ID of the ticket in the vector. */
    if (!ParkingTicket::checkID(Id, ids))
    {
        cout << "ID cua the khong ton tai. \n";
        b.in();
    }
    else if (logs.size() > 0)
    {
        /* This is a loop that iterates through the vector of logs. */
        for (int i = 0; i <= logs.size(); i++)
        {

            if (Id == ids[i] && logs[i].getstatusthe() == false)
            {
                cout << "The da bi khoa.\n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
            }

            if (Id == ids[i] && logs[i].getStatus() == false && logs[i].getstatusthe() == true && biensoxe == logs[i].getLicensenum())
            {
                logs[i].diRa();
                cout << "The da duoc mo. \n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
            }
            if (Id == ids[i] && biensoxe == dstheravao[i].licenseNumber)
            {   
                b.settrue();
                logs[i].diRa();
                b.in();
                inHoaDon(biensoxe,Id);
                cout << "Xac nhan xe di ra.\n";
                cout << "Press Enter to Continue \n";
                cin.ignore();
                return 1;
            }
            else if (biensoxe != dstheravao[i].licenseNumber && i == logs.size() - 1) {
                    cout << "Bien so xe khong dung"<<endl;
                    b.in();
                    cout << "Press Enter to Continue"<<endl;
            }
        }
    }
    return 0;
}
// ham xac nhan xe di vao
void vao()
{
    string Id;
    string biensoxe;
    Barriervao b;
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

    b.settrue();
    b.in();
    logs.push_back(Logs(parkingticket, currentdateTime()));
    cout << "Xac nhan xe di vao.\n";
    cout << "Press Enter to Continue \n";
    return;
}

void danhsach()
{
    cout <<setw(10)<<  "ID ve xe" << setw(20)<< "Bien so xe" <<setw(30)<< "Gio vao" <<setw(30) <<"Gio ra\n";
    for (int i = 0; i < logs.size(); i++)
    {
        cout << setw(10)<< ids[i] << setw(20) << dstheravao[i].licenseNumber << setw(30) << logs[i].getTimeVao() << setw(30) << logs[i].getTimeRa() << endl;
    }
}

void capnhap()
{
    string Id;
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
            if (Id == ids[i])
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
};

// Kiem soat dieu khien ra vao
class ioReport
{
public:
    int carIn = 0;
    int CarOut = 0;
    int remainingCar = 0;
    // ham kiem tra so xe con lai trong bai
    void checkRemain(vector<theravao> dstheravao)
    {
        remainingCar = carIn - CarOut;
    };
    // ham bao cao so xe ra, vao va con lai trong bai
    void statusReport()
    {
        cout << "So xe vao: " << carIn << endl;
        cout << "So xe ra: " << CarOut << endl;
        cout << "So xe con lai: " << remainingCar << endl;
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
        cout << "7- In Tong Doanh Thu\n";
        cout<<"Lua chon: ";
        string t;
        cin>>t;
        if (isNumber(t)) input=stoi(t);
        cin.ignore();
        switch(input){
            case 1:
            {
                if(ra()){
                    IRT.CarOut++;
                    IRT.remainingCar--;
                }
                break;
            }
            case 2:
            {
                danhsach();
                break;
            }
            case 3:
            {
                capnhap();
                break;
            }
            case 4:
            {
                vao();
                IRT.carIn++;
                break;
            }
            case 5:
            {
                IRT.checkRemain(dstheravao);
                IRT.statusReport();
                break;
            }
            case 6:{
                return 0;
            }
            case 7:{
                 cout << "Tong doanh thu: " << Revenue::getRevenue() << " dong" << endl;
            }
            default: 
            {
                cout<<"\nVui long nhap lai!!\n";
            }
        }
        
    }
}
