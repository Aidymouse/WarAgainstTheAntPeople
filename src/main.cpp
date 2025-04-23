
#include <ctime>
#include <iostream>

#include <ProjectConfig.h>
#include <engine/Engine.h>

#include <util/Helper.h>

void cout_arr(int *a, int start, int end) {
  for (int i = start; i <= end; i++) {
    std::cout << a[i] << ", ";
  }
}

void mergesort(int *arr, int start_idx, int end_idx) {

  int len = (end_idx - start_idx) + 1;

  if (len == 1)
    return;
  if (len == 2) {
    if (arr[0] > arr[1]) {
      int t = arr[0];
      arr[0] = arr[1];
      arr[1] = t;
    }
    return;
  }

  int mid_idx = start_idx + len / 2 - 1;

  int start_one = start_idx;
  int end_one = (mid_idx);

  std::cout << "Copying idxs " << start_one << " to " << end_one << std::endl;
  int copy_one[end_one - start_one + 1];
  for (int i = start_one; i <= end_one; i++) {
    copy_one[i - start_one] = arr[i];
  }
  cout_arr(copy_one, 0, end_one - start_one);
  std::cout << std::endl;

  int start_two = mid_idx + 1;
  int end_two = end_idx;
  std::cout << "Copying " << start_two << " to " << end_two << std::endl;
  int copy_two[end_two - start_two + 1];
  for (int k = start_two; k <= end_two; k++) {
    copy_two[k - start_two] = arr[k];
  }
  cout_arr(copy_two, 0, end_two - start_two);
  std::cout << std::endl;

  mergesort(copy_one, 0, end_one - start_one);
  mergesort(copy_two, 0, end_two - start_two);

  int l = 0;
  int r = 0;
  for (int i = start_idx; i <= end_idx; i++) {
    if (l <= end_one - start_one &&
        (r > end_two - start_two || copy_one[l] <= copy_two[r])) {
      arr[i] = copy_one[l];
      l++;
    } else {
      arr[i] = copy_two[r];
      r++;
    }
  }
}

int main() {
  // int LEN = 5;
  // int a[LEN] = {3, 2, 7, 4, 55};
  //
  // mergesort(a, 0, LEN - 1);
  //
  // cout_arr(a, 0, LEN - 1);

  srand(time(NULL));

  std::cout << "Graphics Path: " << GRAPHICS_PATH << std::endl;

  Engine game;
  game.run();
}
