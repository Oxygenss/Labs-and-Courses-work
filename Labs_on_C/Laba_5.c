#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void swap(int *x, int *y) {
  int buff = *x;
  *x = *y;
  *y = buff;
}
void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
void fill_array(int *arr, int *size) {
  printf("Enter the number of elements: ");
  scanf_s("%d", &(*size));
  arr = (int *)calloc((*size), sizeof(int));
  if (arr == NULL) {
    printf("Память не выделилась");
    exit(0);
  }
  print_array(arr, (*size));
  for (int i = 0; i < (*size); i++) {
    scanf_s("%d", &arr[i]);
  }
  printf("\n");
}
void insertion_sort(int *arr, int size) {
  for (int i = 1; i < size; i++) {
    for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
      swap(&arr[j], &arr[j - 1]);
      print_array(arr, size);
    }
    printf("\n");
  }
}
/*void insert_sort(int *arr, int size)
{
for (int i = 1; i < size; i++)
{
int j = i;
while (j > 0 && arr[j - 1] > arr[j])
{
int temp = arr[j - 1];
arr[j - 1] = arr[j];
arr[j] = temp;
j--;
}
}
}
*/
void selection_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (arr[i] > arr[j]) {
        swap(&arr[i], &arr[j]);
        print_array(arr, size);
      }
    }
    printf("\n");
  }
}
void buble_sort(int *arr, int size) {
  bool exit = false;
  while (!exit) {
    exit = true;
    for (int i = 0; i < size - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        print_array(arr, size);
        exit = false;
      }
    }
    printf("\n");
  }
}
void shaker_sort(int *arr, int size) {
  int left = 1;
  int right = size - 1;
  while (left <= right) {
    for (int i = left; i <= right; i++) {
      if (arr[i - 1] > arr[i]) {
        swap(&arr[i], &arr[i - 1]);
        print_array(arr, size);
      }
    }
    printf("\n");
    right--;
    for (int i = right; i >= left; i--) {
      if (arr[i - 1] > arr[i]) {
        swap(&arr[i], &arr[i - 1]);
        print_array(arr, size);
      }
    }
    printf("\n");
    left++;
  }
}
int binarySearch(int *arr, int item, int low, int high) {
  if (high <= low) {
    return (item > arr[low]) ? (low + 1) : low;
  }
  int mid = (low + high) / 2;
  if (item == arr[mid]) {
    return mid + 1;
  }
  if (item > arr[mid]) {
    return binarySearch(arr, item, mid + 1, high);
  }
  return binarySearch(arr, item, low, mid - 1);
}
void insertionSort(int *arr, int size) {
  int i, loc, j, k, selected;
  for (i = 1; i < size; ++i) {
    j = i - 1;
    selected = arr[i];
    loc = binarySearch(arr, selected, 0, j);
    while (j >= loc) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = selected;
  }
}
void quick_sort(int *arr, int first, int last) {
  if (first < last) {
    int left = first;
    int right = last;
    int middle = arr[(first + last) / 2];
    do {
      while (arr[left] < middle) {
        left++;
      }
      while (arr[right] > middle) {
        right--;
      }
      if (left <= right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
      }
    } while (left < right);
    quick_sort(arr, first, right);
    quick_sort(arr, left, last);
  }
}
int main() {
  setlocale(LC_ALL, "Ru");
  int size;
  int *arr = NULL;
  printf("Enter the number of elements: ");
  scanf_s("%d", &size);
  arr = (int *)calloc(size, sizeof(int));
  if (arr == NULL) {
    printf("Память не выделилась");
    exit(0);
  }
  print_array(arr, size);
  for (int i = 0; i < size; i++) {
    scanf_s("%d", &arr[i]);
  }
  printf("\n");
  // insertion_sort(arr, size);
  // selection_sort(arr, size);
  // buble_sort(arr, size);
  // shaker_sort(arr, size);
  // insertionSort(arr, size);
  quick_sort(arr, 0, size - 1);
  print_array(arr, size);
  free(arr);
  return 0;
}