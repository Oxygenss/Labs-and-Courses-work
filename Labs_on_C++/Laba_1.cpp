#include <iostream>
using namespace std;
struct elem {
  int value;
  int div;
  int index;
};
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void swap(elem *xp, elem *yp) {
  elem temp = *xp;
  *xp = *yp;
  *yp = temp;
}
class Array {
protected:
  int size = 0, arr[50];

public:
  int search_max() {
    int max = arr[0];
    for (int i = 0; i < size; i++) {
      if (arr[i] > max) {
        max = arr[i];
      }
    }
    return max;
  }
  void set_array(int i, int value) {
    size++;
    arr[i] = value;
  }
  void get_array() {
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
  }
};
class Array_up : public Array {
public:
  void bubbleSort(elem arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
        if (arr[j].div >= arr[j + 1].div) {
          swap(&arr[j], &arr[j + 1]);
        }
      }
    }
  }
  bool sort_arr() {
    elem change[25];
    int count = 0;
    int j = size - 1, i = 0;
    while (j > i) {
      swap(arr[i], arr[j]);
      j--;
      i++;
    }
    for (int i = 0; i < size; i++) {
      for (int j = 1; j <= arr[i]; j++) {
        if (arr[i] % j == 0) {
          count++;
        }
      }
      change[i].value = arr[i];
      change[i].index = i;
      change[i].div = count;
      count = 0;
    }
    bubbleSort(change, size);
    int l = size;
    for (int i = 0; i < size; i++) {
      if (i != change[i].index) {
        size = 0;
        return 0;
      }
    }
    size = 0;
    return 1;
  }
};
int main() {
  setlocale(LC_ALL, "ru");
  int row, column, array[100][100];
  cout << "Количество строк: ";
  cin >> row;
  cout << "Количесвто столбцов: ";
  cin >> column;
  cout << endl;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      cin >> array[i][j];
    }
  }
  cout << endl;
  Array one;
  int max, temp;
  for (int i = 0; i < row; i++) {
    one.set_array(i, array[i][0]);
  }
  max = one.search_max();
  for (int j = 1; j < column; j++) {
    for (int i = 0; i < row; i++) {
      one.set_array(i, array[i][j]);
    }
    temp = one.search_max();
    if (temp < max) {
      max = temp;
    }
  }
  cout << "===================================================================="
          "=========================="
       << endl;
  cout << "Минимальный из максимальных элементов столбцов == " << max << endl;
  cout << "===================================================================="
          "=========================="
       << endl
       << endl;
  Array_up two;
  int count = 0, sum = 0;
  for (int i = 0; i < column; i++) {
    two.set_array(i, array[0][i]);
  }
  sum += two.sort_arr();
  for (int j = 1; j < row; j++) {
    for (int i = 0; i < column; i++) {
      two.set_array(i, array[j][i]);
    }
    sum += two.sort_arr();
  }
  cout << "===================================================================="
          "=========================="
       << endl;
  cout << "Количество строк, упорядоченных по убыванию количество элементов == "
       << sum << endl;
  cout << "===================================================================="
          "=========================="
       << endl;
  return 0;
}