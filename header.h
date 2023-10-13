#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>

using namespace std;

	template <class T>
	struct Status 
	{
		T* ptr;
		int counter;
	};
		
	
	template <class T>
	class SmartPointer 
	{
	private:
		Status<T>* smartPtr;

	public:
		SmartPointer()
		{
			smartPtr = NULL;
		}

		SmartPointer(T* ptr)
		{
			if (!ptr)
				smartPtr = NULL;
			else
			{
				smartPtr = new Status<T>();
				smartPtr->ptr = ptr;
				smartPtr->counter = 1;
			}
		}

		SmartPointer(const SmartPointer& obj) : smartPtr(obj.smartPtr) 
		{
			if (smartPtr)
				smartPtr->counter++;
		}

		~SmartPointer()
		{
			if (smartPtr)
			{
				smartPtr->counter--;
				if (smartPtr->counter == 0)
				{
					delete[] smartPtr->ptr;
					delete smartPtr;
				}
			}
		} 

		SmartPointer& operator=(const SmartPointer& obj) 
		{
			if (smartPtr)
			{
				smartPtr->counter--;
				if (smartPtr->counter == 0)
				{
					delete[] smartPtr->ptr;
					delete smartPtr;
				}
			}
			smartPtr = obj.smartPtr;
			if (smartPtr)
				smartPtr->counter++;
			return *this;
		}

		T& operator[](int index) const
		{
			if (smartPtr)
			{
				return smartPtr->ptr[index];
			}
		}

		T& operator*() const
		{
			if (smartPtr)
				return *(smartPtr->ptr);
		}

		T* operator->() const
		{
			if (smartPtr)
				return smartPtr->ptr;
			else
				return NULL;
		} 

		void showCounter() 
		{
			cout << "Значение счетчика для объекта " << smartPtr << " равно: " << smartPtr->counter << endl;
		}
	};

	enum State { begin_, middle };

	template <class T>
	class Transaction 
	{
		T* currentState;
		T* prevState;

	public:
		Transaction() : prevState(NULL), currentState(new T)
		{}

		

		Transaction(const Transaction& obj) : currentState(new T(*(obj.currentState))), prevState(NULL) 
		{}

		~Transaction()
		{
			delete currentState; delete prevState;
		}

		Transaction& operator=(const Transaction& obj)
		{
			if (this != &obj)
			{
				delete currentState;
				currentState = new T(*(obj.currentState));
			}
			return *this;
		}

		void showState(State state)
		{
			if (prevState)
				prevState->Display_contact();
			else
				currentState->Display_contact();
		}

		int beginTransactions()
		{
			delete prevState;
			prevState = currentState;
			currentState = new T(*prevState);
			if (!currentState)
				return 0;
				currentState->SetPersonal_data();
	
			return 1;
		}

		void commit()
		{
			delete prevState;
			prevState = NULL;
		}

		void deleteTransactions() 
		{
			if (prevState != NULL)
			{
				delete currentState;
				currentState = prevState;
				prevState = NULL;
			}
		}

		T* operator->()
		{
			return currentState;
		}
	};
