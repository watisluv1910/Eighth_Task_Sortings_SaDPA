#include "array_class.h"

#include <ctime>
#include <chrono>

#include <iostream>

using std::string;
using std::vector;

inline void OutputMenu();
void FillArray(Array& new_array);
void SortArray(Array& my_array);

int main()
{
	OutputMenu();

	std::cout << "\nYour choise is:\n";

	unsigned path = 0; // Menu navigation variable
	std::cin >> path;

	// cin.clear and cin.ignore are used to prevent fake input:
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');

	Array my_array;

	while (path)
	{
		switch (path)
		{
		case 1:
		{
			FillArray(my_array);
			break;
		}	
		case 2:
		{
			SortArray(my_array);
			break;
		}		
		default:

			std::cerr << "\nError (0): Wrong path entered.\n"; // Error 0
			break;
		}

		system("pause");
		system("cls"); // clear screen

		OutputMenu();

		// Next menu navigation step:
		std::cout << "\nYour choise is:\n";
		std::cin >> path;

		// cin.clear and cin.ignore are used to prevent fake input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}
	
	return 0;
}

inline void OutputMenu()
{
	std::cout << "Practical task num.8\nIKBO-03-21 Nasevich V.V.\n"
		"Variant num. 19.\n\nMenu:\n"
		"1)Enter <1> to fill the array.\n"
		"2)Enter <2> to sort the array.\n"
		"3)Enter <0> to end the programm.\n";
}

void FillArray(Array &new_array)
{
	std::cout << "\nEnter the length of the array:\n";
	size_t array_size = 0;
	std::cin >> array_size;

	std::cout << "\nEnter the way how to fill the array:\n"
		"1)Enter <1> to fill the array by yourself.\n"
		"2)Enter <2> to fill the array with random numbers.\n"
		"3)Enter <0> to exit.\n\n";
	unsigned array_filling_method = 0;
	std::cin >> array_filling_method;

	std::cout << "\nEnter the start state of the array:\n"
		"1)Enter <1> to represent the array in standart order.\n"
		"2)Enter <2> to represent the array in ascending order.\n"
		"3)Enter <3> to represent the array in descending order.\n"
		"4)Enter <0> to exit.\n\n";
	unsigned start_state = 0;
	std::cin >> start_state;

	if (!new_array.FillData(array_size, array_filling_method, start_state))
	{
		std::cerr << "\nError (1): Wrong filling data entered.\n"; // Error 1
	}
}

void SortArray(Array& my_array)
{
	std::cout << "\nThe list of sortings is:\n"
		<< "1)Selection_sort.\n"
		<< "2)Cocktail_sort.\n"
		<< "3)Heap_sort.\n";
	std::cout << "\nEnter the name of the sort from the list above:\n";
	string sort_name;
	std::cin >> sort_name;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	auto begin = std::chrono::steady_clock::time_point();
	auto end = std::chrono::steady_clock::time_point();

	if (sort_name == "Selection_sort")
	{
		begin = std::chrono::steady_clock::now();

		my_array.SelectionSort();

		end = std::chrono::steady_clock::now();
	}
	else if (sort_name == "Cocktail_sort")
	{
		begin = std::chrono::steady_clock::now();

		my_array.CocktailSort();

		end = std::chrono::steady_clock::now();
	}
	else if (sort_name == "Heap_sort")
	{
		begin = std::chrono::steady_clock::now();

		my_array.HeapSort();

		end = std::chrono::steady_clock::now();
	}
	else
	{
		std::cerr << "\nError (2): Wrong sorting name entered.\n"; // Error 2
		return;
	}

	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	std::cout << "\nThe sorting time is: " << elapsed_ms.count() << " ms.\n";
}
