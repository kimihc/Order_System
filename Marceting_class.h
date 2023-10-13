#pragma once

#include <iomanip>
#include <io.h>
#include <fcntl.h>

void Line(int a)
{
    for (int i = 0; i < a; i++)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"─";
        _setmode(_fileno(stdout), _O_TEXT);
    }
}

void LineUp()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"│";
    _setmode(_fileno(stdout), _O_TEXT);
}

void LineUpUgol(int a)
{
    if (a == 1)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"┌";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    else if (a == 2)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"└";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    else if (a == 3)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"┐";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    else if (a == 4)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"┘";
        _setmode(_fileno(stdout), _O_TEXT);
    }
}

class Service
{
protected:
    string service_name;
    string description;
    float price;

public:
    Service()
    {
        service_name = "undefined";
        description = "undefined";
        price = 0;
    }

    Service(string service_name, string description, float price)
    {
        this->service_name = service_name;
        this->description = description;
        this->price = price;
    }

    Service(const Service& service)
    {
        service_name = service.service_name;
        description = service.description;
        price = service.price;
    }

    virtual void display_info(int service_number) = 0;
    virtual void set_info() = 0;
};

class MarketingService : public Service
{
private:
	string type_marketing;

public:
	MarketingService()
	{
        type_marketing = "undefined";
	}

    MarketingService(const MarketingService& service)
    {
        type_marketing = service.type_marketing;
    }

    void set_info() override
    {
        cout << "Введите название услуги: ";
        getchar();
        getline(cin, this->service_name);
        cout << "Введите тип услуги: ";
        getline(cin, this->type_marketing);
        cout << "Введите описание услуги: ";
        getline(cin, this->description);
        cout << "Введите цену за услугу: ";
        cin >> this->price;
        getchar();
    }

    void display_info(int service_number) override
    {
       /* cout << "Название услуги: " << service_name << endl;
        cout << "Тип услуги: " << type_marketing << endl;
        cout << "Описание: " << description << endl;
        cout << "Цена: " << price << endl;*/
        LineUp();
        Line(154);
        LineUp();
        cout << endl;
        LineUp();
        cout << left << setw(2) << service_number;
        LineUp();
        cout << left << setw(27) << service_name;
        LineUp(); 
        cout << left << setw(31) << type_marketing;
        LineUp();
        cout << left << setw(75) << description;
        LineUp(); 
        cout << left << setw(12) << price << right << setw(3) << "BYN";
        LineUp();
    }


    void setTypeMarketing(string type_marketing)
    {
        this->type_marketing = type_marketing;
    }

    string getTypeMarketing()
    {
        return type_marketing;
    }

    void setServiceName(string service_name) 
    {
        this->service_name = service_name;
    }

    string getServiceName()
    {
        return service_name;
    }

    void setPrice(float price) {
        this->price = price;
    }

    float getPrice()
    {
        return price;
    }

    void SetDescription(string description)
    {
        this->description = description;
    }

    string GetDescription()
    {
        return description;
    }

};

class Person
{
protected:
    string name;
    string surname;
    string address;
public:
    Person()
    {
        name = "underfined";
        surname = "underfinded";
        address = "Underfined";
    }

    string GetName()
    {
        return name;
    }

    void SetName(string name)
    {
        this->name = name;
    }

    virtual void SetPersonal_data() = 0;
    virtual void Display_contact() = 0;

};

class Manager : virtual public Person
{
private:
    SmartPointer<MarketingService> offeredServices;
    int offeredServicesCount;

public:
    Manager()
    {
        offeredServicesCount = 0;
        offeredServices = nullptr;
    }

    int GetSetnumberService()
    {
        return offeredServicesCount;
    }

    void SetnumberAllService(int offeredServicesCount)
    {
        this->offeredServicesCount = offeredServicesCount;
    }

    int GetSetnumberAllService()
    {
        return offeredServicesCount;
    }

    SmartPointer<MarketingService> GetServices()
    {
        return offeredServices;
    }

    void SetPersonal_data() override
    {
        cout << "Введите фамилию: ";
        cin >> this->surname;
        cout << "Введите имя: ";
        cin >> this->name;
    }

    void Display_contact() override
    {
        cout << "Фамилия: " << surname << endl;
        cout << "Имя: " << name << endl;
    }

    void addService()
    {
        SmartPointer<MarketingService> newServices(new MarketingService[offeredServicesCount + 1]);

        for (int i = 0; i < offeredServicesCount; ++i)
        {
            newServices[i] = offeredServices[i];
        }

        newServices[offeredServicesCount].set_info();

        ++offeredServicesCount;

        offeredServices = newServices;
    }



    void displayServices()
    {
        LineUpUgol(1);
        Line(154);
        LineUpUgol(3);
        cout << endl;
        LineUp();
        cout << left << setw(30) << "        Название услуги";
        LineUp();
        cout << left << setw(31) << "           Тип услуги";
        LineUp();
        cout << left << setw(75) << "                                  Описание";
        LineUp();
        cout << left << setw(15) << "     Цена";
        LineUp();
        cout << endl;

        for (int i = 0; i < offeredServicesCount; ++i)
        {
            offeredServices[i].display_info(i + 1);
            cout << endl;
        }
        LineUpUgol(2);
        Line(154);
        LineUpUgol(4);
        cout << endl;
    }

    void deleteServices()
    {
        int num;
        cout << "Введите номер услуги которую хотите оменить: ";
        cin >> num;

        for (int i = num - 1; i < offeredServicesCount - 1; i++)
        {
            offeredServices[i] = offeredServices[i + 1];
        }

        offeredServicesCount--;

        SmartPointer<MarketingService> newServices(new MarketingService[offeredServicesCount]);

        for (int i = 0; i < offeredServicesCount; ++i)
        {
            newServices[i] = offeredServices[i];
        }

        offeredServices = newServices;
    }
};

class Customer : virtual public Person
{
private:
    int numberAllService;
    SmartPointer<MarketingService> allServices;
    SmartPointer<MarketingService> orderedServices;
    int orderedServicesCount;

public:
    Customer()
    {
        orderedServicesCount = 0;
        orderedServices = nullptr;
        allServices = nullptr;
        numberAllService = 0;
    }

    void SetnumberAllService(int numberAllService)
    {
        this->numberAllService = numberAllService;
    }

    int GetSetnumberAllService()
    {
        return numberAllService;
    }

    int GetSetnumberService()
    {
        return orderedServicesCount;
    }

    void SetServices(SmartPointer<MarketingService> Services)
    {
            SmartPointer<MarketingService> newService(new MarketingService[numberAllService + 1]);

            for (int i = 0; i < numberAllService; ++i)
            {
                newService[i] = Services[i];
            }

            allServices = newService;
    }

    int GetServices()
    {
        LineUpUgol(1);
        Line(154);
        LineUpUgol(3);
        cout << endl;
        LineUp();
        cout << left << setw(2) << "№";
        LineUp();
        cout << left << setw(27) << "        Название услуги";
        LineUp();
        cout << left << setw(31) << "           Тип услуги";
        LineUp();
        cout << left << setw(75) << "                                  Описание";
        LineUp();
        cout << left << setw(15) << "     Цена";
        LineUp();
        cout << endl;

        for (int i = 0; i < numberAllService; ++i)
        {
            allServices[i].display_info(i + 1);
            cout << endl;
        }
        LineUpUgol(2);
        Line(154);
        LineUpUgol(4);
        cout << endl;

        return 0;
    }

    void SetPersonal_data() override
    {
        cout << "Введите фамилию: ";
        cin >> this->surname;
        cout << "Введите имя: ";
        cin >> this->name;
        cout << "Введите адрес: ";
        getchar();
        getline(cin, this->address);
    }

    void Display_contact() override
    {
        cout << "Фамилия: " << surname << endl;
        cout << "Имя: " << name << endl;
        cout << "Адрес: " << address << endl;
    }

    void addService()
    {
        int number;
        cout << "Введите номер маркетинговой услуги: ";
        cin >> number;

        SmartPointer<MarketingService> newServices(new MarketingService[orderedServicesCount + 1]);

        for (int i = 0; i < orderedServicesCount; ++i)
        {
            newServices[i] = orderedServices[i];
        }

        newServices[orderedServicesCount] = allServices[number - 1];

        ++orderedServicesCount;
        
        orderedServices = newServices;
    }



    void displayServices()
    {
        LineUpUgol(1);
        Line(154);
        LineUpUgol(3);
        cout << endl;
        LineUp();
        cout << left << setw(2) << "№";
        LineUp();
        cout << left << setw(27) << "        Название услуги";
        LineUp();
        cout << left << setw(31) << "           Тип услуги";
        LineUp();
        cout << left << setw(75) << "                                  Описание";
        LineUp();
        cout << left << setw(15) << "     Цена";
        LineUp();
        cout << endl;
        
        for (int i = 0; i < orderedServicesCount; ++i) 
        {
            orderedServices[i].display_info(i + 1);
            cout << endl;
        }
        LineUpUgol(2);
        Line(154);
        LineUpUgol(4);
        cout << endl;
    }

    void deleteServices()
    {
        int num;
        cout << "Введите номер услуги которую хотите оменить: ";
        cin >> num;

        for (int i = num - 1; i < orderedServicesCount - 1; i++)
        {
            orderedServices[i] = orderedServices[i + 1];
        }

        orderedServicesCount--;

        SmartPointer<MarketingService> newServices(new MarketingService[orderedServicesCount]);

        for (int i = 0; i < orderedServicesCount; ++i)
        {
            newServices[i] = orderedServices[i];
        }

        orderedServices = newServices;
    }

    
};