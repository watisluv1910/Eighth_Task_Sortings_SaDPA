#include "array_class.h"

#include <iostream>
#include <algorithm>
#include <iterator>

bool Array::FillData(const size_t& size, 
	const unsigned& filling_method, 
	const unsigned& start_state)
{
	// Explanation:
	// 
	// filling_method value defines what way the vector will be 
	// filled - by user (1) or randomly (2).
	//
	// start_state value defines initial sate of the vector:
	// 1 - unsorted (with original order);
	// 2 - sorted in ascending order;
	// 3 - sorted in descending order.

	// Eliminates the possibility of creating a vector with zero length:
	if (!size) return false; 

	srand(time(0)); // For randomization depending on system time

	data_.clear(); // Cleaning vector before filling it with new values

	data_.resize(size);

	for (auto& element : data_) // Iteration over each vector element
	{
		switch (filling_method)
		{
		case 1:
			// Entering vector elements with keyboard:
			std::cin >> element;

			// cin.clear and cin.ignore are used to prevent fake input:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		case 2:
			// Random element initializing (range is from -100 to 100):
			element = static_cast<int>(rand() % 200 - 100);
			break;
		default:

			return false;
		}
	}
	
	switch (start_state)
	{
	case 1:
		// Passing stage if order should be original
		break;
	case 2:
		// Sorting vector in ascending order with built-in sort() function
		std::sort(data_.begin(), data_.end());
		break;
	case 3:
		// Sorting vector in descending order with built-in sort() function
		std::sort(data_.begin(), data_.end(), comparator);
		break;
	default:

		return false;
	}

	return true;
}

void Array::SelectionSort()
{
	// Explanation:
	// The selection sort algorithm sorts an array by repeatedly finding 
	// the minimum element (considering ascending order) from unsorted part 
	// and putting it at the beginning.
	// 
	// The algorithm maintains two subarrays in a given array:
	// 1) The subarray which is already sorted.
	// 2) Remaining subarray which is unsorted.
	// 
	// In every iteration of selection sort, the minimum 
	// element (considering ascending order) from the unsorted subarray 
	// is picked and moved to the sorted subarray.

	// Main loop over all vector elements:
	for (size_t i = 0; i < data_.size(); i++)
	{
		int index_min = i; // Index of the min element in unsorted subarray

		// index_min is equal to the index of the first element 
		// in current unsorted subbarray by default

		// Utility loop over all element of unsorted subarray 
		// (beggining with second 'cause first is i-element):
		for (size_t j = i + 1; j < data_.size(); j++)
		{
			// Finding the minimum element in an unsorted array:
			if (data_.at(j) < data_.at(index_min))
			{
				index_min = j;
			}
		}

		// If min element in unsorted subarray isn't in the beggining of it:
		if (index_min != i)
		{
			std::swap(data_.at(i), data_.at(index_min));
		}
	}
}

void Array::CocktailSort()
{
	// Explanation:
	// Cocktail Sort is a variation of Bubble sort. 
	// The Bubble sort algorithm always traverses elements from left 
	// and moves the largest element to its correct position in first 
	// iteration and second largest in second iteration and so on. 
	// Cocktail Sort traverses through a given array in both directions.
	//
	// Algorithm:
	// 
	// 1)The first stage loops through the array from left to right, 
	//   just like the Bubble Sort. During the loop, adjacent items are compared
	//   and if value on the left is greater than the value on the right, 
	//   then values are swapped. At the end of first iteration, the 
	//   largest number will reside at the end of the array.
	// 
	// 2)The second stage loops through the array in opposite direction - starting
	//   from the item just before the most recently sorted item, and moving
	//   back to the start of the array. Here also, adjacent items are compared 
	//   and swapped if required.

	int left_border = 0,
		right_border = data_.size() - 1;

	// Performs the functions of bool is_swapped identificator
	int	control = data_.size() - 1;
	
	// Main loop while vector isn't sorted:
	while (left_border < right_border)
	{
		// First loop (to the right side):
		for (size_t i = left_border; i < right_border; i++)
		{
			if (data_.at(i) > data_.at(i + 1))
			{
				std::swap(data_.at(i), data_.at(i + 1));
				control = i;
			}
		}

		right_border = control;

		// Second loop (to the left side):
		for (size_t i = right_border; i > left_border; i--)
		{
			if (data_.at(i) < data_.at(i - 1))
			{
				std::swap(data_.at(i), data_.at(i - 1));
				control = i;
			}
		}

		left_border = control;
	}
}

void Array::HeapSort()
{
	// Explanation:
	// Heap sort is a comparison-based sorting technique
	// based on Binary Heap data structure.
	//
	// Algorithm:
	// 1) Build a max heap from the input data. 
	// 2) At this point, the largest item is stored at the root of the heap.
	//    Replace it with the last item of the heap followed 
	//    by reducing the size of heap.
	// 2.1) Finally, heapify the root of the tree.
    // 3) Repeat step 2 while the size of the heap is greater than 1.

	auto index_of_max = max_element(data_.begin(), data_.end()) - data_.begin();
	int largest_elem = data_.at(index_of_max);

	// Build a heap (rearrange array):
	for (int index = data_.size() / 2 - 1; index >= 0; index--)
	{
		Heapify(index);
	}

	// One by one extraction an element from the heap:
	for (int i = data_.size() - 1; i > 0; i--) {

		// Moving current root to the end:
		std::swap(data_.at(0), data_.at(i));

		// Calling max heapify on the reduced heap:
		Heapify(0);
	}
}

// Provides the process of reshaping a binary tree into a Heap data structure
void Array::Heapify(int index_max_old)
{
	int index_max = index_max_old; // Initializing the largest element as a root

	int left_child = 2 * index_max_old + 1,
		right_child = 2 * index_max_old + 2;

	// If left child is larger than root:
	if (left_child < data_.size() && data_.at(left_child) > data_.at(index_max))
	{
		index_max = left_child;
	}
	
	// If right child is larger than root:
	if (right_child < data_.size() && data_.at(right_child) > data_.at(index_max))
	{
		index_max = right_child;
	}

	// If largest is not root:
	if (index_max != index_max_old)
	{
		std::swap(data_.at(index_max_old), data_.at(index_max));

		// Recursively heapify the affected sub-tree
		Heapify(index_max);
	}
}
