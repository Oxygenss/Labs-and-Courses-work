#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
  char data;
  struct LinkedList *next;
} list;

list *create_node(char c) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("No data!");
    exit(0);
  }
  node->data = c;
  node->next = NULL;
  return node;
}

void push_back(list **head, char c) {
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  list *node = create_node(c);
  list *temp = *head;
  while (temp->next) {
    temp = temp->next;
  }
  temp->next = node;
}

void print_list(list *head) {
  if (head == NULL) {
    printf("No list");
    exit(0);
  }
  while (head) {
    printf("%c", head->data);
    head = head->next;
  }
}

void emplace(list **head) {
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  list *temp = *head;
  while (temp->next) {
    if (temp->data == '.') {
      list *first_node = create_node('.');
      first_node->next = temp->next;
      temp->next = first_node;
      list *second_node = create_node('.');
      second_node->next = temp->next;
      temp->next = second_node;
      temp = temp->next;
      temp = temp->next;
    }
    temp = temp->next;
  }
  if (temp->next == NULL && temp->data == '.') {
    list *first_node = create_node('.');
    first_node->next = temp->next;
    temp->next = first_node;
    list *second_node = create_node('.');
    second_node->next = temp->next;
    temp->next = second_node;
  }
}

void remove_elem(list **head) {
  int c;
  printf("Введите номер элемента: ");
  scanf("%d", &c);
  list *temp = *head;
  list *temp1 = *head;
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  int count = 1;
  while (count != c - 1) {
    temp1 = temp1->next;
    temp = temp->next;
    count++;
  }
  temp1 = temp1->next;
  temp->next = temp1->next;
  free(temp1);
}

void free_list(list *head) {
  if (head == NULL) {
    printf("No list");
    exit(0);
  }
  while (head) {
    list *temp = head;
    head = head->next;
    free(temp);
  }
  free(head);
}

int main() {
  setlocale(LC_ALL, "Ru");
  char c;
  c = getchar();
  list *head = create_node(c);
  c = getchar();
  while (c != '\n') {
    push_back(&head, c);
    c = getchar();
  }
  remove_elem(&head);
  print_list(head);
  printf("\n");
  emplace(&head);
  print_list(head);
  free_list(head);
  return 0;
}