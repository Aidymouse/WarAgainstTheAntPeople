#pragma once

#include "engine/CollisionGrid.h"
#include <functional>
#include <set>

namespace Helper {
void cout_set(std::set<int> *s);
void cout_cell_ids(std::set<collision_cell_id> *s);

// template <typename T> void swap(T *arr, T i1, T i2) {
//   T t = arr[i1];
//   arr[i1] = arr[i2];
//   arr[i2] = t;
// }
//
// // Compare returns -1 if second input is to go before first, 0
// // if they're equal, or 1 ifit's meant to go after
// // TODO: time complexity of this
// template <typename T>
// void quicksort(T *arr, int start, int end, std::function<int(T, T)> compare)
// {
//   // std::cout << "=== Sorting " << start << " to " << end << ": ";
//   // for (int i =start; i<=end; i++) {
//   // 	std::cout << arr[i] << ", ";
//   // }
//   // std::cout << std::endl;
//
//   if (start >= end || start < 0)
//     return;
//   int len = (end - start) + 1;
//   if (len < 2) {
//     return;
//   }
//   // if (len == 2) {
//   // 	if (arr[start] > arr[end]) swap(arr, start, end);
//   // 	return;
//   // }
//
//   // Partition
//   int pivot_idx = start + len / 2;
//   int pivot_value = arr[pivot_idx];
//   int pivot_will_go = pivot_idx;
//   // std::cout << "Pivot idx " << pivot_idx << " value " << pivot_value <<
//   // std::endl;
//
//   for (int idx = start; idx <= end; idx++) {
//     // std::cout << arr[idx] << " bigger than " << pivot_value << "?" <<
//     // std::endl;
//
//     if (idx == pivot_idx || idx == pivot_will_go) {
//       continue;
//     }
//
//     if (compare(arr[idx], pivot_value) > 0 && idx < pivot_will_go) {
//       swap<T>(arr, idx, pivot_will_go);
//       if (pivot_will_go == pivot_idx) {
//         pivot_idx = idx;
//       }
//       pivot_will_go--;
//       idx--;
//
//     } else if (compare(arr[idx], pivot_value) <= 0 && idx > pivot_will_go) {
//       swap<T>(arr, idx, pivot_will_go);
//       if (pivot_will_go == pivot_idx) {
//         pivot_idx = idx;
//       }
//       pivot_will_go++;
//       idx--;
//     }
//   }
//
//   // You have to do this because...
//   // I think it's something to do with the fact we go up from the bottom and
//   how
//   // we adjust the pivot_will_go. Forgor
//   if (pivot_value < arr[pivot_will_go] && pivot_idx < pivot_will_go) {
//     // std::cout << "Adjusting Pivot" << std::endl;
//     pivot_will_go--;
//   }
//
//   // std::cout << "Swapping " << pivot_idx << " with " << pivot_will_go <<
//   // std::endl;
//   //
//   swap<T>(arr, pivot_will_go, pivot_idx);
//
//   // std::cout << "Done partitioning: ";
//   // 	bool validate = true;
//   // for (int i=start; i<=end; i++) {
//   // std::cout << arr[i] << ", ";
//   //  if (i < pivot_will_go && arr[i] > pivot_value) validate = false;
//   //  if (i > pivot_will_go && arr[i] < pivot_value) validate = false;
//   // }
//   //  if (validate) std::cout << " PASS";
//   //  if (!validate) std::cout << " FAIL";
//   //  std::cout << std::endl;
//   //  	if (validate == false) {
//   // 	return false;
//   // }
//
//   // return validate;
//
//   // Do rest of sort
//   Helper::quicksort<T>(arr, start, pivot_will_go - 1, compare);
//   Helper::quicksort<T>(arr, pivot_will_go + 1, end, compare);
//   return;
// }

} // namespace Helper
