#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedList {
  char data;
  struct LinkedList *next;
  struct LinkedList *prev;
} list;
void free_list(list *head) {
  while (head) {
    list *temp = head;
    head = head->next;
    free(temp);
  }
  free(head);
}
void error() { printf("\nВы еще не начали работу со списком\n\n"); }
void remove_element_after(list *rab, list *next) {
  if (next->next == NULL) {
    rab->next = NULL;
    free(next);
  } else {
    rab->next = next->next;
    next->next->prev = rab;
    free(next);
  }
}
void remove_element_before(list *rab, list *prev) {
  if (prev->prev == NULL) {
    rab->prev = NULL;
    free(prev);
  } else {
    rab->prev = prev->prev;
    prev->prev->next = rab;
    free(prev);
  }
}
list *create_node(char c) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("Память не выделилиась");
    exit(0);
  }
  node->data = c;
  node->next = NULL;
  node->prev = NULL;
  return node;
}
void emplace_after(char c, list *rab, list *tail) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("No data!");
    exit(0);
  }
  node->data = c;
  node->prev = rab;
  node->next = rab->next;
  rab->next = node;
  if (node->next) {
    node->next->prev = node;
  }
}
void emplace_before(char c, list *rab, list *head) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("No data!");
    exit(0);
  }
  node->data = c;
  node->next = rab;
  node->prev = rab->prev;
  rab->prev = node;
  if (node->prev) {
    node->prev->next = node;
  }
  if (node->prev == NULL) {
    head = node;
  }
}
void print_list_start(list *head, list *rab) {
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
void print_list_finish(list *tail, list *rab) {
  while (tail) {
    if (rab == tail) {
      if (tail->data == ' ') {
        printf("\033[3;45;30m");
        printf("%c", tail->data);
        printf("\033[0m");
        tail = tail->prev;
      } else {
        printf("\033[35m\033[1m");
        printf("%c", tail->data);
        printf("\033[0m");
        tail = tail->prev;
      }
    } else {
      printf("%c", tail->data);
      tail = tail->prev;
    }
  }
  printf("\n");
}
void menu() {
  int select, flag = 0;
  list *head = NULL;
  list *rab = NULL;
  list *tail = NULL;
  while (true) {
    if (head != NULL) {
      printf("\n");
      print_list_start(head, rab);
      printf("\n");
      print_list_finish(tail, rab);
      printf("\n");
    }
    printf("1) Начать работу со списком\n");
    printf("2) Сделать список пустым\n");
    printf("3) Проверить список на пустату\n");
    printf("4) Установить указатель в начало списка\n");
    printf("5) Установить указатель в конец списка\n");
    printf("6) Проверить, в конце ли рабочий указатель\n");
    printf("7) Проверить, в начале ли рабочий указатель\n");
    printf("8) Передвинуть рабочий указатель на одну позицию вправо\n");
    printf("9) Передвинуть рабочий указатель на одну позицию влево\n");
    printf("10) Показать значение элемента списка перед указателем\n");
    printf("11) Показать значение элемента списка за указателем\n");
    printf("12) Удалить элемент списка перед указателем\n");
    printf("13) Удалить элемент списка за указателем\n");
    printf("14) Взять значение элемента списка перед указателем\n");
    printf("15) Взять значение элемента списка за указателем\n");
    printf("16) Изменить значение элемента перед указателем\n");
    printf("17) Изменить значение элемента за указателем\n");
    printf("18) Добавить элемент перед указателем\n");
    printf("19) Добавить элемент за указателем\n");
    printf("20) Распечатать список\n");
    printf("21) Закончить работу со списком\n");
    printf("22) Закончить работу с программой\n");
    printf("Выберите вариант: ");
    scanf_s("%d", &select);
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
          rab = NULL;
          tail = NULL;
          head = NULL;
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
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab == tail) {
            printf("\nРабочий указатель уже в конце списка\n");
          } else {
            rab = tail;
            printf("\nВы установили рабочий указатель в конец списка\n");
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
            printf("\nРабочий указатель не в конце списка\n");
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
          if (rab->prev == NULL) {
            printf("\nРабочий указатель находится в начале списка\n");
          } else {
            printf("\nРабочий указатель не в начале списка\n");
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
    case 9:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->prev == NULL) {
            printf("\nРабочий указатель находится в начале списка\n");
          } else {
            printf("\nВы подвинули рабочий указатель на один элемент влево\n");
            rab = rab->prev;
          }
        }
      } else {
        error();
      }
      break;
    case 10:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->prev == NULL) {
            printf("\nУказатель находится в начале списка\n");
          } else {
            printf("\nЭлемент перед рабочего указателя: ");
            printf("%c\n", rab->prev->data);
          }
        }
      } else {
        error();
      }
      break;
    case 11:
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
    case 12:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->prev == NULL) {
            printf("\nУказатель находится в начале списка\n");
          } else {
            remove_element_before(rab, rab->prev);
            if (rab->prev == NULL) {
              head = rab;
            }
            printf("\nВы удалили элемент перед рабочим указателем\n");
          }
        }
      } else {
        error();
      }
      break;
    case 13:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            remove_element_after(rab, rab->next);
            if (rab->next == NULL) {
              tail = rab;
            }
            printf("\nВы удалили элемент за рабочим указателем\n");
          }
        }
      } else {
        error();
      }
      break;
    case 14:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->prev == NULL) {
            printf("\nУказатель находится в начале списка\n");
          } else {
            printf("\nЭлемент, который вы взяли: ");
            printf("%c\n", rab->prev->data);
            remove_element_before(rab, rab->prev);
            if (rab->prev == NULL) {
              head = rab;
            }
          }
        }
      } else {
        error();
      }
      break;
    case 15:
      if (flag) {
        if (rab == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->next == NULL) {
            printf("\nУказатель находится в конце списка\n");
          } else {
            printf("\nЭлемент, который вы взяли: ");
            printf("%c\n", rab->next->data);
            remove_element_after(rab, rab->next);
            if (rab->next == NULL) {
              tail = rab;
            }
          }
        }
      } else {
        error();
      }
      break;
    case 16:
      if (flag) {
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
          if (rab->prev == NULL) {
            printf("\nУказатель находится в начале списка\n");
          } else {
            char ch;
            printf("\nВведите символ, на который хотите поменять: ");
            ch = getchar();
            if (ch == '\n') {
              ch = getchar();
            }
            rab->prev->data = ch;
            system("cls");
            printf("\nВы поменяли символ перед рабочим указателем на: ");
            printf("%c\n", ch);
          }
        }
      } else {
        error();
      }
      break;
    case 17:
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
            printf("%c\n", ch);
          }
        }
      } else {
        error();
      }
      break;
    case 18:
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
          tail = head;
        } else {
          emplace_before(ch, rab, head);
          if (head->prev) {
            head = head->prev;
          }
        }
      } else {
        error();
      }
      break;
    case 19:
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
          tail = head;
        } else {
          emplace_after(ch, rab, tail);
          if (tail->next) {
            tail = tail->next;
          }
        }
      } else {
        error();
      }
      break;
    case 20:
      if (flag) {
        if (head == NULL) {
          printf("\nПустой список\n\n");
        } else {
        }
      } else {
        error();
      }
      break;
    case 21:
      if (!flag) {
        printf("\nРабота со списком еще не начата\n\n");
      } else {
        flag = 0;
        free_list(head);
        head = NULL;
        rab = NULL;
        tail = NULL;
        printf("\nРабота со списком завершена\n\n");
      }
      break;
    case 22:
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
    scanf_s("%d", &check);
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