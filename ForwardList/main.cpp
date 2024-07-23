#include<iostream>
using namespace std;

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstractor: " << this << endl;
	}
	~Element()
	{
		cout << "EDistructor: " << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor: " << this << endl;
	}
	~ForwardList()
	{
		cout << "LDistruuctor: " << this << endl;
	}
	// Add
	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);

		if (Head == nullptr)
			Head = New;
		else
		{
			Element* Temp = Head;
			while (Temp)
			{
				if (Temp->pNext == nullptr)
				{
					Temp->pNext = New;
					break;
				}
				else
					Temp = Temp->pNext;
			}
		}
	}
	void pop_front()
	{
		Element* buf = Head;
		Head = Head->pNext;
		delete buf;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext)
		{
			if (Temp->pNext->pNext == nullptr)
			{
				delete Temp->pNext;
				Temp->pNext = nullptr;
			}
			else
				Temp = Temp->pNext;
		}
	}

	//Metods
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(0, "");
	ForwardList list;
	for (int i = 0; i < 5; i++)
		list.push_back(rand() % 100);
	list.print();
	list.pop_front();
	cout << endl;
	list.print();
	list.pop_back();
	cout << endl;
	list.print();
}