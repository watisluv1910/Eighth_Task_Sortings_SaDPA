#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H

#include <vector>

class Array
{
public:

	// Default constructor initializes vector with zero value
	Array() : data_({ 0 }) {}; 

	// Method for vector filling
	bool FillData(const size_t &size, 
		const unsigned &filling_method, const unsigned &start_state = 0);

	void SelectionSort();
	void CocktailSort();
	void HeapSort();
private:

	// Comparator for arranging elements in descending order 
	// for a built-in sort() function
	struct {

		bool operator()(int a, int b) const { return a > b; }

	} comparator;

	std::vector<int> data_;

	// Utility method for HeapSort sorting, which provides heap building
	void Heapify(int new_largest_elem);
};

#endif