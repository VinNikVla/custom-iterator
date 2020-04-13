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
		iterator(myQueue* ptr, unsigned int index) :ptrQueue(ptr), ind(index) {};
		iterator& operator++() { ind++;ind %= ptrQueue->cap; return (*this); }
		bool operator != (const iterator& other) const { return !((ptrQueue->p == other.ptrQueue->p) && (ind == other.ind)); }
		bool operator == (const iterator& other) const { return ((ptrQueue->p == other.ptrQueue->p) && (ind == other.ind));}
		const T& operator*() const { return ptrQueue->p[ind]; }//только для чтения
		T& operator*() {return ptrQueue->p[ind];}//для чтения и записи вроде как

	private:
		myQueue* ptrQueue;
		unsigned int ind;

	};
private:
	unsigned int cnt;//размер очереди
	unsigned int cap;//емкость очереди
	unsigned int head;//первый элемент
	unsigned int tail;//последний элемент
	T* p;//динамический массив
public:
	myQueue() :cap(10), cnt(0), head(0), tail(0), p(new T[cap]) { }
	myQueue(const myQueue& other):cap(other.cnt + 10),cnt(other.cnt), head(0), tail(cnt), p(new T[cap])
	{


		auto itb = other.begin();
			
			for (int i = 0; i < cnt; i++)
			{
				p[i] = *itb;
				++itb;
			}


	}
	void push(const T& item)
	{
		
		if (cnt == cap - 1)
		{
			//перераспределение памяти

		}
		p[tail] = item;
		cnt++;
		tail = (tail + 1) % cap;
		
	}
	//move operATOR


	T pop()
	{
		//ПЕРЕМЕЩАЮЩИЙ КОНСТРУКТОР

		T tmp{ std::move(p[head]) };
		head = (head +1 ) % cap;
		cnt--;
		return tmp;
	}
	myQueue(const std::initializer_list<T>& init):cap(init.size()*2), cnt(init.size()), head(0), tail(0), p(new T[cap])
	{

		for (const auto& i : init)
		{
			p[tail] = i;
			tail++;
		}
	}

	~myQueue()
	{
			delete[] p;
	}

	void print(const char* obj)
	{
		std::cout << "Очередь " << obj << std::endl;
		for (int i = 0; i < cnt; i++)
		{
			std::cout << p[i] << " ";
		}
		std::cout << std::endl;
	}

	friend std::ostream& operator << (std::ostream& out, const myQueue<T>& queue)
	{
		out << "Capacity: " << queue.cap << " " << "Size: " << queue.cnt << std::endl;
		for (int i = 0; i < queue.cnt; i++)
		{
			out << queue.p[i] << " ";
		}
		out << std::endl;
		return out;
	}

	//оператора присваивания класический
	//оператор присваивания move
	//сравнение на равенство
	iterator begin() { return iterator(this, head); }
	iterator end() { return iterator(this, tail); }

};