#include "header.h"
#include "Marceting_class.h"
#include <type_traits>
#include <fstream>

template <class T>
void file_write(T obj, string name)
{
	ofstream file;
	file.open(name, ofstream::app);

	if (!file.is_open())
		cout << "������ �������� �����" << endl;
	else
		file.write((char*)&obj, sizeof(T));

	file.close();
}


template <class T>
void make(T& person, Transaction<T>& transaction)
{
	bool check_personalDate = true;
	if (transaction->GetName() == "underfined")
		check_personalDate = false;

	int choice_;
	do
	{
		cout << "1. ������ ������ ������" << endl;
		cout << "2. �������� ������ ����������" << endl;
		cout << "3. �������� ������ ����������" << endl;
		if (is_same<T, Customer>::value)
		{
			cout << "4. �������� ������" << endl;
			cout << "5. ���������� ��� ���������� ������" << endl;
			cout << "6. �������� ���������� ������" << endl;
		}
		else
		{
			cout << "4. �������� ������" << endl;
			cout << "5. ���������� ���������� ������" << endl;
			cout << "6. �������� ���������� ������" << endl;
		}
		cout << "7. �����" << endl;
		cout << "�������� �����: ";
		cin >> choice_;
		system("cls");

		switch (choice_)
		{
		case 1:
			if (check_personalDate)
			{
				cout << "������ ������ �������";
				Sleep(1200);
			}
			else
			{
				transaction.beginTransactions();
				transaction.commit();
				//customer.SetPersonal_data();
				check_personalDate = true;
			}
			system("cls");
			break;
		case 2:
			if (!check_personalDate)
			{
				cout << "���������� ������ ������ ������";
				Sleep(1200);
				system("cls");
			}
			else
			{
				char exit;
				//customer.Display_contact();
				transaction.showState(middle);
				cout << endl << endl << "��� ������ ������� ����� �������";
				exit = _getch();
				system("cls");
			}
			break;
		case 3:
			if (!check_personalDate)
			{
				cout << "���������� ������ ������ ������";
				Sleep(1200);
				system("cls");
			}
			else
			{
				int result;
				cout << "������� ����� ������ " << endl;
				transaction.beginTransactions();
				cout << endl << endl << "���������� ��������:" << endl;
				transaction.showState(begin_);
				cout << endl;
				cout << endl << "����������� ���������?" << endl;
				cout << "1. ��" << endl;
				cout << "2. ���" << endl;
				cout << "�������� �����: ";
				cin >> result;
				if (result == 1)
					transaction.commit();
				else
					transaction.deleteTransactions();
				system("cls");
			}
			break;
		case 4:
			if (!check_personalDate)
			{
				cout << "���������� ������ ������ ������";
				Sleep(1200);
				system("cls");
			}
			else
			{
				if (is_same<T, Customer>::value)
				{
					if (person.GetSetnumberAllService() == 0)
					{
						cout << "�� ������ ������ �������� �� ������������� ������������� ������";
							Sleep(1200);
					}
					else
					{
						person.GetServices();
						cout << endl;
						person.addService();
					}
					system("cls");
				}
				else
				{
					person.addService();
					system("cls");
				}
				
			}
			break;
		case 5:
			if (!check_personalDate)
			{
				cout << "���������� ������ ������ ������";
				Sleep(1200);
				system("cls");
			}
			else
			{
				bool boolean = false;
				if (is_same<T, Customer>::value)
				{
					if (person.GetSetnumberService() == 0)
					{
						cout << "� ��� ��� ���������� �����";
						Sleep(1200);
					}
					else
						boolean = true;
				}
				else if(is_same<T, Manager>::value)
				{
					if (person.GetSetnumberAllService() == 0)
					{
						cout << "� ��� ��� ���������� �����";
						Sleep(1200);
					}
					else
						boolean = true;
				}
				 if(boolean == true)
				{
					char exit;
					person.displayServices();
					cout << endl << endl << "��� ������ ������� ����� �������";
					exit = _getch();
				}
				system("cls");
			}
			break;
		case 6:
			if (!check_personalDate)
			{
				cout << "���������� ������ ������ ������";
				Sleep(1200);
				system("cls");
			}
			else
			{
				bool boolean = false;
				if (is_same<T, Customer>::value)
				{
					if (person.GetSetnumberService() == 0)
					{
						cout << "� ��� ��� ���������� �����";
						Sleep(1200);
					}
					else
						boolean = true;
				}
				else if(is_same<T, Manager>::value)
				{
					if (person.GetSetnumberAllService() == 0)
					{
						cout << "� ��� ��� ���������� �����";
						Sleep(1200);
					}
					else
						boolean = true;
				}

				 if (boolean == true)
				 {
					char exit;
					person.displayServices();
					cout << endl;
					person.deleteServices();
					system("cls");
					person.displayServices();
					cout << endl << endl << "��� ������ ������� ����� �������";
					exit = _getch();
				 }
				system("cls");
			}
			break;
		}
	} while (choice_ != 7);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Customer customer;
	Manager manager;

	Transaction<Customer> transactionCustomer;
	Transaction<Manager> transactionManager;

	int choice;
	do
	{
		customer.SetnumberAllService(manager.GetSetnumberAllService());
		customer.SetServices(manager.GetServices());
		cout << "1. ������������" << endl;
		cout << "2. ��������" << endl;
		cout << "3. �����" << endl;
		cout << "�������� �����: ";
		cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
			make(customer, transactionCustomer);
			break;
		case 2:
			make(manager, transactionManager);
			break;
		}

	} while (choice != 3);

	file_write(customer, "customer.txt");
	file_write(manager, "manager.txt");
	file_write(transactionCustomer, "tr_customer.txt");
	file_write(transactionManager, "tr_manager.txt");

	return 0;
}	
