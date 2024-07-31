#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

class Element
{
	int Data;			
	Element* pNext;	
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "IConstructor: " << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor: " << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator == (Iterator& other)
	{
		return this->Temp == other.Temp;
	}
	bool operator != (Iterator& other)
	{
		return this->Temp != other.Temp;
	}

	int operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	int size;
public:
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
		cout << "MoveConstructor:" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*if (Head == nullptr)return push_front(Data);

		Element* New = new Element(Data);

		Element* Temp = Head;

		while (Temp->pNext)
			Temp = Temp->pNext;

		Temp->pNext = New;
		size++;*/
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;

		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (Index == 0)
		{
			Element* New = new Element(Data);

			New->pNext = Head;

			Head = New;
			size++;
		}
		else
		{
			Element* New = new Element(Data);

			Element* Temp = Head;
			for (int i = 0; i < Index - 1; i++)
			{
				Temp = Temp->pNext;
			}

			New->pNext = Temp->pNext;
			Temp->pNext = New;

			size++;
		}
	}

	//Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Erased = Head;

		Head = Head->pNext;

		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		delete Temp->pNext;

		Temp->pNext = nullptr;

		size--;
	}

	//Methods:
	void print()const
	{
		Element* Temp = Head;	
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Колтчество элементов списка: " << size << endl;
		cout << "Общее колтчество элементов: " << Element::count << endl;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer = left;
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}

void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите воличество элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

}