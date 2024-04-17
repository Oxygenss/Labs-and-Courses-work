#include <ctype.h>
#include <locale.h> //Для использование русского языка
#include <stdio.h> //Подключение всех необходимых библеотек
#include <stdlib.h>
int glub; // Переменная, хранящая глубину стеков
typedef struct Stack // Описание структуры данных "Стек"
{
  struct Stack *next; // Следующий элемент стека
  int data; // Целочисленное значение, которое хранит элемент стека
} Stack;
typedef struct Matrix // Описание структуры данных "Динамическая матрица"
{
  struct Matrix *next; // Следующий элемент строки матрицы
  struct Matrix *prev; // Предыдущий элемент строки матрицы
  struct Matrix *down; // Нижний элемент столбца матрицы
  struct Matrix *up; // Верхний элемент столбца матрицы
  struct Stack
      *stack; // Указатель на стек, который хранит каждый элемент матрицы
} Matrix;
Stack *stack_menu(Stack *head); // Прототип функции, которая содержит меню
                                // функций стека и вызовы этих функций
void print_stack(Stack *head);
int obrabotka() // Функция, отвечающая за правильность введенного символа
                // пользователя
{
  char c[10];            // Массив типа char
  scanf_s("%s", &c, 10); // Вводим массив
  while (atoi(c) == 0) // Функция возвращает 0, если мы ввели в массив символы,
                       // не являющиеся числами
  {
    printf("Вы ввели недопустимое значени, попробуйте еще раз: ");
    scanf_s("%s", &c, 10);
  }
  return atoi(c); // Возвращаем введенное нами значение
}
inline void error() // Сообщение, котороя выводит информацию о том, что работа с
                    // матрицей уже начата
{
  printf("Вы ещё не начали работу с матрицей\n");
}
inline void error_stack() // Сообщейние, которое выводи информацию о том, что
                          // работа со стеком уже начата
{
  printf("Вы ещё не начали работу со стеком\n");
}
void start_matrix(int *flag) {
  if ((*flag)) {
    printf("Вы уже начали работу с матрицей\n");
  } else {
    (*flag) = 1;
    printf("Вы успешно начали работу с матрицей\n");
  }
}
void start_stack(int *flag) {
  if ((*flag)) // Проверяем, что работа с матрицей еще не начата
  {
    printf("Вы уже начали работу со стеком\n");
  } else {
    (*flag) = 1;
    printf("Вы успешно начали работу со стеком\n");
  }
}
void free_list(Stack *head) // Функция, которая очищает стек
{
  if (head) // Проверяем, что стек не пуст
  {
    while (head) // Цикл работает, пока существую элементы стека
    {
      Stack *temp = head; // Копия элемента стека
      head = head->next; // Двигаем указаетель на следующий элемент стека
      free(temp);        // Очищаем элемент стека
    }
  } else {
    printf("Стек уже пуст\n");
  }
}
void show_top(Stack *head) // Функция, которая показывает вершину стека
{
  if (head) {
    while (head->next) // Цикл работает, пока существует следующий элемент стека
    {
      head = head->next; // Двигем указатель на следующий элемент стека
    }
    printf("Вершина стека: ");
    printf("%d\n", head->data); // Выводим в консоль вершину стека
  } else {
    printf("Стек пуст\n");
  }
}
void remove_top(Stack *head) // Функция, которая удаляет вершину стека
{
  Stack *temp = head->next; // Копия следующего элемента стека
  while (temp->next) // Цикл работает, пока существует следующий элемент стека
  {
    temp = temp->next; // Двигаем копию указателя на начало стека на следующий
                       // элемент
    head = head->next; // Двигаем указатель на начало стека на следующий элемент
  }
  free(temp); // Очищаем вершину стека///////////////////////
  head->next = NULL; // Нулим указатель на вершину стека
}
void get_top(Stack *head) // функция, которая берет вершину стека
{
  if (head) {
    while (head->next) {
      head = head->next;
    }
    char a = head->data; // Берем вершину стека
    printf("Вы успешно взяли вершину стека: ");
    printf("%d\n\n", a); // Выводим вершину стека
    remove_top(head);    // Удаляем вершину стека
    printf("Стек: ");
    print_stack(head); // Печатаем стек
    printf("\n");
  } else {
    printf("Стек пуст\n");
  }
}
void change_top(Stack *head) // Функция, которая изменяет вершину стека
{
  if (head) {
    int n;
    printf("Введите символ, на который хотите поменять: ");
    n = obrabotka();
    while (head->next) {
      head = head->next;
    }
    head->data = n; // Изменяем вершину стека на новое значение
  } else {
    printf("Стек пуст\n");
  }
}
void add_stack(Stack *head) // Функция, которая добавляет элемент в стек
{
  printf("Введите число: ");
  int n;
  n = obrabotka();
  Stack *node =
      (Stack *)malloc(sizeof(Stack)); // Выделяем память под новый элемент
  if (node == NULL) // Проверка на то, что память выделилась
  {
    printf("No data!");
    exit(0);
  }
  while (head->next) {
    head = head->next;
  }
  head->next = node; // Делаем новый элемент вершиной стека
  node->data = n; // Присваиваем новому элементу целочисленное значение
  node->next = NULL; // Нулим указатель на следующий элемент созданного элемента
}
Stack *create_node_stack() // Функция, которая создает новый элемент стека, если
                           // в стеке еще нет элементов
{
  printf("Введите число: ");
  int n;
  n = obrabotka(); // Вводим новое значение
  Stack *node = (Stack *)malloc(sizeof(Stack));
  if (node == NULL) {
    printf("Память не выделилиась");
    exit(0);
  }
  node->data = n;
  node->next = NULL;
  return node;
}
void print_stack(Stack *head) // Функция, которая печатает стек
{
  if (head) // Проверка на то, что стек не пуст
  {
    while (head) // Цикл работает, пока существуют элементы в стеке
    {
      printf("%d", head->data);
      printf(" ");
      head = head->next;
    }
  } else {
    printf("Стек пуст\n");
  }
}
void print_matrix(Matrix *head,
                  Matrix *tail) // Функция, которая печатает матрицу
{
  if (head) {
    while (head) {
      Matrix *temp = head;
      while (temp) // Выводим элементы первой строки
      {
        print_stack(temp->stack);
        printf(" | ");
        temp = temp->next;
      }
      printf("\n");
      printf("----------\n");
      if (head->down) // Переходим на следующую строку
      {
        head = head->down;
      } else {
        break;
      }
    }
  } else {
    printf("Матрица пуста\n");
  }
}
Matrix *create_node() // Функция, которая создает новый элемент матрицы
{
  Matrix *node = (Matrix *)malloc(
      sizeof(Matrix)); // Выделяет память под новый элемент матрицы
  if (node == NULL) {
    printf("Память не выделилиась");
    exit(0);
  }
  node->stack = NULL;
  node->stack = stack_menu(node->stack); // Создаем стек в новом элементе
                                         // матрицы
  node->next = NULL; // Нулим все указатели нового элемента
  node->prev = NULL;
  node->up = NULL;
  node->down = NULL;
  return node; // Возвращаем новый элемент
}
void add_line(Matrix *head, Matrix *tail, int *line,
              int *column) // Функция добавления строк
{
  if (!head) {
    head = create_node(); // Сооздаем элемент, если матрица пуста
    tail = head;
    (*line)++;   // Увеличиваем счетчик строк
    (*column)++; // Увеличиваем счетчик столбцов
  } else {
    int i = 1;                    // Счетчик строк матрицы
    Matrix *temp = create_node(); // Создаем новый элемент строки
    while (i < (*column)) // Создаем новую строку матрицы
    {
      Matrix *node = create_node();
      temp->next = node;
      node->prev = temp;
      temp = temp->next;
      i++;
    }
    if (tail->down) // Спускаемся по последней строки матрицы
    {
      while (tail->down) {
        tail = tail->down;
      }
    }
    while (tail) // Связываем указателями нашу матрицу с созданной строкой
    {
      tail->down = temp;
      temp->up = tail;
      tail = tail->prev;
      temp = temp->prev;
    }
    (*line)++;
  }
}
void add_column(Matrix *head, Matrix *tail, int *line,
                int *column) // Функция добавления столбцов
{
  if (head == NULL) {
    head = create_node();
    tail = head;
    (*line)++;
    (*column)++;
  } else {
    int i = 1; // Счетчик количества столбцов в матрице
    Matrix *temp = create_node(); // СОздаем новый элемент столбца
    while (i < (*line)) // Создаем новый столбец
    {
      Matrix *node = create_node();
      temp->down = node;
      node->up = temp;
      temp = temp->down;
      i++;
    }
    if (tail->down) // Двигаемся до последнего столбца матрицы
    {
      while (tail->down) {
        tail = tail->down;
      }
    }
    while (tail) // Связываем указателями нашу матрицы с новым столбцом
    {
      tail->next = temp;
      temp->prev = tail;
      tail = tail->up;
      temp = temp->up;
    }
    (*column)++;
  }
}
void number_of_rows(
    Matrix *head) // Функция, которая считает количество строк в матрице
{
  if (head) {
    int count = 1;
    while (head->down) {
      head = head->down;
      count++;
    }
    printf("Количество строк в матрице == ");
    printf("%d\n", count);
  } else {
    printf("Матрица пуста\n");
  }
}
void number_of_columns(
    Matrix *head) // Функция, которая считает количество столбцов в матрице
{
  if (head) {
    int count = 1;
    while (head->next) {
      head = head->next;
      count++;
    }
    printf("Количество столбцов в матрице == ");
    printf("%d\n", count);
  } else {
    printf("Матрица пуста\n");
  }
}
int check_size(
    int n, int m, int line,
    int column) // Функция, которая проверяет ввод количества строк и столбцов
{
  if (n > line) // Проверяем количесвто строк
  {
    system("cls");
    printf("Введенное вами значение превышает количество строк в матрице, "
           "попробуйте заново\n\n");
    return 0;
  } else if (m > column) // Проверяем количество столбцов
  {
    system("cls");
    printf("Введенное вами значение превышает количество столбцов в матрице, "
           "попробуйте заново\n\n");
    return 0;
  } else if (n == 0 ||
             m == 0) // Проверяем, что введенные значение не равны нулю
  {
    system("cls");
    printf(
        "Введенное вами значение не может быть нулевым, попробуйте заново\n\n");
    return 0;
  } else {
    return 1;
  }
}
int check_size_line(
    int n, int line) // Функция, которая проверяет ввод количества строк
{
  if (n > line) {
    system("cls");
    printf("Введенное вами значение превышает количество строк в матрице, "
           "попробуйте заново\n\n");
    return 0;
  } else if (n == 0) {
    system("cls");
    printf(
        "Введенное вами значение не может быть нулевым, попробуйте заново\n\n");
    return 0;
  } else {
    return 1;
  }
}
int check_size_column(
    int m, int column) // Функция, которая проверяет ввод количества столбцов
{
  if (m > column) {
    system("cls");
    printf("Введенное вами значение превышает количество столбцов в матрице, "
           "попробуйте заново\n\n");
    return 0;
  } else if (m == 0) {
    system("cls");
    printf(
        "Введенное вами значение не может быть нулевым, попробуйте заново\n\n");
    return 0;
  } else {
    return 1;
  }
}
void show_element(Matrix *head, int line,
                  int column) // Функция, которая показывет элемент матрицы
{
  if (head) {
    int i = 1, n, m;
    while (1) {
      printf("Выберите элемент матрицы, который хотете посмотреть\n\n");
      printf("Введите номер строки: ");
      n = obrabotka(); // Вводим номер строки
      printf("Введите номер столбца: ");
      m = obrabotka(); // Вводим номер столбца
      printf("\n");
      if (check_size(n, m, line, column)) // Проверяем введенные значения
      {
        break;
      }
    }
    if (head->down) // Двигаем указатель до нужной строки
    {
      while (i < n) {
        head = head->down;
        i++;
      }
    } else {
      i++;
    }
    i = 1;
    if (head->next) // Двигаем указатель до нужного столбца
    {
      while (i < m) {
        head = head->next;
        i++;
      }
    } else {
      i++;
    }
    printf("[%d][%d] = ", n, m);
    print_stack(head->stack); // Печатаем наш элемент
    printf("\n");
  } else {
    printf("Матрица пуста\n");
  }
}
void get_element(Matrix *head, int line,
                 int column) // Функция, которая берет элемент матрицы
{
  if (head) {
    int i = 1, n, m;
    while (1) {
      printf("Выберите элемент матрицы, который хотете посмотреть\n\n");
      printf("Введите номер строки: ");
      n = obrabotka();
      printf("Введите номер столбца: ");
      m = obrabotka();
      printf("\n");
      if (check_size(n, m, line, column)) {
        break;
      }
    }
    if (head->down) {
      while (i < n) {
        head = head->down;
        i++;
      }
    } else {
      i++;
    }
    i = 1;
    if (head->next) {
      while (i < m) {
        head = head->next;
        i++;
      }
    } else {
      i++;
    }
    Stack *temp = head->stack; // Создаем новую переменную и присваиваем ей,
                               // выбранный нами элемент(берем)
    printf("[%d][%d] = ", n, m);
    print_stack(temp); // Печатаем элемент, который мы взяли
    printf("\n");
  } else {
    printf("Матрица пуста\n");
  }
}
void change_element(Matrix *head, int line,
                    int column) // Функция,которая изменяет элемент матрицы
{
  if (head) {
    int i = 1, n, m;
    while (1) {
      printf("Выберите элемент матрицы\n\n");
      printf("Введите номер строки: ");
      n = obrabotka();
      printf("Введите номер столбца: ");
      m = obrabotka();
      printf("\n");
      if (check_size(n, m, line, column)) {
        break;
      }
    }
    if (head->down) {
      while (i < n) {
        head = head->down;
        i++;
      }
    } else {
      i++;
    }
    i = 1;
    if (head->next) {
      while (i < m) {
        head = head->next;
        i++;
      }
    } else {
      i++;
    }
    head->stack = stack_menu(
        head->stack); // Спускаемся на второй уровень, чтобы изменить элемент
  } else {
    printf("Матрица пуста\n");
  }
}
void delete_line(Matrix *head,
                 int *line) // Функция, которая удаляет строку матрицы
{
  Matrix *temp = head->down;
  while (temp->down) // Спускаемся на последнюю строку
  {
    temp = temp->down;
    head = head->down;
  }
  while (temp) // Цикл работает, пока в сроке есть элементы
  {
    Matrix *temp1 = temp; // Создаем копию последней строки
    free_list(temp->stack); // Очищаем стек в элементе строки
    head->down = NULL; // НУлим указатель на нижний элемент
    head = head->next; // Двигаем указаеть
    temp = temp->next; // Двигаем копию указаетля
    free(temp1);       // Очищаем элемент строки
  }
  (*line)--; // Уменьшаем счетчик количества строк
  printf("Вы успешно удалили строку матрицы\n");
}
void show_line(Matrix *head, int line) // Функция, которая показывает строку
{
  if (head) {
    int i = 1, n;
    while (1) {
      printf("Выберите элемент матрицы\n\n");
      printf("Введите номер строки: ");
      n = obrabotka();
      printf("\n");
      if (check_size_line(n, line)) {
        break;
      }
    }
    while (i != n) {
      head = head->down;
      i++;
    }
    print_stack(head->stack);
    printf(" ");
    while (head->next) {
      head = head->next;
      print_stack(head->stack);
      printf(" ");
    }
    printf("\n");
  } else {
    printf("Матрица пуста\n");
  }
}
void show_column(Matrix *head,
                 int column) // Функция, которая показывает столбец
{
  if (head) {
    int i = 1, m;
    while (1) {
      printf("Выберите элемент матрицы\n\n");
      printf("Введите номер столбца: ");
      m = obrabotka();
      printf("\n");
      if (check_size_column(m, column)) {
        break;
      }
    }
    while (i != m) {
      head = head->next;
      i++;
    }
    print_stack(head->stack);
    printf("\n\n");
    while (head->down) {
      head = head->down;
      print_stack(head->stack);
      printf("\n\n");
    }
  } else {
    printf("Матрица пуста\n");
  }
}
void get_line(Matrix *head, Matrix *tail, int *line,
              int *column) // Функция взятия строк
{
  if (head) {
    if (head->down) {
      printf("Строка, которую вы взяли: ");
      show_line(head, (*line)); // Показываем выбранную строку
    } else {
      printf("Строка, которую вы взяли: ");
      print_matrix(head, tail); // Показываем единственную строку
    }
  } else {
    printf("Матрица пуста\n");
  }
}
void get_column(Matrix *head, Matrix *tail, int *line,
                int *column) // Функция взятия столбцов
{
  if (head) {
    if (head->next) {
      printf("Столбец, которую вы взяли: ");
      show_column(head, (*column)); // Показываем выбранный столбец
    } else {
      printf("Столбец, которую вы взяли: ");
      print_matrix(head, tail); // Показываем единственный столбец
    }
  } else {
    printf("Матрица пуста\n");
  }
}
void delete_line(Matrix *head, Matrix *tail, int *line,
                 int *column) // Функция удаления строк
{
  if (head) {
    if (!head->down) // Проверяем, что в матрице всего одна строка
    {
      while (head) {
        Matrix *temp = head;
        free_list(head->stack);
        head = head->next;
        free(temp);
      }
      head = NULL; // Нулим указатель на начало первой строки
      tail = NULL; // Нулим указатель на конец первой строки
      line--;   // Уменьшаем счетчик строк
      column--; // Уменьшаем счетчик столбцов
      printf("Вы успешно удалили строку матрицы\n");
    } else {
      Matrix *temp = head->down;
      while (temp->down) // Спускаемся на последнюю строку
      {
        temp = temp->down;
        head = head->down;
      }
      while (temp) // Цикл работает, пока в сроке есть элементы
      {
        Matrix *temp1 = temp; // Создаем копию последней строки
        free_list(temp->stack); // Очищаем стек в элементе строки
        head->down = NULL; // НУлим указатель на нижний элемент
        head = head->next; // Двигаем указаеть
        temp = temp->next; // Двигаем копию указаетля
        free(temp1);       // Очищаем элемент строки
      }
      (*line)--; // Уменьшаем счетчик количества строк
      printf("Вы успешно удалили строку матрицы\n");
    }
  } else {
    printf("Матрица пуста\n");
  }
}
void delete_column(Matrix *head, Matrix *tail, int *line,
                   int *column) // Функция удаления столбцов
{
  if (head) {
    if (!head->next) {
      while (head) {
        Matrix *temp = head;
        free_list(head->stack);
        head = head->down;
        free(temp);
      }
      head = NULL;
      tail = NULL;
      line--;
      column--;
      printf("Вы успешно удалили столбец матрицы\n");
    } else {
      Matrix *temp = head->next;
      while (temp->next) {
        temp = temp->next;
        head = head->next;
      }
      while (temp) {
        Matrix *temp1 = temp;
        free_list(temp->stack);
        head->next = NULL;
        head = head->down;
        temp = temp->down;
        free(temp1);
      }
      (*column)--;
      printf("Вы успешно удалили столбец матрицы\n");
    }
  } else {
    printf("Матрица пуста\n");
  }
}
void delete_matrix(Matrix *head, Matrix *tail, int *line,
                   int *column) // Функция очистки матрицы
{
  if (head) // Проверяем, что матрица еще не пуста
  {
    while (head) {
      Matrix *temp = head;
      while (temp) {
        free_list(temp->stack);
        temp = temp->next;
      }
      if (head->down) {
        head = head->down;
      } else {
        break;
      }
    }
    (*line) = 0;
    (*column) = 0;
    head = NULL; // Нулим указатель на начало первой строки матрицы
    tail = NULL; // Нулим указатель на конец первой строки матрицы
    printf("Вы успешно очистили матрицу\n");
  } else {
    printf("Матрица уже пуста\n");
  }
}
void main_menu() // Функция, которая содержит меню функций и их вызовы
{
  Matrix *head = NULL; // Создаем указатель на начало первой строки матрицы
  Matrix *tail = NULL; // Создаем указатель на конец первой строки матрицы
  int line = 0;        // Содержит количесвто строк
  int column = 0;      // Содержит количесвто столбцов
  int choice;          // Переменная для Switch
  int flag = 0; // Хранит информацию о том, начали ли мы работу с матрицей
  printf("Введите глубину ваших стеков: ");
  glub = obrabotka(); // Ввод глубины стеков
  while (1) {
    printf("\n"); // Меню функций
    printf("1 -> Начать работу с матрицей\n");
    printf("2 -> Сделать матрицу пустой\n");
    printf("3 -> Проверить матрицу на пустату*\n");
    printf("4 -> Определить количество строк в матрице\n");
    printf("5 -> Определить количество столбцов в матрице\n");
    printf("6 -> Показать элемент с индексами NxM\n");
    printf("7 -> Взять элемент с индексами NxM\n");
    printf("8 -> Изменить элемент с индексами NxM\n");
    printf("9 -> Показать строку с индексом N\n");
    printf("10 -> Показать столбец с индексом M\n");
    printf("11 -> Удалить строку\n");
    printf("12 -> Удалить столбец\n");
    printf("13 -> Взять строку с индексом N\n");
    printf("14 -> Взять строку с индексом M\n");
    printf("15 -> Добавить строку\n");
    printf("16 -> Добавить столбец\n");
    printf("17 -> Распечатать структуру\n");
    printf("18 -> Завершить работу с матрицей\n");
    printf("19 -> Завершить работу программы\n\n");
    printf("Выберите вариант: ");
    choice = obrabotka(); // Выбераем номер меню
    system("cls");        // Очищаем консоль
    switch (choice) {
    case 1: // Начать работу с матрицей
      start_matrix(&flag);
      break;
    case 2: //
      if (flag) {
        delete_matrix(head, tail, &line, &column);
      } else {
        error();
      }
      break;
    case 3: // Проверить матрицу на пустату
      if (flag) {
        if (!head) {
          printf("Матрица пуста\n");
        } else {
          printf("Матрица не пуста\n");
        }
      } else {
        error();
      }
      break;
    case 4: // Определить количество строк в матрице
      if (flag) {
        number_of_rows(head); // Считаем количество строк
      } else {
        error();
      }
      break;
    case 5: // Определить количество столбцов в матрице
      if (flag) {
        number_of_columns(head); // Считаем количество столбцов
      } else {
        error();
      }
      break;
    case 6: // Показать элемент с индексами NxM
      if (flag) {
        show_element(head, line, column); // Показываем выбранный элемент
      } else {
        error();
      }
      break;
    case 7: // Взять элемент с индексами NxM
      if (flag) {
        get_element(head, line, column); // Берем выбранный элемент
      } else {
        error();
      }
      break;
    case 8: // Изменить элемент с индексами NxM
      if (flag) {
        change_element(head, line, column); // Изменяем выбранный элемент
      } else {
        error();
      }
      break;
    case 9: // Показать строку с индексом N
      if (flag) {
        show_line(head, line); // Показывай выбранную строку
      } else {
        error();
      }
      break;
    case 10: // Показать столбец с индексом M
      if (flag) {
        show_column(head, column); // Показываем выбранный столбец
      } else {
        error();
      }
      break;
    case 11: // Удалить строку
      if (flag) {
        delete_line(head, tail, &line, &column); // Удаляет строку
      } else {
        error();
      }
      break;
    case 12: // Удалить столбец
      if (flag) {
        delete_column(head, tail, &line, &column); // Удаляет столбец
      } else {
        error();
      }
      break;
    case 13: // Взять строку с индексом N
      if (flag) {
        get_line(head, tail, &line, &column); // Берет строку
      } else {
        error();
      }
      break;
    case 14: // Взять столбец с индексом M
      if (flag) {
        get_column(head, tail, &line, &column); // Берет столбец
      } else {
        error();
      }
      break;
    case 15: // Добавить строку
      if (flag) {
        add_line(head, tail, &line, &column); // Добавляет строку
      } else {
        error();
      }
      break;
    case 16: // Добавить столбец
      if (flag) {
        add_column(head, tail, &line, &column); // Добавляет столбец
        tail = tail->next; // Передвигаем указатель на конец первой строки
      } else {
        error();
      }
      break;
    case 17: // Распечатать структуру
      if (flag) {
        print_matrix(head, tail); // Печатаем матрицу
      } else {
        error();
      }
      break;
    case 18: // Завершить работу с матрицей
      if (flag) {
        flag = 0;
        delete_matrix(head, tail, &line, &column); // Чистит матрицу
        head = NULL;
        tail = NULL;
        printf("Вы успешно завершили работу с матрицей\n");
      } else {
        error();
      }
      break;
    case 19: // Завершить работу программы
      if (flag) {
        printf("Вы ещё не завершили работу с матрицей\n");
      } else {
        system("cls");
        printf("Работа программы завершена!!!\n");
        exit(0); // Завершаем работу программы
      }
      break;
    default: // Проверяем, что ввели допустимое значение
      printf("Вы ввели недопустимое значение, попробуйте ещё раз\n");
      break;
    }
  }
}
Stack *
stack_menu(Stack *head) // Функция, которая содержит меню функций и их вызовы
{
  int count = 0; // Счетчик элементов в стеке
  int choice;    // Переменная для Switch
  int flag = 0; // Хранит информацию о том, начали ли мы работу с матрицей
  while (1) {
    printf("\n"); // Меню функций стека
    printf("1 -> Начать работу со стеком\n");
    printf("2 -> Сделать стек пустым\n");
    printf("3 -> Проверить стек на пустоту\n");
    printf("4 -> Показать значение вершины стека\n");
    printf("5 -> Удалить вершину\n");
    printf("6 -> Взять элемент из стека\n");
    printf("7 -> Изменить значение вершины\n");
    printf("8 -> Добавить элемент в стек\n");
    printf("9 -> Распечатать стек\n");
    printf("10 -> Закончить работу со стеком\n\n");
    printf("Выберите вариант: ");
    choice = obrabotka();
    system("cls");
    switch (choice) {
    case 1: // Начать работу со стеком
      start_stack(&flag);
      break;
    case 2: // Сделать стек пустым
      if (flag) {
        free_list(head); // Очищаем стек
        head = NULL; // Нулик указатель на начало стека
        printf("Вы успешно очистили стек\n");
      } else {
        error_stack();
      }
      break;
    case 3: // Проверить стек на пустоту
      if (flag) {
        if (head) // Проверяем, что стек не пуст
        {
          printf("Стек не пуст\n");
        } else {
          printf("Стек пуст\n");
        }
      } else {
        error_stack();
      }
      break;
    case 4: // Показать значение вершины стека
      if (flag) {
        show_top(head); // Показываем вершину стека
      } else {
        error_stack();
      }
      break;
    case 5: // Удалить вершину
      if (flag) {
        if (head) {
          if (!head->next) {
            free(head); // Очищаем единственный элемент в стеке
            head = NULL; // Нулим указатель на начало стека
          } else {
            remove_top(head); // Удаляем вершину стека
          }
          printf("Вы успешно удалили вершину стека\n");
        } else {
          printf("Стек пуст\n");
        }
      } else {
        error_stack();
      }
      break;
    case 6: // Взять элемент из стека
      if (flag) {
        get_top(head); // Берем вершину стека
      } else {
        error_stack();
      }
      break;
    case 7: // Изменить значение вершины
      if (flag) {
        change_top(head); // Изменяем вершину стека
        system("cls");    // Очищаем консоль
        printf("Вы успешно изменили вершину стека\n");
      } else {
        error_stack();
      }
      break;
    case 8: // Добавить элемент в стек
      if (flag) {
        if (count < glub) {
          if (!head) {
            head = create_node_stack(); // Создаем единственный элемент стека
            system("cls");
            printf("Вы успешно добавили элемент в стек\n");
          } else {
            add_stack(head); // Добавляем элемент в сек
            system("cls");
            printf("Вы успешно добавили элемент в стек\n");
            count++; // Увеличиваем счетчик элементов стека
          }
        } else {
          printf("Переполнение стека");
        }
      } else {
        error_stack();
      }
      break;
    case 9: // Распечатать стек
      if (flag) {
        printf("Стек: ");
        print_stack(head); // Печатаем стек
        printf("\n");
      } else {
        error_stack();
      }
      break;
    case 10: // Закончить работу со стеком
      if (!flag) {
        printf("\nРабота со списком еще не начата\n");
      } else {
        flag = 0;
        return head; // Возвращаем указатель на начало стека
        printf("\nРабота со списком завершена\n");
      }
      break;
    default:
      printf("\nВы ввели недопустимое значение, попробуйте еще раз :)\n");
      break;
    }
  }
}
void start_menu() // Функция начала работы программы
{
  while (1) {
    printf("Начать работу программы?\n\n");
    printf("1 -> Да\n");
    printf("2 -> Нет\n\n");
    printf("Выберите вариант: ");
    int choice = obrabotka();
    switch (choice) {
    case 1:
      system("cls");
      main_menu();
      break;
    case 2:
      system("cls");
      printf("Работа с программой завершена!!!\n");
      exit(0);
      break;
    default:
      printf("Вы ввели недопустимое значение, попробуйте ещё раз\n");
      break;
    }
  }
}
int main() {
  setlocale(LC_ALL, "Ru");
  start_menu();
  return 0;
}