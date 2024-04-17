#include <stdio.h>
#include <stdlib.h>
int search_size() {
  FILE *base;
  int size = 0, a;
  fopen_s(&base, "base.txt", "r");
  if (base == 0) {
    printf("file not open\n");
    exit(0);
  }
  while (!feof(base)) {
    fscanf_s(base, "%d", &a);
    size++;
  }
  fclose(base);
  return size;
}
void print_base(int seria) {
  FILE *base;
  int a, count = 0;
  fopen_s(&base, "base.txt", "r");
  if (base == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("base: ");
  while (!feof(base)) {
    fscanf_s(base, "%d", &a);
    if (!feof(base)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(base);
}
void print_f1(int seria) {
  FILE *f1;
  int a, count = 0;
  fopen_s(&f1, "f1.txt", "r");
  if (f1 == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("f1: ");
  while (!feof(f1)) {
    fscanf_s(f1, "%d", &a);
    if (!feof(f1)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(f1);
}
void print_f2(int seria) {
  FILE *f2;
  int a, count = 0;
  fopen_s(&f2, "f2.txt", "r");
  if (f2 == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("f2: ");
  while (!feof(f2)) {
    fscanf_s(f2, "%d", &a);
    if (!feof(f2)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(f2);
}
void print_g1(int seria) {
  FILE *g1;
  int a, count = 0;
  fopen_s(&g1, "g1.txt", "r");
  if (g1 == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("g1: ");
  while (!feof(g1)) {
    fscanf_s(g1, "%d", &a);
    if (!feof(g1)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(g1);
}
void print_g2(int seria) {
  FILE *g2;
  int a, count = 0;
  fopen_s(&g2, "g2.txt", "r");
  if (g2 == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("g2: ");
  while (!feof(g2)) {
    fscanf_s(g2, "%d", &a);
    if (!feof(g2)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(g2);
}
void separation(int *seria, int size) {
  FILE *base, *f1, *f2;
  fopen_s(&base, "base.txt", "r");
  fopen_s(&f1, "f1.txt", "w");
  fopen_s(&f2, "f2.txt", "w");
  int a, i = 0, j = 0;
  if (base == 0 || f1 == 0 || f2 == 0) {
    printf("file not open\n");
    exit(0);
  }
  char count = 0;
  while (count < size) {
    if (i < (*seria)) {
      j = 0;
      fscanf_s(base, "%d", &a);
      fprintf(f1, "%d", a);
      fprintf(f1, " ");
      count++;
      i++;
    } else {
      if (j < (*seria)) {
        fscanf_s(base, "%d", &a);
        fprintf(f2, "%d", a);
        fprintf(f2, " ");
        count++;
        j++;
      } else {
        i = 0;
      }
    }
  }
  fclose(base);
  fclose(f1);
  fclose(f2);
}
void merge_one(int *seria) {
  int a, b, flag = 0, i = 0, j = 0;
  FILE *f1, *f2, *g1, *g2;
  fopen_s(&f1, "f1.txt", "r");
  fopen_s(&f2, "f2.txt", "r");
  fopen_s(&g1, "g1.txt", "w");
  fopen_s(&g2, "g2.txt", "w");
  if (f1 == 0 || f2 == 0 || g1 == 0 || g2 == 0) {
    printf("file not open\n");
    exit(0);
  }
  int temp = 0;
  if (f1 != NULL && f2 != NULL) {
    fscanf_s(f1, "%d", &a);
    fscanf_s(f2, "%d", &b);
    while ((!feof(f1)) || (!feof(f2))) {
      if (temp % 2 == 0) {
        if (i < (*seria) && j < (*seria)) {
          if (a <= b) {
            if (!feof(f1)) {
              fprintf(g1, "%d", a);
              fprintf(g1, " ");
            }
            fscanf_s(f1, "%d", &a);
            if (feof(f1)) {
              flag = 2;
            }
            i++;
          } else if (a >= b) {
            if (!feof(f2)) {
              fprintf(g1, "%d", b);
              fprintf(g1, " ");
            }
            fscanf_s(f2, "%d", &b);
            if (feof(f2)) {
              flag = 1;
            }
            j++;
          }
        } else if (i < (*seria) && j == (*seria)) {
          while (i != (*seria)) {
            if (!feof(f1)) {
              fprintf(g1, "%d", a);
              fprintf(g1, " ");
            }
            fscanf_s(f1, "%d", &a);
            i++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(f1)) {
            flag = 2;
          }
        } else if (j < (*seria) && i == (*seria)) {
          while (j != (*seria)) {
            if (!feof(f2)) {
              fprintf(g1, "%d", b);
              fprintf(g1, " ");
            }
            fscanf_s(f2, "%d", &b);
            j++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(f2)) {
            flag = 1;
          }
        }
      } else {
        if (i < (*seria) && j < (*seria)) {
          if (a <= b) {
            if (!feof(f1)) {
              fprintf(g2, "%d", a);
              fprintf(g2, " ");
            }
            fscanf_s(f1, "%d", &a);
            if (feof(f1)) {
              flag = 2;
            }
            i++;
          } else if (a >= b) {
            if (!feof(f2)) {
              fprintf(g2, "%d", b);
              fprintf(g2, " ");
            }
            fscanf_s(f2, "%d", &b);
            if (feof(f2)) {
              flag = 1;
            }
            j++;
          }
        } else if (i < (*seria) && j == (*seria)) {
          while (i != (*seria)) {
            if (!feof(f1)) {
              fprintf(g2, "%d", a);
              fprintf(g2, " ");
            }
            fscanf_s(f1, "%d", &a);
            i++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(f1)) {
            flag = 2;
          }
        } else if (j < (*seria) && i == (*seria)) {
          while (j != (*seria)) {
            if (!feof(f2)) {
              fprintf(g2, "%d", b);
              fprintf(g2, " ");
            }
            fscanf_s(f2, "%d", &b);
            j++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(f2)) {
            flag = 1;
          }
        }
      }
    }
  }
  if (flag == 1) {
    if (temp % 2 == 0) {
      while (!feof(f1)) {
        fprintf(g1, "%d", a);
        fprintf(g1, " ");
        fscanf_s(f1, "%d", &a);
      }
    } else {
      while (!feof(f1)) {
        fprintf(g2, "%d", a);
        fprintf(g2, " ");
        fscanf_s(f1, "%d", &a);
      }
    }
  }
  if (flag == 2) {
    if (temp % 2 == 0) {
      while (!feof(f2)) {
        fprintf(g1, "%d", a);
        fprintf(g1, " ");
        fscanf_s(f2, "%d", &a);
      }
    } else {
      while (!feof(f2)) {
        fprintf(g2, "%d", a);
        fprintf(g2, " ");
        fscanf_s(f2, "%d", &a);
      }
    }
  }
  (*seria) *= 2;
  fclose(f1);
  fclose(f2);
  fclose(g1);
  fclose(g2);
}
void merge_two(int *seria) {
  int a, b, flag = 0, i = 0, j = 0;
  FILE *f1, *f2, *g1, *g2;
  fopen_s(&f1, "f1.txt", "w");
  fopen_s(&f2, "f2.txt", "w");
  fopen_s(&g1, "g1.txt", "r");
  fopen_s(&g2, "g2.txt", "r");
  if (f1 == 0 || f2 == 0 || g1 == 0 || g2 == 0) {
    printf("file not open\n");
    exit(0);
  }
  int temp = 0;
  if (g1 != NULL && g2 != NULL) {
    fscanf_s(g1, "%d", &a);
    fscanf_s(g2, "%d", &b);
    while ((!feof(g1)) || (!feof(g2))) {
      if (temp % 2 == 0) {
        if (i < (*seria) && j < (*seria)) {
          if (a <= b) {
            if (!feof(g1)) {
              fprintf(f1, "%d", a);
              fprintf(f1, " ");
            }
            fscanf_s(g1, "%d", &a);
            if (feof(g1)) {
              flag = 2;
            }
            i++;
          } else if (a >= b) {
            if (!feof(g2)) {
              fprintf(f1, "%d", b);
              fprintf(f1, " ");
            }
            fscanf_s(g2, "%d", &b);
            if (feof(g2)) {
              flag = 1;
            }
            j++;
          }
        } else if (i < (*seria) && j == (*seria)) {
          while (i != (*seria)) {
            if (!feof(g1)) {
              fprintf(f1, "%d", a);
              fprintf(f1, " ");
            }
            fscanf_s(g1, "%d", &a);
            i++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(g1)) {
            flag = 2;
          }
        } else if (j < (*seria) && i == (*seria)) {
          while (j != (*seria)) {
            if (!feof(g2)) {
              fprintf(f1, "%d", b);
              fprintf(f1, " ");
            }
            fscanf_s(g2, "%d", &b);
            j++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(g2)) {
            flag = 1;
          }
        }
      } else {
        if (i < (*seria) && j < (*seria)) {
          if (a <= b) {
            if (!feof(g1)) {
              fprintf(f2, "%d", a);
              fprintf(f2, " ");
            }
            fscanf_s(g1, "%d", &a);
            if (feof(g1)) {
              flag = 2;
            }
            i++;
          } else if (a >= b) {
            if (!feof(g2)) {
              fprintf(f2, "%d", b);
              fprintf(f2, " ");
            }
            fscanf_s(g2, "%d", &b);
            if (feof(g2)) {
              flag = 1;
            }
            j++;
          }
        } else if (i < (*seria) && j == (*seria)) {
          while (i != (*seria)) {
            if (!feof(g1)) {
              fprintf(f2, "%d", a);
              fprintf(f2, " ");
            }
            fscanf_s(g1, "%d", &a);
            i++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(g1)) {
            flag = 2;
          }
        } else if (j < (*seria) && i == (*seria)) {
          while (j != (*seria)) {
            if (!feof(g2)) {
              fprintf(f2, "%d", b);
              fprintf(f2, " ");
            }
            fscanf_s(g2, "%d", &b);
            j++;
          }
          temp++;
          i = 0;
          j = 0;
          if (feof(g2)) {
            flag = 1;
          }
        }
      }
    }
  }
  if (flag == 1) {
    if (temp % 2 == 0) {
      while (!feof(g1)) {
        fprintf(f1, "%d", a);
        fprintf(f1, " ");
        fscanf_s(g1, "%d", &a);
      }
    } else {
      while (!feof(g1)) {
        fprintf(f2, "%d", a);
        fprintf(f2, " ");
        fscanf_s(g1, "%d", &a);
      }
    }
  }
  if (flag == 2) {
    if (temp % 2 == 0) {
      while (!feof(g2)) {
        fprintf(f1, "%d", a);
        fprintf(f1, " ");
        fscanf_s(g2, "%d", &a);
      }
    } else {
      while (!feof(g2)) {
        fprintf(f2, "%d", a);
        fprintf(f2, " ");
        fscanf_s(g2, "%d", &a);
      }
    }
  }
  (*seria) *= 2;
  fclose(f1);
  fclose(f2);
  fclose(g1);
  fclose(g2);
}
int main() {
  int seria = 1;
  int size = search_size();
  print_base(seria);
  printf("---------------------------------------\n");
  separation(&seria, size);
  print_f1(seria);
  print_f2(seria);
  printf("---------------------------------------\n");
  while (seria <= size) {
    merge_one(&seria);
    print_g1(seria);
    print_g2(seria);
    printf("---------------------------------------\n");
    if (seria <= size) {
      merge_two(&seria);
      print_f1(seria);
      print_f2(seria);
      printf("---------------------------------------\n");
    }
  }
  return 0;
}