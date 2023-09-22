#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <conio.h>

using namespace std;

float SetPresision(float value);

class OrderLine
{
private:
	string product;
	int quantity;
	float price;
	int number_line;

public:
	OrderLine()
	{
		product = "Undefined";
		quantity = 0;
		price = 0;
		number_line = 1;
	}

	OrderLine(string product, int quantity, float price)
	{
		this->product = product;
		this->quantity = quantity;
		this->price = price;
		number_line = 1;
	}

	void Create_OrderLine()
	{
		cout << "Введите название товара: ";
		cin >> this->product;
		cout << "Введите количество товара: ";
		cin >> this->quantity;
		cout << "Введите стоимость товара(BYN): ";
		cin >> this->price;
		this->price = SetPresision(this->price);
	}

	void SetProduct(string product)
	{
		this->product = product;
	}

	string GetProduct()
	{
		return product;
	}

	void SetQuantity(int quantity)
	{
		this->quantity = quantity;
	}

	int GetQuantity()
	{
		return quantity;
	}

	void SetNumber_line(int number_line)
	{
		this->number_line = number_line;
	}

	int GetNumber_line()
	{
		return number_line;
	}

	void SetPrice(float price)
	{
		this->price = price;
	}

	float GetPrice()
	{
		return price;
	}

	friend istream& operator>>(istream& cin, OrderLine line);
	friend bool operator<(const OrderLine& first_value, const OrderLine& second_value);
};

ostream& operator<<(ostream& cout, OrderLine line)
{
	cout << "Название товара: " << setw(20) << left << line.GetProduct() << setw(2) << "|";
	cout << "Цена: " << setw(10) << left << line.GetPrice() << setw(2) << "|";
	cout << "Количество: " << setw(10) << left << line.GetQuantity() << setw(2) << "|" << endl;
	for (int i = 0; i < 80; i++)
		cout << "-";

	return cout;
}

bool operator<(const OrderLine& first_value, const OrderLine& second_value)
{
	return first_value.price < second_value.price;
}

class Order
{
private:
	string dateReceived;
	int number;
	float total_price;
	vector<OrderLine> line;

public:

	Order()
	{
		dateReceived = "02.02.2005";
		total_price = 0;
		number = 0;
	}

	Order(int number)
	{
		dateReceived = "02.02.2005";
		total_price = 0;
		this->number = number;
	}

	void add(OrderLine& orderLine)
	{
		this->line.push_back(orderLine);
		total_price += orderLine.GetPrice() * orderLine.GetQuantity();
	}

	void Display()
	{
		for (auto i = begin(line); i != end(line); i++)
		{
			cout << *i << endl;
		}
	}

	void Sort_price()
	{
		sort(line.begin(), line.end());
	}





	void SetTotal_price(float total_price)
	{
		this->total_price = total_price;
	}

	float GetTotal_price()
	{
		return total_price;
	}

	string GetDateReceived()
	{
		return dateReceived;
	}

	void SetNumber(int number)
	{
		this->number = number;
	}

	int GetNumber()
	{
		return number;
	}


	friend bool operator<(const Order& first_value, const Order& second_value);
};

ostream& operator<<(ostream& cout, Order myOrder)    /// Изменить в табличку ///
{
	cout << "Номер заказа: ";
	cout << myOrder.GetNumber() << endl;
	cout << "Дата получения: ";
	cout << myOrder.GetDateReceived() << endl;
	cout << "Итоговая цена: ";
	cout << myOrder.GetTotal_price() << endl;
	for (int i = 0; i < 8 + to_string(myOrder.GetTotal_price()).length(); i++)
	{
		cout << "-";
	}

	return cout;
}

class Customer
{
protected:
	float credit;
	vector<Order> myOrder;
	string name;
	string surname;
	string address;
public:


	Customer()
	{
		credit = 0;
		name = "Underfined";
		surname = "Underfined";
		address = "Underfined";
	}

	Customer(float credit)
	{
		this->credit = credit;
	}

	void virtual Display_contact()
	{

	}

	bool virtual Dispatch(Order& order)
	{
		if (this->credit < order.GetTotal_price())
			return false;
		else
		{
			myOrder.push_back(order);
			this->credit -= order.GetTotal_price();
			return true;
		}
	}

	void DisplayOrders()
	{
		Display_contact();
		int j = 0;
		cout << endl;
		for (auto i = begin(myOrder); i != end(myOrder); i++)
		{
			for (int i = 0; i < 80; i++)
			{
				cout << "-";
			}
			cout << endl << *i << endl;
			myOrder[j].Display();
			cout << endl;
			cout << endl << endl;
			j++;
		}


	}

	void Sort_price()
	{
		sort(myOrder.begin(), myOrder.end());
	}

	void Cancellations_order(int number)
	{
			if (number < myOrder.size())
			{
				this->credit += myOrder[number - 1].GetTotal_price();
				myOrder.erase(myOrder.begin() + number - 1);
			}
	}

	void Search_order(int number)
	{
		return myOrder[number - 1].Display();
	}

	void virtual SetPersonal_data()
	{

	}

	void SetCredit(double credit)
	{
		this->credit = credit;
	}

	double GetCredit()
	{
		return credit;
	}
};

bool operator<(const Order& first_value, const Order& second_value)
{
	return first_value.total_price < second_value.total_price;
}

class CorporateCustomer : public virtual Customer // Возможность бронирования в долг
{
protected:
	int numberPhone;
private:
	string contactName;
	string companyName;

public:

	CorporateCustomer()
	{
		numberPhone = 0;
		contactName = "Underfined";
		companyName = "Underfined";
	}

	void SetPersonal_data() override
	{
		cout << "Введите название компании: ";
		cin >> this->companyName;
		cout << "Введите контактное имя: ";
		cin >> this->contactName;
		cout << "Введите номер телефона(+375): ";
		cin >> this->numberPhone;
		cout << "Введите количество денег: ";
		cin >> this->credit;
		this->credit = SetPresision(this->credit);
	}

	void Display_contact() override
	{
		cout << "Название компании: " << companyName << endl;
		cout << "Контактное имя: " << contactName << endl;
		cout << "Номер телефона(+375): " << numberPhone << endl;
		cout << "Количество денег: " << credit << endl;
	}

	bool Dispatch(Order& order) override
	{
		if (this->credit < order.GetTotal_price())
		{
			int choice;
			cout << "Сделать заказ с отсрочкой оплаты? " << endl;
			cout << "1. Да" << endl;
			cout << "2. Нет" << endl;
			cin >> choice;
			if (choice == 1)
			{
				myOrder.push_back(order);
				return true;
			}
			else
				return false;

		}
		else
		{
			myOrder.push_back(order);
			this->credit -= order.GetTotal_price();
			return true;
		}
	}
};

class PersonalCustomer : public virtual Customer
{
protected:
	int CreditCardID;
public:

	PersonalCustomer()
	{
		CreditCardID = 123456;
	}

	void Display_contact() override
	{
		cout << "Фамилия: " << surname << endl;
		cout << "Имя: " << name << endl;
		cout << "Адрес: " << address << endl;
		cout << "Номер счета: " << CreditCardID << endl;
		cout << "Количество денег: " << credit << endl << endl;
	}

	void SetPersonal_data() override
	{
		cout << "Введите фамилию: ";
		cin >> this->surname;
		cout << "Введите имя: ";
		cin >> this->name;
		cout << "Введите адрес: ";
		cin >> this->address;
		cout << "Введите номер счета: ";
		cin >> this->CreditCardID;
		cout << "Деньги: ";
		cin >> this->credit;
		this->credit = SetPresision(this->credit);

	}

	bool Dispatch(Order& order) override
	{
		if (this->credit < order.GetTotal_price())	
		return false;
		else
		{
			myOrder.push_back(order);
			this->credit -= order.GetTotal_price();
			return true;
		}
	}

};



class VIPCustomer : public CorporateCustomer, public PersonalCustomer
{
private:
	float discount;

public:
	VIPCustomer()
	{
		discount = 0.2;
	}

	bool Dispatch(Order& order) override
	{
		if (this->credit < order.GetTotal_price() * (1 - discount))
			return false;
		else
		{
			myOrder.push_back(order);
			return true;
		}
	}

	void SetPersonal_data() override /// поменять ///
	{
		cout << "Введите фамилию: ";
		cin >> this->surname;
		cout << "Введите имя: ";
		cin >> this->name;
		cout << "Введите номер телефона(+375)";
		cin >> this->numberPhone;
		cout << "Введи адрес:";
		cin >> this->address;
		cout << "Введите номер счета: ";
		cin >> this->CreditCardID;
		cout << "Деньги: ";
		cin >> this->credit;
		this->credit = SetPresision(this->credit);
	}

	void Display_contact() override
	{
		cout << "Фамилия: " << surname << endl;
		cout << "Имя: " << name << endl;
		cout << "Номер телефона: " << numberPhone << endl;
		cout << "Адрес: " << address << endl;
		cout << "Номер счета: " << CreditCardID << endl;
		cout << "Количество денег: " << credit << endl << endl;
	}
};

float SetPresision(float value)
{
	 return floor(value * 100) / 100;
}

template <typename T>
void make(T& customer, vector<OrderLine>& line, vector<Order>& order)
{
	int number_orderline = 0;
	bool check_personalDate;
	if (customer.GetCredit() == 0)
		check_personalDate = false;
	else
		check_personalDate = true;

	int choice;
	do
	{
		cout << "1. Ввод личных данных" << endl;
		cout << "2. Сделать заказ" << endl;
		cout << "3. Посмотреть мои заказы" << endl;
		cout << "4. Сортировать заказы по цене" << endl;
		cout << "5. Отменить заказ" << endl;
		cout << "6. Поиск заказа по номеру" << endl << endl;

		cout << "Сделайте выбор: ";
		cin >> choice;
		system("cls");
		cout << endl;
		switch (choice)
		{
		case 1:
			if (check_personalDate)
				cout << "Личные данные введены";
			else
			{
				customer.SetPersonal_data();
				check_personalDate = true;
			}
			system("cls");
			break;
		case 2:
			if (!check_personalDate)
			{
				cout << "Необходимо ввести личные данные";
				Sleep(1200);
				system("cls");
			}
			else
			{
				char exit;
				order.push_back(Order());
				do {
					line.push_back(OrderLine());
					line[size(line) - 1].Create_OrderLine();
					cout << "Для выхода нажмите клавишу ESP, для продолжерия любую другую клавишу";
					exit = _getch();
					system("cls");
				} while (exit != 27);
				for (int i = number_orderline; i < size(line); i++)
				{
					order[size(order) - 1].add(line[i]);
					number_orderline = size(line);
				}
				order[size(order) - 1].SetNumber(size(order));
				if (customer.Dispatch(order[size(order) - 1]))
					cout << "Заказ номер " << order[size(order) - 1].GetNumber() << " Завершен успешно";
				else
					cout << "Заказ номер " << order[size(order) - 1].GetNumber() << " Отклонен, недостаточно срелств";
				Sleep(1000);
				system("cls");
			}
			break;
		case 3:
			if (!check_personalDate)
			{
				cout << "Необходимо ввести личные данные";
				Sleep(1200);
				system("cls");
			}
			else
				customer.DisplayOrders();
			break;
		case 4:
			if (!check_personalDate)
			{
				cout << "Необходимо ввести личные данные";
				Sleep(1200);
				system("cls");
			}
			else
			{
				customer.Sort_price();
				customer.DisplayOrders();
			}
			break;
		case 5:
			if (!check_personalDate)
			{
				cout << "Необходимо ввести личные данные";
				Sleep(1200);
				system("cls");
			}
			else
			{
				int number_order;
				cout << "Введите номер заказа который хотите удалить: ";
				cin >> number_order;
				customer.Cancellations_order(number_order);
				customer.DisplayOrders();
			}
			break;
		case 6:
			if (!check_personalDate)
			{
				cout << "Необходимо ввести личные данные";
				Sleep(1200);
				system("cls");
			}
			else
			{
				int number_order;
				cout << "Введите номер заказа который хотите найти: ";
				cin >> number_order;
				customer.Display_contact();
				customer.Search_order(number_order);
			}
			break;
		}
	} while (choice != 7);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<OrderLine> personal_line;
	vector<Order> personal_order;
	vector<OrderLine> corporate_line;
	vector<Order> corporate_order;
	vector<OrderLine> vip_line;
	vector<Order> vip_order;

	PersonalCustomer personal_customer;
	CorporateCustomer corporate_customer;
	VIPCustomer VIP_customer;

	int choice_;
	do
	{
		cout << "1. Пользователь" << endl;
		cout << "2. Корпоротивный Пользователь" << endl;
		cout << "3. VIP Пользователь" << endl;
		cout << "4. Пользователь(хард-код)" << endl;
		cout << "5. Выход" << endl;
		cout << "Сделайте выбор: ";
		cin >> choice_;
		system("cls");

		switch (choice_)
		{
		case 1:
			make(personal_customer, personal_line, personal_order);
			break;
		case 2:
			make(corporate_customer, corporate_line, corporate_order);
			break;
		case 3:
			make(VIP_customer, vip_line, vip_order);
			break;
		case 4:
			OrderLine base_line[6];
			base_line[0] = OrderLine("Моторное масло", 10, 40);
			base_line[1] = OrderLine("Антифриз", 10, 30);
			base_line[2] = OrderLine("Шины", 10, 50);
			base_line[3] = OrderLine("Аккумулятор", 10, 10);
			base_line[4] = OrderLine("Свечи зажигания", 10, 10);
			base_line[5] = OrderLine("Автомобиль", 1, 1000000);
			Order base_order[3] {1, 2, 3};
			for (int i = 0; i < 3; i++)
				base_order[0].add(base_line[i]);
			for (int i = 3; i < 5; i++)
				base_order[1].add(base_line[i]);
				base_order[2].add(base_line[5]);

			PersonalCustomer base_personal_customer;
			base_personal_customer.SetCredit(1500);

			for (int i = 0; i < 3; i++)
			{
				if (base_personal_customer.Dispatch(base_order[i]))
					cout << "Заказ номер " << base_order[i].GetNumber() << " Завершен успешно";
				else
					cout << "Заказ номер " << base_order[i].GetNumber() << " Отклонен, недостаточно срелств";
				Sleep(1000);
				system("cls");
			}
			base_personal_customer.DisplayOrders();
			base_personal_customer.Sort_price();
			base_personal_customer.DisplayOrders();
			base_personal_customer.Cancellations_order(0);
			base_personal_customer.DisplayOrders();
			break;
		}
	} while (choice_ != 5);

	return 0;




}

