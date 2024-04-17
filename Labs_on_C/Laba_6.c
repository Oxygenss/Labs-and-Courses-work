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
void print_f(int seria) {
  FILE *f;
  int a, count = 0;
  fopen_s(&f, "f.txt", "r");
  if (f == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("f: ");
  while (feof(f) == 0) {
    fscanf_s(f, "%d", &a);
    if (!feof(f)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(f);
}
void print_g(int seria) {
  FILE *g;
  int a, count = 0;
  fopen_s(&g, "g.txt", "r");
  if (g == 0) {
    printf("file not open\n");
    exit(0);
  }
  printf("g: ");
  while (!feof(g)) {
    fscanf_s(g, "%d", &a);
    if (!feof(g)) {
      printf("%d ", a);
      count++;
      if (count == seria) {
        printf("| ");
        count = 0;
      }
    }
  }
  printf("\n");
  fclose(g);
}
void separation(int *seria, int size) {
  FILE *base, *f, *g;
  fopen_s(&base, "base.txt", "r");
  fopen_s(&f, "f.txt", "w");
  fopen_s(&g, "g.txt", "w");
  int a, i = 0, j = 0;
  if (base == 0 || f == 0 || g == 0) {
    printf("file not open\n");
    exit(0);
  }
  char count = 0;
  while (count < size) {
    if (i < (*seria)) {
      j = 0;
      fscanf_s(base, "%d", &a);
      fprintf(f, "%d", a);
      fprintf(f, " ");
      count++;
      i++;
    } else {
      if (j < (*seria)) {
        fscanf_s(base, "%d", &a);
        fprintf(g, "%d", a);
        fprintf(g, " ");
        count++;
        j++;
      } else {
        i = 0;
      }
    }
  }
  fclose(base);
  fclose(f);
  fclose(g);
}
void merge(int *seria) {
  int a, b, flag = 0, i = 0, j = 0;
  FILE *base, *f, *g;
  fopen_s(&base, "base.txt", "w");
  fopen_s(&f, "f.txt", "r");
  fopen_s(&g, "g.txt", "r");
  if (base == 0 || f == 0 || g == 0) {
    printf("file not open\n");
    exit(0);
  }
  if (f != NULL && g != NULL) {
    fscanf_s(f, "%d", &a);
    fscanf_s(g, "%d", &b);
    while ((flag != 1) && (flag != 2)) {
      while ((!feof(f)) || (!feof(g))) {
        if (i < (*seria) && j < (*seria)) {
          if (a <= b) {
            if (!feof(f)) {
              fprintf(base, "%d", a);
              fprintf(base, " ");
            }
            fscanf_s(f, "%d", &a);
            if (feof(f)) {
              flag = 2;
            }
            i++;
          } else if (a >= b) {
            if (!feof(g)) {
              fprintf(base, "%d", b);
              fprintf(base, " ");
            }
            fscanf_s(g, "%d", &b);
            if (feof(g)) {
              flag = 1;
            }
            j++;
          }
        } else if (i < (*seria) && j == (*seria)) {
          while (i != (*seria)) {
            if (!feof(f)) {
              fprintf(base, "%d", a);
              fprintf(base, " ");
            }
            fscanf_s(f, "%d", &a);
            i++;
          }
          i = 0;
          j = 0;
          if (feof(f)) {
            flag = 2;
          }
        } else if (j < (*seria) && i == (*seria)) {
          while (j != (*seria)) {
            if (!feof(g)) {
              fprintf(base, "%d", b);
              fprintf(base, " ");
            }
            fscanf_s(g, "%d", &b);
            j++;
          }
          i = 0;
          j = 0;
          if (feof(f)) {
            flag = 1;
          }
        }
      }
    }
    if (flag == 1) {
      while (!feof(f)) {
        fprintf(base, "%d", a);
        fprintf(base, " ");
        fscanf_s(f, "%d", &a);
      }
    }
    if (flag == 2) {
      while (!feof(g)) {
        fprintf(base, "%d", b);
        fprintf(base, " ");
        fscanf_s(g, "%d", &b);
      }
    }
  }
  (*seria) *= 2;
  fclose(base);
  fclose(f);
  fclose(g);
}
int main() {
  int seria = 1;
  int size = search_size();
  print_base(seria);
  printf("---------------------------------------\n");
  while (seria <= size) {
    separation(&seria, size);
    print_f(seria);
    print_g(seria);
    merge(&seria);
    print_base(seria);
    printf("---------------------------------------\n");
  }
  return 0;
}