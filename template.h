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
		iterator(T* ptr) :ptr(ptr) {};
		iterator operator++() { ++ptr; return *this; }
		bool operator != (const iterator& other) { return ptr != other.ptr; }
		const T& operator*() const { return *ptr; }
	private:
		T* ptr;
	};
private:
	T* p;//динамический массив
	unsigned int cnt;//размер очереди
	unsigned int cap;//емкость очереди
	unsigned int frst;//первый элемент
	unsigned int lst;//последний элемент
public:
	myQueue() = default;
	myQueue(const myQueue& other)
	{
		cap = other.cap;

		try {
			p = new T[cap];
			for (int i = 0; i < cap; i++)
			{
				p[i] = other.p[i];
				cnt++;
			}
		}
		catch (std::bad_alloc e)
		{
			std::cout << e.what() << std::endl;
			cnt = 0;
		}
	}
	void push(const T& item)
	{
		T* p2;//дополнительный указатель
		p2 = p;//перенаправил дополнительный указатель на p

		if (cnt == cap)
		{
			cap++;
			p = new T[cnt + 1];
		}
		try 
		{
			//попытка выделения памяти для p
			

			for (int i = 0; i < cnt; i++)
			{
				p[i] = p2[i];
			}
			
			p[cnt] = item;//скопировали последний элементы
			cnt++;
			//увеличили число элементов
			//освободили предварительно выделенную память
			if (cnt > 1)
			{
				delete[] p2;
			}
		}
		catch(std::bad_alloc e)
		{
			//если память не выделена 
			std::cout << e.what() << std::endl;// вывести сообщение об ошибке

			//вернуть указатель
			p = p2;
		}
	}
	myQueue(const std::initializer_list<T>& init)
	{
		cap = init.size();
		p = new T[cap];
		for (const auto& i : init)
		{
			p[cnt] = i;
			cnt++;
		}
	}

	~myQueue()
	{
		if (cnt > 0)
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
		for (int i = 0; i < queue.cnt; i++)
		{
			out << queue.p[i] << " ";
		}
		out << std::endl;
		return out;
	}
	iterator begin() const { return iterator(p); }
	iterator end() const { return iterator(p + cnt); }

};