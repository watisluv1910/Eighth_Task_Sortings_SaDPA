#include "array_class.h"

#include <algorithm>
#include <iterator>

int Array::FillData(const size_t& size, 
	const unsigned& filling_method, 
	const unsigned& start_state)
{
	if (!size) return 0;

	srand(time(0));

	data_.clear();

	data_.resize(size);

	for (auto& element : data_)
	{
		switch (filling_method)
		{
		case 1:

			std::cin >> element;

			// cin.clear and cin.ignore are used to prevent fake input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		case 2:

			element = static_cast<int>(rand() % 200 - 100);
			break;
		default:

			return 0;
		}
	}
	
	switch (start_state)
	{
	case 1:
		break;
	case 2:

		std::sort(data_.begin(), data_.end());
		break;
	case 3:

		std::sort(data_.begin(), data_.end(), comparator);
		break;
	default:

		return 0;
	}
}

void Array::SelectionSort()
{
	for (size_t i = 0; i < data_.size(); i++)
	{
		int min_index = i;

		for (size_t j = i + 1; j < data_.size(); j++)
		{
			if (data_.at(j) < data_.at(min_index))
			{
				min_index = j;
			}
		}

		if (min_index != i)
		{
			std::swap(data_.at(i), data_.at(min_index));
		}
	}
}

void Array::CocktailSort()
{
	int left_border = 0,
		right_border = data_.size() - 1,
		control = data_.size() - 1;
	
	while (left_border < right_border)
	{
		for (size_t i = left_border; i < right_border; i++)
		{
			if (data_.at(i) > data_.at(i))
			{
				std::swap(data_.at(i), data_.at(i + 1));
				control = i;
			}
		}

		right_border = control;

		for (size_t i = right_border; i > left_border; i--)
		{
			if (data_.at(i) < data_.at(i))
			{
				std::swap(data_.at(i), data_.at(i + 1));
				control = i;
			}
		}

		left_border = control;
	}
}

void Array::HeapSort()
{
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
