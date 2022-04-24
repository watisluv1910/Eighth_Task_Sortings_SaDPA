#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H

#include <iostream>
#include <vector>

class Array
{
public:

	Array() : data_({ 0 }) {};
	int FillData(const size_t &size, 
		const unsigned &filling_method, const unsigned &start_state = 0);

	void SelectionSort();
	void CocktailSort();
	void HeapSort();
private:

	struct {

		bool operator()(int a, int b) const { return a > b; }

	} comparator;

	std::vector<int> data_;
	void Heapify(int new_largest_elem);
};

#endif