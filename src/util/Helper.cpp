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
	std::cout << "=== Sorting " << start << " to " << end << ": ";
	for (int i =start; i<=end; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;

	if (start >= end || start < 0) return;
	int len = (end - start)+1;
	if (len < 2) { return; }
	// if (len == 2) {
	// 	if (arr[start] > arr[end]) swap(arr, start, end);
	// 	return;
	// }

	// Partition
	int pivot_idx = start + len / 2;
	int pivot_value = arr[pivot_idx];
	int pivot_will_go = pivot_idx;
	std::cout << "Pivot idx " << pivot_idx << " value " << pivot_value << std::endl;

	// Some funny fnagling to get this to be in place
	for (int idx=start; idx <= end; idx++) {
		// std::cout << arr[idx] << " bigger than " << pivot_value << "?" << std::endl;

		if (arr[idx] > pivot_value && idx < pivot_will_go) {
			swap(arr, idx, pivot_will_go);
			if (pivot_will_go == pivot_idx) {
				pivot_idx = idx;
			}
			pivot_will_go--;

		} else if (arr[idx] <= pivot_value && idx > pivot_will_go) {
			swap(arr, idx, pivot_will_go);
			if (pivot_will_go == pivot_idx) {
				pivot_idx = idx;
			}
			pivot_will_go++;

		}
	}

	if (arr[pivot_will_go] > pivot_value) {
		pivot_will_go--;
	}

	if (pivot_will_go >= start) {
		swap(arr, pivot_will_go, pivot_idx);
	}

	std::cout << "Done partitioning: ";
  	bool validate = true;
  for (int i=start; i<=end; i++) {
   std::cout << arr[i] << ", ";
   if (i < pivot_will_go && arr[i] > pivot_value) validate = false;
   if (i > pivot_will_go && arr[i] < pivot_value) validate = false;
  }
  if (validate) std::cout << " PASS";
  if (!validate) std::cout << " FAIL";
  std::cout << std::endl;

	// Do rest of sort
	Helper::quicksort(arr, start, pivot_will_go-1);
	Helper::quicksort(arr, pivot_will_go+1, end);
	return;
}
