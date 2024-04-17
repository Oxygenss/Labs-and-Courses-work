#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedList {
  char data;
  struct LinkedList *next;
  struct LinkedList *prev;
} list;
list *create_node(char c) {
  list *node = (list *)malloc(sizeof(list));
  if (node == NULL) {
    printf("No data!");
    exit(0);
  }
  node->data = c;
  node->next = NULL;
  node->prev = NULL;
  return node;
}
void push_back(list **head, list **tail, char c) {
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  list *node = create_node(c);
  list *temp0 = *head;
  while (temp0->next != NULL) {
    temp0 = temp0->next;
  }
  temp0->next = node;
  node->prev = temp0;
  *tail = node;
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
void emplace(list **head, list **tail) {
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  list *temp = *head;
  list *temp0 = *tail;
  while (temp->next) {
    if (temp->data == '.') {
      list *first_node = create_node('.');
      first_node->prev = temp;
      first_node->next = temp->next;
      temp->next = first_node;
      temp = temp->next;
      list *second_node = create_node('.');
      second_node->prev = temp;
      second_node->next = temp->next;
      temp->next = second_node;
      temp = temp->next;
      temp0 = second_node;
    }
    temp = temp->next;
  }
  if (temp->next == NULL && temp->data == '.') {
    list *first_node = create_node('.');
    first_node->prev = temp;
    first_node->next = temp->next;
    temp->next = first_node;
    list *second_node = create_node('.');
    second_node->prev = temp;
    second_node->next = temp->next;
    temp->next = second_node;
    temp0 = second_node;
  }
}
void free_list(list *head, list *tail) {
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
  tail = NULL;
}
void remove_elem(list **head) {
  int c;
  printf("Введите номер элемента: ");
  scanf("%d", &c);
  list *temp = *head;
  list *temp1 = *head;
  list *temp2 = *head;
  if (*head == NULL) {
    printf("No list");
    exit(0);
  }
  int count = 1;
  while (count != c - 1) {
    temp = temp->next;
    temp1 = temp1->next;
    temp2 = temp2->next;
    count++;
  }
  temp1 = temp1->next;
  temp2 = temp2->next;
  temp2 = temp2->next;
  temp->next = temp1->next;
  temp2->prev = temp->prev;
  free(temp1);
}
int main() {
  setlocale(LC_ALL, "Rus");
  char c;
  c = getchar();
  list *head = create_node(c);
  list *tail = head;
  c = getchar();
  while (c != '\n') {
    push_back(&head, &tail, c);
    c = getchar();
  }
  remove_elem(&head);
  print_list(head);
  printf("\n");
  emplace(&head, &tail);
  print_list(head);
  free_list(head, tail);
  return 0;
}