#include "engine/CollisionGrid.h"
#include <iostream>
#include <util/Helper.h>

void Helper::cout_set(std::set<int> *s) {
  if (s->size() == 0) {
    std::cout << "Empty Set" << std::endl;
    return;
  }

  for (auto i = s->begin(); i != s->end(); i++) {
    int num = (int)*i;
    std::cout << num << ", ";
  }

  std::cout << std::endl;
}

void Helper::cout_cell_ids(std::set<collision_cell_id> *s) {
  for (auto i = s->begin(); i != s->end(); i++) {
    collision_cell_id id = (collision_cell_id)*i;
    std::cout << "(" << (id >> 4) << ", " << (id - ((id >> 4) << 4)) << "), ";
  }
  std::cout << std::endl;
}

void swap(int* arr, int i1, int i2) {
	int t = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = t;
}
void Helper::quicksort(int* arr, int start, int end) {
	std::cout << "=== Sorting " << start << " to " << end << std::endl;
	if (start >= end || start < 0) return;
	int len = end - start;
	if (len < 2) { return; }

	// Partition
	int pivot_idx = start + (end - start) / 2;
	int pivot_value = arr[pivot_idx];
	int pivot_will_go = pivot_idx;
	std::cout << "Pivot idx " << pivot_idx << " value " << pivot_value << std::endl;

	// Doesn't handle duplicate values... damn
	for (int idx=start; idx <= end; idx++) {
		// std::cout << arr[idx] << " bigger than " << pivot_value << "?" << std::endl;
		if (arr[idx] > pivot_value && idx <= pivot_idx) {
			swap(arr, idx, pivot_idx);
			pivot_will_go--;
			pivot_idx = idx;
		}
		if (arr[idx] < pivot_value && idx > pivot_idx) {
			swap(arr, idx, pivot_idx);
			pivot_will_go++;
			pivot_idx = idx;
		}
	}

	swap(arr, pivot_will_go, pivot_idx);
	//arr[pivot_will_go], arr[pivot_idx] = arr[pivot_idx], arr[pivot_will_go];

  for (int i=0; i<10; i++) {
	  std::cout << arr[i] << ", ";
  }
  std::cout << std::endl;
	// Do rest of sort
	Helper::quicksort(arr, start, start+len/2);
	Helper::quicksort(arr, start+len/2+1, end);
	return;
}
