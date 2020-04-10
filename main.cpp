#include <iostream>
#include "template.h"	

int main()
{
	setlocale(LC_ALL, "Russian");
	myVector<int> vec(0, 10, { 5, 1, 3, 2, 6, 8, 0, 15, -3, 3, 3, 3 ,3 });
	std::cout << vec << "\n";
	
	vec.Add({ 1, 5, 6, 3, 5, 6, 6, 11, 6, 7 , 4 });

	std::cout << vec << "\n";
	
	vec.Delete({ 1,1,1,1, 3,5, 11, 12 });
	
	std::cout << vec << "\n";
	//vec.Delete({ 2,6,8,4,7 });
	try{
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

	myQueue<int> que{ 1,5, 7,9,3 };
	std::cout << "Function method print\n";
	que.print("que");
	std::cout << "Function method <<\n";
	std::cout << que;

	que.push(5);

	std::cout << que;
	std::cout << "range based for\n";
	for (auto i : que)
	{
		std::cout << i << " ";
	}

	return 0;
}