#include <iostream>
#include "template.h"	
#include <queue>
#include "MyString.h"
#include <vector>
int main()
{
	setlocale(LC_ALL, "Russian");
	{

		std::cout << "\n--------------------First example---------------\n";
		myVector<int> vec(0, 10, { 5, 1, 3, 2, 6, 8, 0, 15, -3, 3, 3, 3 ,3 });
		std::cout << vec << "\n";

		vec.Add({ 1, 5, 6, 3, 5, 6, 6, 11, 6, 7 , 4 });

		std::cout << vec << "\n";

		vec.Delete({ 1,1,1,1, 3,5, 11, 12 });

		std::cout << vec << "\n";
		//vec.Delete({ 2,6,8,4,7 });
		try {
			vec.Sort("Up");

		}
		catch (const std::exception exp)
		{
			std::cout << exp.what() << std::endl;
		}

		std::cout << vec << "\n";

		try {
			vec.Sort("Down");
		}
		catch (const std::exception exp)
		{
			std::cout << exp.what() << std::endl;
		}

		std::cout << vec << "\n";

		std::cout << "\n--------------------End of First example---------------\n";
	}


	{
		std::cout << "\n--------------------Second example---------------\n";


		myQueue<int> que;// { 1, 5, 7, 9, 3 };
		std::cout << "Function method print\n";
		std::cout << "Function method <<\n";
		std::cout << que;

		que.push(5);
		que.push(4);
		que.push(3);
		que.push(2);
		que.push(1);

		std::cout << "range based for\n";

		for (const auto& i : que)
		{
			std::cout << i << "\n";
			std::cout << typeid(i).name() << "\n";
		}

		std::queue<int> qInt;

		qInt.push(5);
		qInt.push(4);
		qInt.push(3);
		qInt.push(2);
		qInt.push(1);


		std::cout << que << std::endl;

		que.pop();
		std::cout << que << std::endl;

		que.pop();
		std::cout << que << std::endl;

		que.push(5);
		std::cout << que << std::endl;
		que.push(4);
		std::cout << que << std::endl;
		que.push(3);
		std::cout << que << std::endl;
		que.push(2);
		std::cout << que << std::endl;
		que.push(1);
		std::cout << que << std::endl;
		que.push(1);
		std::cout << que << std::endl;
		que.push(1);
		std::cout << que << std::endl;
		que.push(1);
		std::cout << que << std::endl;

		que.pop();
		std::cout << que << std::endl;

		que.pop();
		std::cout << que << std::endl;

		que.push(5);
		std::cout << que << std::endl;
		que.push(5);
		std::cout << que << std::endl;

		//std::cout << que;

		//хз можно ли так делать
		myQueue<int> queCopy;// { std::move(que) };

		queCopy = que;
		//queCopy{ std::move(que) };


		std::cout << "Copy que\n";
		std::cout << queCopy;

		/*if (que == queCopy)
		{
			std::cout << "queues are identical!\n";
		}
		else
		{
			std::cout << "queues are not identical!\n";
		}*/


		myQueue<int>::iterator itb = que.begin();
		myQueue<int>::iterator ite = que.end();

		if (itb == ite)
		{
			std::cout << " All right!";
		}

		std::cout << *ite;
		//std::cout << it;
		std::cout << *itb;
		++itb;
		std::cout << *itb;
		++itb;
		std::cout << *itb;
		++itb;
		std::cout << *itb;
		++itb;
		std::cout << *itb;

		std::cout << "Function method <<\n";
		std::cout << que;

		myQueue<MyString>  q1{ MyString("AAA"), MyString("qwerty"), MyString("qwerty2"), MyString("qwerty3"), MyString("qwerty4"), MyString("qwerty5"), MyString("qwerty6") };
		//использование MyQueue в диапазонном for:
		for (auto& el : q1) { std::cout << el << ' '; }
		MyString s("abc");
		q1.push(s);
		q1.push(MyString("123"));
		MyString s1 = q1.pop();
		//q1.push("qqq");
		q1.push(s);
		std::cout << q1;
		myQueue < MyString >  q2 = q1;
		std::cout << q2;
		myQueue < MyString >  q22 = std::move(q1);

		myQueue<MyString> q3{ 10, MyString("!") };

		std::cout << q3;

		q2 = myQueue<MyString>(5, MyString("?"));

		std::cout << q2;

		q1 = { MyString("bbb"), MyString("ssss") };

		std::cout << q1;

		std::cout << q3;

		q1 = q3;

		std::cout << q1;

		std::cout << "\n--------------------End of Second example---------------\n";
	
	}

	{
	std::cout << "\n--------------------Third example---------------\n";

	myUniquePtr<int> ptr = new int(5);

	std::cout << *ptr;
	myUniquePtr<int> ptr1(new int(5));

	MyString s("abc");
	std::cout << s.GetString() << std::endl;
	myUniquePtr<MyString> ptrStr(new MyString("abc"));
std: cout << *ptrStr;
	std::cout << ptrStr->GetString() << std::endl;

	ptrStr->SetNewString("qwerty");

	std::cout << ptrStr->GetString() << std::endl;

	MyString s2 = *ptrStr;

	std::cout << s2 << std:: endl;

	myUniquePtr<MyString> p2(move(ptrStr));

	std::cout << *p2 << std::endl;

	std::cout << ptrStr << std::endl;

	if (ptrStr)
	{
		std::cout << "No object!" << std::endl;
	}
	
	myUniquePtr<MyString> p3(new MyString("gggg"));

	//p3 = p2;

	std::vector<myUniquePtr<MyString>> vecPtr{ move(new MyString("aaa")), move(new MyString("bbb")) };//{ std::move(myUniquePtr<MyString("aaa")>), std::move(myUniquePtr < MyString("bbb")>) };
	vecPtr.push_back(new MyString("abc"));
	for (const auto& i : vecPtr)
	{
		std::cout << i->GetString();
	}
	

	std::cout << "\n--------------------End of Third example---------------\n";
	}
	
	return 0;
}