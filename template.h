#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <functional>
template<typename T>  class myVector
{
	T m_top{};
	T m_bottom{};
	std::vector<T> v;
public:
	myVector() = default;
	myVector(const T& bottom, const T& top, const std::initializer_list<T>& init) :m_top(top), m_bottom(bottom)
	{
		v.reserve(init.size());
		for (const auto& i : init)
		{
			if (i > m_bottom && i < m_top && (std::find(v.begin(), v.end(), i) == v.end()))
			{
				v.push_back(i);
			}
		}

	}
	void Add(const std::initializer_list<T>& init)
	{
		v.reserve(v.size() + init.size());
		for (const auto& i : init)
		{
			if (i > m_bottom && i < m_top && (std::find(v.begin(), v.end(), i) == v.end()))
			{
				v.push_back(i);
			}
		}
	}

	void Delete(const std::initializer_list<T>& init)
	{
		auto it = v.begin();
		for (const auto& i : init)
		{
			it = std::find(v.begin(), v.end(), i);
			if (it != v.end())
			{
				v.erase(it);
			}
		}
		
	}


	void Sort(const std::string& str)
	{
		std::string up = "Up";
		std::string down = "Down";
		if (str == up)
		{
			std::sort(v.begin(), v.end());
		}
		else if (str == down)
		{
			std::sort(v.begin(), v.end(), [](const auto& left, const auto& right)->bool {return (left > right); });
		}
		else
		{
			throw std::exception("Incorrectly enterd command\nEnter Up or Down\n");
		}
	}


	friend std::ostream& operator<< (std::ostream& out, const myVector<T>& vec)
	{
		std::cout << "Границы вектора\n" << "Нижняя " << vec.m_bottom << "\n" << "Верхняя " << vec.m_top << "\n";
		for (const auto& i : vec.v)
		{
			out << i << " ";
		}
		out << std::endl;
			return out;
	}
	
};


template<typename T> 
class myQueue
{

public:

	class iterator
	{
	public:
		//конструктор
		iterator(const myQueue* ptr, unsigned int index) :ptrQueue(ptr), ind(index) {};
		//оператор инкрементации
		iterator& operator++() { ind++;ind %= ptrQueue->cap; return (*this); }
		//оператор сравнения
		bool operator != (const iterator& other) const { return !((ptrQueue->p == other.ptrQueue->p) && (ind == other.ind)); }
		//оператор равенства
		bool operator == (const iterator& other) const { return ((ptrQueue->p == other.ptrQueue->p) && (ind == other.ind));}
		const T& operator*() const { return ptrQueue->p[ind]; }//только для чтения
//		T& operator*() {return ptrQueue->p[ind];}//для чтения и записи вроде как

	private:
		const myQueue* ptrQueue;
		unsigned int ind;

	};
private:
	unsigned int cnt;//размер очереди
	unsigned int cap;//емкость очереди
	unsigned int head;//первый элемент
	unsigned int tail;//последний элемент
	T* p;//динамический массив
	const unsigned int delta = 10;

public:
	//коструктор
	myQueue() :cap(10), cnt(0), head(0), tail(0), p(new T[cap]) { }

	//конструтор копирования
	myQueue(const myQueue& other):cap(other.cnt + 10),cnt(other.cnt), head(0), tail(cnt), p(new T[cap])
	{


		myQueue<T>::iterator itb = other.begin();
			
			for (int i = 0; i < cnt; i++)
			{
				p[i] = *itb;
				++itb;
			}


	}

	myQueue(const unsigned int& nmbr, const T& data):cap(nmbr + 10), cnt(nmbr), head(0),tail(nmbr), p(new T[cap])
	{
		//T tmp{ std::move(data) };
		for (int i = 0; i < nmbr;i++)
		{
			p[i] = data;
		}
	}

	//конструктор копирования(move semantic)
	myQueue(myQueue&& other)
	{
		p = other.p;
		head = other.head;
		tail = other.tail;
		cnt = other.cnt;
		cap = other.cap;
		other.p = nullptr;
	}

	//итераторы
	iterator begin() const { return iterator(this, head); }
	iterator end() const {return iterator(this, tail);}

	iterator cbegin()	const { return iterator(this, head); }
	iterator cend()		const { return iterator(this, tail); }

	/*const_iterator cbegin() { return const_iterator(this, head); }
	const_iterator cend() { return const_iterator(this, tail); }*/

	//выделение памяти
	void newMemory(unsigned int add)
	{
		

		try {
			cap = add + delta;
			p = new T[cap];
		}
		catch(std::bad_alloc err)
		{
			std::cout << err.what() << std::endl;
		}

	}

	//добавление в конец очереди
	void push(const T& item)
	{
		//std::cout << "Добавляемые значения без зацикливания\n";
		//for (int i = 0; i < cnt; i++)
		//{
		//	std::cout << "p[" << i << "]" << " = " << p[i] << std::endl;
		//}
		
		if (cnt == cap - 1)
		{ 
			T* p2;
			p2 = p;
			p2[tail] = item;
			newMemory(cap);
			//перераспределение памяти
			for(int i = 0; i < cnt;i++)
			{
				p[i] = p2[(head + i) % cnt];
			}
			head = 0;
			tail = cnt;
			delete[] p2;
		}
		//std::cout << "Tail before add " << tail << std::endl;
		p[tail] = item;
		cnt++;
		tail = (tail + 1) % cap;
		//std::cout << "Tail after add " << tail << std::endl;
		
	}
	//move operATOR

	//удаление первого элемента
	T pop()
	{
		//ПЕРЕМЕЩАЮЩИЙ КОНСТРУКТОР
		//не сделано, если очередь пуста
		try{

			T tmp{ std::move(p[head]) };
			head = (head + 1) % cap;
			cnt--;
			return tmp;
		}
		catch (std::bad_alloc err)
		{
			std::cout << err.what() << std::endl;
		}
	}

	//конструктор с листом инициализации
	myQueue(const std::initializer_list<T>& init):cap(init.size()*2), cnt(init.size()), head(0), tail(0), p(new T[cap])
	{

		for (const auto& i : init)
		{
			p[tail] = i;
			tail++;
		}
	}

	//деструктор
	~myQueue()
	{
			delete[] p;
	}

	//перегруженный стандартный вывод
	friend std::ostream& operator << (std::ostream& out, const myQueue<T>& queue)
	{
		try {
			out << "Capacity: " << queue.cap << " " << "Size: " << queue.cnt << std::endl
				<< "Head: " << queue.head << " " << "Tail: " << queue.tail << std::endl;
			for (const auto& i : queue)
			{
				out << i << " ";
			}
			out << std::endl;
			return out;
		}
		catch (std::bad_alloc err)
		{
			std::cout << err.what() << std::endl;
		}
	}

	//оператора присваивания класический
	myQueue<T>& operator=(const myQueue<T>& other)
	{
		
		//проверка на nullptr
		if (other.p == nullptr)
		{
			delete[]p;
			p = nullptr;
		}
		else if(this != &other)
		{
			if (other.cnt > (cap - 1))
			{
				delete[] p;
				newMemory(other.cnt);
			}
			head = 0;
			tail = 0;
			cnt = 0;
			for (const auto& i: other)
			{
				push(i);
			}
		}

		return *this;
	}

	//оператор присваивания move//НЕ ДОДЕЛАН
	myQueue<T>& operator=(myQueue<T>&& other)
	{
		//delete p;
		p = other.p;
		head = other.head;
		tail = other.tail;
		cnt = other.cnt;
		cap = other.cap;
		other.p = nullptr;
		return *this;
	}
	
	
	//сравнение на равенство
	bool equal(const myQueue<T>& other)
	{
		
			if (cnt != other.cnt)
			{
				return false;
			}
			else
			{
				unsigned int j = head;
				for (const auto& i : other)
				{
					if (p[j] != i)
					{
						return false;
					}
					j = (j + 1) % cap;
				}
			}
			return true;
		
	}
	

};


template<typename T>
class myUniquePtr
{
public:
	//конструктор
	myUniquePtr(T* ptr)
	{
		this->m_ptr = ptr;
		std::cout << "Constructor\n";
	}
	//деструктор
	~myUniquePtr()
	{
		delete m_ptr;
		std::cout << "Destructor\n";
	}
	//оператор разыменования
	T& operator *()
	{
		return *m_ptr;
	}

private:
	T* m_ptr;
};