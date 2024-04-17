#include <locale.h> //Для использование русского языка
#include <stdio.h> //Подключение всех необходимых библеотек
#include <stdlib.h>
int depth_deque; // Переменная, хранящая глубину дека
int depth_queue; // Переменная, хранящаю глубину очереди
typedef struct Queue // Описание структуры данных "Очередь"
{
  struct Queue *next; // Следующий элемент очереди
  struct Deque *head; // Начало Дека
  struct Deque *tail; // Конец Дека
} Queue;
typedef struct Deque // Описание структуры данных "Дека"
{
  struct Deque *next; // Следующий элемент Дека
  struct Deque *prev; // Предыдущий элемент Дека
  unsigned int data;  // Хранит целое значение
} Deque;
int deque_menu(Queue *node);
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
void error_queue() { printf("Вы ещё не начали работу с очередью\n"); }
void error_deque() { printf("Вы ещё не начали работу со стеком\n"); }
Deque *create_node_deque() // Функция создания элемента дека
{
  unsigned int c;
  Deque *node = (Deque *)malloc(sizeof(Deque)); // Выделяем память
  if (node == NULL) // Проверяем, то память выделилась
  {
    printf("Память не выделилиась");
    exit(0);
  }
  printf("Введите элемент, который хотите добавит: ");
  c = obrabotka();
  printf("\n");
  node->next = NULL;
  node->prev = NULL;
  node->data = c;
  return node;
}
void add_node_start(Deque *head) // Функция добавления элемента в начало дека
{
  Deque *node = create_node_deque(); // Создаем элемент дека
  head->prev = node;
  node->next = head;
}
void add_node_back(Deque *tail) // Функция добавления элемента в конец дека
{
  Deque *node = create_node_deque();
  tail->next = node;
  node->prev = tail;
}
void free_deque(Deque *head) // Функция очищения дека
{
  while (head) // Двигаем указатель до конца дека, пока существуют элемента
  {
    Deque *temp = head; // Делаем копию указателя
    head = head->next;  // Двигаем сам указатель
    free(temp);         // Очищаем копию
  }
  free(head); // Очищаем последний элемент
}
void print_deque(
    Deque *head,
    Deque *tail) // Функция оаспечатывания дека с прямым и обратным выводом
{
  printf("\n");
  printf("Прямой вывод: ");
  while (head) // Двигаем указатель от начала дека до конца, пока элементы
               // существуют
  {
    printf("%u ",
           head->data); // Выводим значение, которые хранится в элементе дека
    head = head->next;  // Двигаем указатель
  }
  printf("\n\n");
  printf("Обратный вывод: "); // Обратный вывод, указатель начинаем двигать с
                              // конца дека
  while (tail) {
    printf("%u ", tail->data);
    tail = tail->prev;
  }
  printf("\n");
}
void print_deque(
    Deque *head) // Функция, которая распечатывает дек только в прямо порядке
{
  if (head->next) {
    while (head) {
      printf("%u ", head->data);
      head = head->next;
    }
  } else {
    printf("%u ", head->data);
  }
}
void change_start(
    Deque *head) // Функция, которая изменяет элемент в начале дека
{
  unsigned int c;
  printf("Введите элемент, на который хотите изменить начало очереди: ");
  c = obrabotka(); // Вводим элемент, на который хотим заменить уже существующий
  printf("\n");
  head->data = c; // Присваиваем новый элемент
}
void change_end(Deque *tail) // Функция, которая изменяет элемент в конце
{
  unsigned int c;
  printf("Введите элемент, на который хотите изменить конец очереди: ");
  c = obrabotka();
  printf("\n");
  tail->data = c;
}
Deque *remove_start(Deque *head) // Функция, которая удаляет начало дека
{
  Deque *temp = head; // Копируем указатель на начало дека
  head = head->next; // Двигаем указатель на следующий элемент
  head->prev = NULL; // Нулим указатель на предыдущий элемент
  free(temp);  // Очищаем копию
  return head; // Возвращает измененный указатель на начало дека
}
Deque *remove_end(Deque *tail) // Функция, которая удаляет конец дека
{
  Deque *temp = tail; // Копируем указатель на конец дека
  tail = tail->prev; // Двигаем указатель на предыдущий элемент
  tail->next = NULL; // Нулим указатель на следующий элемент
  free(temp);  // Очищаем копию
  return tail; // Возвращает измененный указатель на конец дека
}
Deque *
remove_start_show(Deque *head) // Функция, которая берет элемент из начала дека
{
  unsigned int c = head->data; // Создаем переменную, в которую кладем элемент
                               // из начала дека (берем элемент)
  printf("Элемент, который вы взяли: ");
  printf("%u\n", c); // Показываем элемент, который мы будем брать
  Deque *temp = head;
  head = head->next;
  head->prev = NULL;
  free(temp);
  return head;
}
Deque *
remove_end_show(Deque *tail) // Функция, которая берет элемент из конца дека
{
  unsigned int c = tail->data; // Создаем переменную, в которую кладем элемент
                               // из конца дека (берем элемент)
  printf("Элемент, который вы взяли: ");
  printf("%u\n", c);
  Deque *temp = tail;
  tail = tail->prev;
  tail->next = NULL;
  free(temp);
  return tail;
}
void remove_show_one(Deque *head) // Функция, которая берет элемент
{
  unsigned int c = head->data;
  printf("Элемент, который вы взяли: ");
  printf("%u\n", c);
  free(head);
}
void show_start(Deque *head) // Функция, которая показывает начало дека
{
  printf("Начало дека: ");
  printf("%u\n", head->data); // Выводим в консоль начало дека
}
void show_end(Deque *tail) // Функция, которая показывает конец дека
{
  printf("Конец дека: ");
  printf("%u\n", tail->data); // Выводим в консоль конец дека
}
Queue *create_node_queue() // Функция, которая создает элемент очереди
{
  Queue *node = (Queue *)malloc(sizeof(Queue)); // Выделяем память
  if (node == NULL) {
    printf("Память не выделилиась");
    exit(0);
  }
  node->head = NULL;
  node->tail = NULL;
  node->next = NULL;
  deque_menu(
      &(*node)); // Спускаемя на второуй уровень, чтобы заполнить новый элемент
  return node;
}
Queue *
add_element(Queue *head) // Функция, которая добаляет элемент в конец очереди
{
  Queue *node = create_node_queue(); // Создаем новый элемент
  node->next = head; // Указатель на следующий элемент у нового элемента
                     // указывает на уже существующюю очередь (ставим в начало)
  return node;
}
void print_queue(Queue *head) // Функция, которая распечатывает очередь
{
  printf("\nВаша очередь: ");
  while (head) // Пока существуют элементы очередь
  {
    print_deque(head->head); // Выводим элемент очереди на экран
    printf("| ");
    head = head->next; // Двигаем указатель
  }
  printf("\n");
}
void remove_queue(Queue *head) // Функция, которая очищает очередь
{
  while (head) {
    Queue *temp = head;     // Создаем копию указателя
    free_deque(head->head); // Очищаем содержимое элемента
    head = head->next;      // Двигаем указатель
    free(temp);             // Очищаем элемент
  }
  free(head);
}
void show_start(Queue *head) // Функция, которая показывает начало очереди
{
  printf("Начало очереди: ");
  while (head->next) // Пока чуществует указатель на следующий элемент очереди
  {
    head = head->next; // Двигаем указатель
  }
  print_deque(head->head, head->tail); // Выводи начало очереди
}
void remove_start(Queue *head) // Функция, которая удаляет начало очереди
{
  Queue *temp = head->next; // Делаем копию указателя на следующий элемент
  if (temp->next) // Проверяем, что существует следующий элемент очереди
  {
    while (temp->next) // Пока существует следующий элемент
    {
      temp = temp->next;
      head = head->next;
    }
    head->next = NULL;
  } else {
    head->next = NULL; // Обнуляем указатель на следующий элемент очереди
  }
}
void get_start(Queue *head) // Функция, которая берет начало очереди, если в ней
                            // не один елемент
{
  Queue *temp = head;
  if (temp->next) {
    while (temp->next) {
      temp = temp->next;
    }
    Queue *temp1 = temp; // Создаем копию начала очереди
    printf("Элемент, который вы взяли: ");
    print_deque(temp1->head); // Выврдим в консоль содержимое этой копии
    remove_start(head); // Удаляем начало очереди
  }
}
void change_start_queue(Queue *head) // Функция, которая изменяет начало очереди
{
  while (head->next) // Пока существует указатель на слелующий элемент
  {
    head = head->next; // Двигаем указатель
  }
  deque_menu(
      &(*head)); // Спускаемся на второй уровень, чтобы изменить начало очереди
}
void get_start_one(Queue *head) // Функция, которая берет начало очереди, если в
                                // ней только один элемент
{
  printf("Элемент, который вы взяли: ");
  print_deque(head->head);
  printf("\n");
  free(head);
}
int deque_menu(Queue *node) {
  int check = 1; // Отвечает за while
  int choice;    // Переменная для Switch
  int flag = 0; // Хранит информацию о том, начали ли мы работу с очередью
  int count = 0; // Счетчик уже добавленных элементов очереди
  while (check) {
    printf("\n"); // Меню функций дека
    printf("1 -> Начать работу с деком\n");
    printf("2 -> Сделать дек пустым\n");
    printf("3 -> Проверить дек на пустату\n");
    printf("4 -> Показать значение в начале дека\n");
    printf("5 -> Показать значение в конце дека\n");
    printf("6 -> Удалить начало дека\n");
    printf("7 -> Удалить конец дека\n");
    printf("8 -> Взять элемент из начала дека\n");
    printf("9 -> Взять элемент из конца дека\n");
    printf("10 -> Изменить начало дека\n");
    printf("11 -> Изменить конец дека\n");
    printf("12 -> Добавить элемент в начало дека\n");
    printf("13 -> Добавить элемент в конец дека\n");
    printf("14 -> Распечатать дек\n");
    printf("15 -> Завершить работу с деком\n\n");
    printf("Выберите вариант: ");
    choice = obrabotka();
    system("cls");
    switch (choice) {
    case 1: // Начать работу с деком
      if (flag) // Проверяет, начали ли мы работу с деком
      {
        printf("Вы уже начали работу с деком\n");
      } else {
        flag = 1;
        printf("Вы успешно начали работу с деком\n");
      }
      break;
    case 2: // Сделать дек пустым
      if (flag) {
        if (node->head) // Проверяет, существует ли очередь
        {
          free_deque(&(*node->head)); // Очищает очередь
          node->tail = NULL; // Нулит указатель на конец дека
          node->head = NULL; // Нулит указатель на начало дека
          count = 0; // Нулит количество уже введенных элементов в дек
        } else {
          printf("Дек уже пуст\n");
        }
      } else {
        error_deque(); // Ошибка, если работа с деком уже начата
      }
      break;
    case 3: // Проверить дек на пустату
      if (flag) {
        if (node->head) // Проверяет, пуст ли дек
        {
          printf("Дек не пуст\n");
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 4: // Показать значение в начале дека
      if (flag) {
        if (node->head) {
          show_start(&(*node->head)); // Показывает значение в начале дека
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 5: // Показать значение в конце дека
      if (flag) {
        if (node->head) {
          show_end(&(*node->tail)); // Показывает значение в конце дека
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 6: // Удалить начало дека
      if (flag) {
        if (node->head) {
          if (node->head->next) // Проверяет, что в деке больше одного элемента
          {
            node->head = remove_start(&(*node->head)); // Удаляет начало дека
            print_deque(&(*node->head), &(*node->tail)); // Распечатывает дек
            count--; // Уменьшает счетчик количества уже введенных элементов
          } else {
            free(node->head); // Удаляет единственный элемент в деке
            node->head = NULL; // Нулит указатель на начало дека
            node->tail = NULL; // Нулит указательна на конец дека
            count--;
          }
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 7: // Удалить конец дека
      if (flag) {
        if (node->tail) {
          if (node->tail->prev) // Если существует предыдущий элемент
          {
            node->tail = remove_end(&(*node->tail)); // Удаляет конец дека
            print_deque(&(*node->head), &(*node->tail));
            count--;
          } else {
            free(node->tail);
            node->head = NULL;
            node->tail = NULL;
            count--;
          }
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 8: // Взять элемент из начала дека
      if (flag) {
        if (node->head) {
          if (node->head->next) {
            node->head = remove_start_show(
                &(*node->head)); // Берет элемент из начала дека
            print_deque(&(*node->head), &(*node->tail));
            count--;
          } else {
            remove_show_one(&(*node->head)); // Берет единственный элемент дека
            node->head = NULL;
            node->tail = NULL;
            count--;
          }
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 9: // Взять элемент из конца дека
      if (flag) {
        if (node->tail) {
          if (node->tail->prev) {
            node->tail =
                remove_end_show(&(*node->tail)); // Берет элемент из конца дека
            print_deque(&(*node->head), &(*node->tail));
            count--;
          } else {
            remove_show_one(&(*node->head));
            node->head = NULL;
            node->tail = NULL;
            count--;
          }
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 10: // Изменить начало дека
      if (flag) {
        if (node->head) {
          change_start(&(*node->head)); // Изменяет начало дека
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 11: // Изменить конец дека
      if (flag) {
        if (node->tail) {
          change_end(&(*node->tail)); // Изменяет конец дека
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 12: // Добавить элемент в начало дека
      if (flag) {
        if (!node->head) {
          if (count < depth_deque) {
            node->head = create_node_deque(); // Создает элемент в пустом деке
            node->tail = node->head;
            count++;
          } else {
            printf("Переполнение Дека\n");
          }
        } else {
          if (count < depth_deque) {
            add_node_start(&(*node->head)); // Добавляет элемент в начало дека
            node->head = node->head->prev;
            count++;
          } else {
            printf("Переполнение Дека\n");
          }
        }
      } else {
        error_deque();
      }
      break;
    case 13: // Добавить элемент в конец дека
      if (flag) {
        if (node->tail == NULL) {
          if (count < depth_deque) {
            node->tail = create_node_deque(); // Создает элемент в пустом деке
            node->head = node->tail;
            count++;
          } else {
            printf("Переполнение Дека\n");
          }
        } else {
          if (count < depth_deque) {
            add_node_back(&(*node->tail)); // Добавляет элемент в конец дека
            node->tail = node->tail->next;
            count++;
          } else {
            printf("Переполнение Дека\n");
          }
        }
      } else {
        error_deque();
      }
      break;
    case 14: // Распечатать дек
      if (flag) {
        if (node->head) {
          print_deque(&(*node->head), &(*node->tail)); // Печатает дек
        } else {
          printf("Дек пуст\n");
        }
      } else {
        error_deque();
      }
      break;
    case 15: // Завершить работу с деком
      if (!flag) {
        printf("\nРабота с деком еще не начата\n");
      } else {
        printf("\nРабота с деком завершена\n");
        return 0; // Работа с деком заканчивается
      }
      break;
    default:
      printf("Вы ввели недопустимое значение, попробуйте ещё раз\n");
      break;
    }
  }
}
void queue_menu() {
  Queue *head = NULL; // Хранит конец очереди
  int choice;         // Переменная для Switch
  int flag = 0; // Хранит информацию о том, начали ли мы работу с очередью
  int count = 0; // Количесвто уже добавленных элементов очереди
  printf("Введите глубину очереди: ");
  depth_queue = obrabotka(); // Определяет глубину очереди
  printf("Введите глубину деков: ");
  depth_deque = obrabotka(); // Определяет глубину дека
  while (1) {
    printf("\n"); // Меню функций очереди
    printf("1 -> Начать работу с очередью\n");
    printf("2 -> Сделать очередь пустой\n");
    printf("3 -> Проверить очередь на пустату\n");
    printf("4 -> Показать значение элемента в начале очереди\n");
    printf("5 -> Удалить начало очереди\n");
    printf("6 -> Взять элемент из начала очереди\n");
    printf("7 -> Изменить значение элемента в начале очереди\n");
    printf("8 -> Добавить элемент в конец очереди\n");
    printf("9 -> Распечатать очередь\n");
    printf("10 -> Завершить работу с очередью\n");
    printf("11 -> Завершить работу программы\n\n");
    printf("Выберите вариант: ");
    choice = obrabotka(); // Определяет следующую команду программы
    system("cls"); // Очищает консоль
    switch (choice) {
    case 1:     // Начать работу с очередью
      if (flag) // Если работа с очередью уже начата
      {
        printf("Вы уже начали работу с очередью\n");
      } else {
        flag = 1;
        printf("Вы успешно начали работу с очередью\n");
      }
      break;
    case 2: // Сделать очередь пустой
      if (flag) {
        if (head) // Проверяет, существует ли очередь
        {
          remove_queue(head); // Очищает очередь
          head = NULL; // Обнуляет указатель на конец очереди
          count = 0; // Обнуляет количесвто введенных элементов очереди
          printf("Очередь успешно очищена\n");
        } else {
          printf("Очередь уже пуста\n");
        }
      } else {
        error_queue(); // Если работа с очередью еще не начата
      }
      break;
    case 3: // Проверить очередь на пустату
      if (flag) {
        if (head) // Существует ли очередь
        {
          printf("Очередь не пуста\n");
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 4: // Показать значение элемента в начале очереди
      if (flag) {
        if (head) {
          show_start(head); // Показывает значение элемента в начале очереди
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 5: // Удалить начало очереди
      if (flag) {
        if (head) {
          if (head->next) // Проверяет, один ли элемент в очереди
          {
            remove_start(head); // Удаляет начало очереди
            printf("Начало очереди успешно удалено\n");
            count--; // Уменьшает количество уже введенных элементов в очередь
          } else {
            free(head); // Чистит единственный элемент очереди
            head = NULL; // Обнуляет указатель на конец очереди
          }
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 6: // Взять элемент из начала очереди/////////////////////
      if (flag) {
        if (head) {
          if (head->next) {
            get_start(head); // Берет элемент из начала очереди
            count--;
          } else {
            get_start_one(head);
            head = NULL;
            count--;
          }
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 7: // Изменить значение элемента в начале очереди
      if (flag) {
        if (head) {
          change_start_queue(
              head); // Изменяет значение элемента в начале очереди
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 8: // Добавить элемент в конец очереди
      if (flag) {
        if (!head) // Если в очереди еще нет элементов
        {
          if (count < depth_queue) // Сравниевает количесвто уже введенных
                                   // элементов с глубиной
          {
            head = create_node_queue(); // Создает новый элемент очереди и
                                        // присваивает его концу
            printf("Вы успешно создали первый элемент очереди\n");
            count++; // Увеличивает количество уже введенных элементов
          } else {
            printf("Переполнение очереди\n");
          }
        } else {
          if (count < depth_queue) {
            head = add_element(head); // Добавляет новый элемент в конец очереди
                                      // и двигает указатель на конец очереди
            printf("Вы успешно добавили новый элемент в конец очереди\n");
            count++;
          } else {
            printf("Переполнение очереди\n");
          }
        }
      } else {
        error_queue();
      }
      break;
    case 9: // Распечатать очередь
      if (flag) {
        if (head) {
          print_queue(head); // Распечатывает очеердь
        } else {
          printf("Очередь пуста\n");
        }
      } else {
        error_queue();
      }
      break;
    case 10: // Завершить работу с очередью
      if (flag) {
        if (head) {
          remove_queue(head); // Очищает очередь
          head = NULL; // Обнуляет указатель на конец очереди
          flag = 0; // Указывает на то, что работа с очередью окончена
          printf("Вы успешно завершили работу с очередью\n");
        } else {
          head = NULL;
          flag = 0;
          printf("Вы успешно завершили работу с очередью\n");
        }
      } else {
        error_queue();
      }
      break;
    case 11: // Завершить работу программы
      if (flag) {
        printf("Вы ещё не завершили работу с очередью\n");
      } else {
        system("cls");
        printf("Работа программы завершена!!!\n");
        exit(0); // Заканчивает работу программы функции, тем самым заканчивает
                 // работу программы
      }
      break;
    default:
      printf("Вы ввели недопустимое значение, попробуйте ещё раз\n");
      break;
    }
  }
}
void start_menu() // Функция, отвечающая за запуск программы
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
      queue_menu(); // Вызывает меню очереди
      break;
    case 2:
      system("cls"); // Очищаем консоль
      printf("Работа с программой завершена!!!\n");
      exit(0); // Заканчиваем работу программы
      break;
    default:
      printf("Вы ввели недопустимое значение, попробуйте ещё раз\n");
      break;
    }
  }
}
int main() {
  setlocale(LC_ALL, "Ru"); // Локализовать под русский язык
  start_menu(); // Вызывает функцию, отвечающую за запуск программы
  return 0;
}