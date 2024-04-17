#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedList {
  char data;
  struct LinkedList *next;
} list;
list *create_node(char c) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("Память не выделилиась");
    exit(0);
  }
  node->data = c;
  node->next = NULL;
  return node;
}
void error() { printf("\nВы еще не начали работу со списком\n\n"); }
void emplace(char c, list *rab) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("No data!");
    exit(0);
  }
  node->data = c;
  node->next = rab->next;
  rab->next = node;
}
void print_list(list *head, list *rab) {
  while (head) {
    if (rab == head) {
      if (head->data == ' ') {
        printf("\033[3;45;30m");
        printf("%c", head->data);
        printf("\033[0m");
        head = head->next;
      } else {
        printf("\033[35m\033[1m");
        printf("%c", head->data);
        printf("\033[0m");
        head = head->next;
      }
    } else {
      printf("%c", head->data);
      head = head->next;
    }
  }
  printf("\n");
}
void free_list(list *head) {
  while (head) {
    list *temp = head;
    head = head->next;
    free(temp);
  }
}
list *remove_element(list *one, list *two) {
  if (one == NULL) {
    one = two;
    two = two->next;
    free(one);
    return (two);
  } else {
    one->next = two->next;
    free(two);
    return (one);
  }
}
void menu() {
  int select, flag = 0;
  list *head = NULL;
  list *rab = NULL;
  while (true) {
    if (head != NULL) {
      printf("\n");
      print_list(head, rab);
      printf("\n");
    }
    printf("1) Начать работу со списком\n");
    printf("2) Сделать список пустым\n");
    printf("3) Проверить список на пустоту\n");
    printf("4) Установить рабочий указатель в начало списка\n");
    printf("5) Проверить, в конце ли рабочий указатель\n");
    printf("6) Передвинуть рабочий указатель на одну позицию\n");
    printf("7) Показать значение элемента списка за указателем\n");
    printf("8) Удалить элемент списка за указателем\n");
    printf("9) Взять элемент списка за указкателем\n");
    printf("10) Изменить значение элемента за указателем\n");
    printf("11) Добавить элемент за указателем\n");
    printf("12) Распечатать список\n");
    printf("13) Закончить работу со списком\n");
    printf("14) Закончить работу с программой\n\n");
    printf("Выберите вариант: ");
    scanf("%d", &select);
    system("cls");
    switch (select) {
    case 1:
      if (flag) {
        printf("\nВы уже начали работу со списком\n\n");
      } else {
        flag = 1;
        printf("\nВы начали работу со списком\n\n");
      }
      break;
    case 2:
      if (flag) {
        if (head == NULL) {
          printf("\nСписок уже список\n\n");
        } else {
          free_list(head);
          head = NULL;
          rab = NULL;
          printf("\nВы очистили список\n\n");
        }
      } else {
        error();
      }
      break;
    case 3:
      if (flag) {
        if (head == NULL) {
          printf("\nСписок пуст\n\n");
        } else {
          printf("\nСписок не пустой\n");
        }
      } else {
        error();
      }
      break;
    case 4:
      if (flag) {
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab == head) {
            printf("\nРабочий указатель уже в начале списка\n");
          } else {
            rab = head;
            printf("\nВы установили рабочий указатель в начало списка\n");
          }
        }
      } else {
        error();
      }
      break;
    case 5:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nРабочий указатель находится в конце списка\n");
          } else {
            printf("\nРабочий указатель не в конце списка\n");
          }
        }
      } else {
        error();
      }
      break;
    case 6:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nРабочий указатель находится в конце списка\n");
          } else {
            printf("\nВы подвинули рабочий указатель на один элемент вправо\n");
            rab = rab->next;
          }
        }
      } else {
        error();
      }
      break;
    case 7:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            printf("\nЭлемент после рабочего указателя: ");
            printf("%c\n", rab->next->data);
          }
        }
      } else {
        error();
      }
      break;
    case 8:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            rab = remove_element(rab, rab->next);
            printf("\nВы удалили элемент за рабочим указателем\n");
          }
        }
      } else {
        error();
      }
      break;
    case 9:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            print_list(head, rab);
            printf("\nЭлемент, который вы взяли: ");
            printf("%c\n", rab->next->data);
            rab = remove_element(rab, rab->next);
          }
        }
      } else {
        error();
      }
      break;
    case 10:
      if (flag) {
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            char ch;
            printf("\nВведите символ, на который хотите поменять: ");
            ch = getchar();
            if (ch == '\n') {
              ch = getchar();
            }
            rab->next->data = ch;
            system("cls");
            printf("\nВы поменяли символ за рабочим указателем на: ");
            printf("%c", ch);
          }
        }
      } else {
        error();
      }
      break;
    case 11:
      if (flag) {
        char ch;
        printf("\nВведите символ: ");
        ch = getchar();
        if (ch == '\n') {
          ch = getchar();
        }
        if (head == NULL) {
          head = create_node(ch);
          rab = head;
        } else {
          emplace(ch, rab);
        }
      } else {
        error();
      }
      break;
    case 12:
      if (flag) {
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
        }
      } else {
        error();
      }
      break;
    case 13:
      if (!flag) {
        printf("\nРабота со списком еще не начата\n\n");
      } else {
        flag = 0;
        free_list(head);
        head = NULL;
        rab = NULL;
        printf("\nРабота со списком завершена\n\n");
      }
      break;
    case 14:
      if (flag) {
        printf("\nВы не можете завершить работу программы, так как вы еще не "
               "завершили работу со структурой\n\n");
      } else {
        system("cls");
        printf("\n\t\tРабота программы завершена!!!\n");
        exit(0);
      }
      break;
    default:
      printf("\nВы ввели недопустимое значение, попробуйте еще раз :)\n\n");
      break;
    }
  }
}
void start() {
  while (true) {
    printf("Начать работу?\n\n");
    printf("1) Да\n");
    printf("2) Нет\n\n");
    int check;
    printf("Выберите вариант: ");
    scanf("%d", &check);
    system("cls");
    switch (check) {
    case 1:
      system("cls");
      menu();
      break;
    case 2:
      system("cls");
      printf("\n\t\tРабота с программой завершена!!!\n");
      exit(0);
      break;
    default:
      printf("\nВы ввели недопустимое значение, попробуйте еще раз :)\n\n");
      break;
    }
  }
}
int main() {
  setlocale(LC_ALL, "Ru");
  start();
  return 0;
}