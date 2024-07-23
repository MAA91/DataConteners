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
		cout << "FConstructor: " << this << endl;
	}
	~ForwardList()
	{
		cout << "FDistruuctor: " << this << endl;
	}
	// Add
	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;
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
		list.push_front(rand() % 100);
	list.print();
}