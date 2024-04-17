#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#define REPORTSIZE 15000
int *sort(int *a, int len, int lvl, char *report, int *rp);
int *ReadIntegersFromFile(const char *fileName, int *i, char *report, int *rp);
int *RandomGenerator(int _count, const char *outputFileName, int *k,
                     char *report, int *rp);
int NaturaFusion(const char *fileName, char *report, int *rp);
int DualPhaseMerging(const char *fileName, int max_seria, char *report,
                     int *rp);
#define COLOR_BLACK "\x1b[30m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[1;33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGNETA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"
#define STDCOLOR COLOR_WHITE
#define NEEDSORTARRAY COLOR_CYAN
#define SPLITEDARRAY COLOR_BLUE
#define SORTEDARRAY COLOR_GREEN
#define INPUTFILENAME "report.txt"
int main() {
  system("chcp 1251");
  printf("\033[?25l");
  int *a = NULL, rp = 0, k = 0, max_seria; // report pointer
  char report[REPORTSIZE];
  FILE *rep_file;
  while (1) {
    system("cls");
    a = ReadIntegersFromFile(INPUTFILENAME, &k, report, &rp);
    if (k == 0) {
      a = RandomGenerator(10, INPUTFILENAME, &k, report, &rp);
      printf("Массив был пустым: файл автоматически заполнен случайными "
             "числами: ");
    }
    for (int i = 0; i < k; ++i)
      printf("%i ", a[i]);
    printf("\n\n");
    printf("F - Считать массив из файла '%s'\n", INPUTFILENAME);
    printf("G - Сгенерировать массив (и записать в файл '%s')\n\n",
           INPUTFILENAME);
    printf("1 - Сортировка двухпутевым двухфазным естественным слиянием (через "
           "файлы, итеративно)\n");
    // printf("2 - Сортировка двухпутевым нисходящим слиянием (через ОЗУ,
    // рекурсивно)\n");
    printf("2 - Сортировка двухпутевым двуфазным слиянием (через файлы, "
           "итеративно)\n");
    printf("\n0 - Exit)\n");
    switch (_getch()) {
    case 'F':
    case 'f':
      // free(a);
      a = ReadIntegersFromFile(INPUTFILENAME, &k, report, &rp);
      break;
    case 'G':
    case 'g':
      // free(a);
      a = RandomGenerator(0, INPUTFILENAME, &k, report, &rp);
      break;
    case '1':
      rp = 0;
      while (NaturaFusion(INPUTFILENAME, report, &rp) == 0)
        ;
      report[rp] = '\0';
      fopen_s(&rep_file, "report.txt", "w");
      fprintf(rep_file, "%s", report);
      fclose(rep_file);
      puts(report);
      puts("Записано в 'report.txt'");
      puts("Нажмите любую клавишу для подолжения");
      _getch();
      break;
      /*case '2':
      rp = 0;
      int* sorted = sort(a, k, 1, report, &rp);
      report[rp] = '\0';
      fopen_s(&rep_file, "report.txt", "w"); fprintf(rep_file, "%s", report);
      fclose(rep_file);
      puts(report);
      puts("Записано в 'report.txt'");
      puts("Нажмите любую клавишу для подолжения");
      _getch();
      break;*/
    case '2':
      max_seria = 1;
      rp = 0;
      while (DualPhaseMerging(INPUTFILENAME, max_seria, report, &rp) == 0)
        max_seria *= 2;
      report[rp] = '\0';
      fopen_s(&rep_file, "report.txt", "w");
      fprintf(rep_file, "%s", report);
      fclose(rep_file);
      puts(report);
      puts("Записано в 'report.txt'");
      puts("Нажмите любую клавишу для подолжения");
      _getch();
      break;
    case '0':
      system("cls");
      puts("End of program. Goodbye");
      return 0;
    default:
      break;
    }
  }
  return 0;
}
int *sort(int *a, int len, int lvl, char *report, int *rp) {
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\n");
  for (int i = 0 + 1; i < lvl; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\t"); // tabulation
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp,
                   "lvl: %i \tсортировка массива:%s\t", lvl,
                   len > 1 ? NEEDSORTARRAY : SORTEDARRAY); // lvl
  for (int i = 0; i < len; ++i)
    *rp +=
        sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", a[i]); // start array
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%s", STDCOLOR);
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "");
  if (len < 2) {
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\t(отсортирован)");
    return a;
  }
  // распределение
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n");
  for (int i = 0 + 1; i < lvl + 1; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\t"); // tabulation
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "Распределение на\t%s[ ",
                   SPLITEDARRAY);
  int len1 = len / 2, len2 = len - (len / 2);
  int *t1 = (int *)malloc(len1 * sizeof(int));
  int *t2 = (int *)malloc(len2 * sizeof(int));
  for (int i = 0; i < len1; ++i) {
    t1[i] = a[0 + i];
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", t1[i]);
  }
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "]%s и %s[ ", STDCOLOR,
                   SPLITEDARRAY);
  for (int i = 0; i < len2; ++i) {
    t2[i] = a[len1 + i];
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", t2[i]);
  }
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "]%s", STDCOLOR);
  // сортировка
  int *t1_sorted = sort(t1, len1, lvl + 1, report, rp);
  int *t2_sorted = sort(t2, len2, lvl + 1, report, rp);
  // free(t1); free(t2);
  // слияние
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\n");
  for (int i = 0 + 1; i < lvl + 1; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\t"); // tabulation
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "слияние массивов:\t[ ");
  for (int i = 0; i < len1; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ",
                     t1_sorted[i]); // sorted array - merge
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "] и [ ");
  for (int i = 0; i < len2; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ",
                     t2_sorted[i]); // sorted array - merge
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "]\n");
  for (int i = 0 + 1; i < lvl + 1; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\t"); // tabulation
  *rp +=
      sprintf_s(report + *rp, REPORTSIZE - *rp, "в массив:%s\t\t", SORTEDARRAY);
  int *a_sorted = (int *)malloc(len * sizeof(int));
  int i = 0, i_t1 = 0, i_t2 = 0;
  while (i < len) {
    if (i_t1 < len1 && i_t2 < len2) {
      if (t1_sorted[i_t1] < t2_sorted[i_t2])
        a_sorted[i++] = t1_sorted[i_t1++];
      else
        a_sorted[i++] = t2_sorted[i_t2++];
    } else if (i_t1 < len1)
      a_sorted[i++] = t1_sorted[i_t1++];
    else if (i_t2 < len2)
      a_sorted[i++] = t2_sorted[i_t2++];
  }
  for (int i = 0; i < len; ++i)
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ",
                     a_sorted[i]); // merged array - merge
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%s", STDCOLOR);
  // free(t1_sorted);
  // free(t2_sorted);
  //*rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "слияние\n");
  return a_sorted; // a_sorted[0] a_sorted[1] a_sorted[2]
}
int *ReadIntegersFromFile(const char *fileName, int *i, char *report, int *rp) {
  int size = 50;
  *i = 0;
  int *arr = (int *)malloc(size * sizeof(int));
  FILE *f;
  fopen_s(&f, fileName, "r");
  if (f == NULL) {
    printf("Проблемы с чтением файла '%s'", fileName);
    _getch();
    return NULL;
  }
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\nИсходный массив: (");
  int x;
  while (fscanf_s(f, "%i", &x) == 1) {
    if (*i == size) {
      arr = (int *)realloc(arr, (size += 50) * sizeof(int));
    }
    arr[(*i)++] = x;
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, " % i ", x);
  }
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, ")\n\n");
  arr = (int *)realloc(arr, (*i) * sizeof(int));
  fclose(f);
  return arr;
}
int *RandomGenerator(int _count, const char *outputFileName, int *k,
                     char *report, int *rp) {
  system("cls");
  int count;
  *k = 0;
  if (_count < 1) {
    puts("Сколько чисел сгенерировать ?");
    scanf_s("%i", &count);
  } else
    count = _count;
  int *num = (int *)malloc(count * sizeof(int));
  FILE *f;
  fopen_s(&f, outputFileName, "w");
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\nИсходный массив: (");
  for (int i = 0; i < count; ++i, ++(*k)) {
    num[i] = ((rand() % 21) * (rand() % 10 > 5 ? -1 : 1));
    fprintf(f, "%i ", num[i]);
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, " % i ", num[i]);
  }
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, ")\n\n");
  _fcloseall();
  return num;
}
int NaturaFusion(const char *fileName, char *report, int *rp) {
  FILE *inputFile, *A, *B;
  fopen_s(&inputFile, fileName, "r");
  fopen_s(&A, "A.txt", "w");
  fopen_s(&B, "B.txt", "w");
  int now, prev, res, fileSwitcher = 0, inputFile_count = 0,
                      outputFile_count = 0;
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\n%s# Распределение%s:\n",
                   COLOR_BLUE, STDCOLOR);
  res = fscanf_s(inputFile, "%i", &now);
  prev = now;
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "f1 << ");
  while (res != EOF) {
    if (now < prev) {
      fileSwitcher = (fileSwitcher + 1) % 2;
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n%s",
                       fileSwitcher == 0 ? "f1 << " : "f2 << ");
    }
    if (fileSwitcher == 0) {
      fprintf(A, "%d ", now);
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", now);
    } else {
      fprintf(B, "%d ", now);
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", now);
    }
    ++inputFile_count;
    prev = now;
    res = fscanf_s(inputFile, "%i", &now);
  };
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n");
  freopen_s(&inputFile, fileName, "wt", inputFile);
  freopen_s(&A, "A.txt", "r", A);
  freopen_s(&B, "B.txt", "r", B);
  int n1, n2, res1, res2;
  res1 = fscanf_s(A, "%i", &n1);
  res2 = fscanf_s(B, "%i", &n2);
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%s## Слияние:%s\n",
                   COLOR_CYAN, STDCOLOR);
  while (res1 != EOF || res2 != EOF) {
    if (res1 != EOF && res2 != EOF) {
      if (n1 < n2) {
        fprintf(inputFile, "%d ", n1);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n1);
        res1 = fscanf_s(A, "%i", &n1);
        ++outputFile_count;
      } else {
        fprintf(inputFile, "%d ", n2);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n2);
        res2 = fscanf_s(B, "%i", &n2);
      }
    } else if (res1 != EOF) {
      fprintf(inputFile, "%d ", n1);
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n1);
      res1 = fscanf_s(A, "%i", &n1);
      ++outputFile_count;
    } else if (res2 != EOF) {
      fprintf(inputFile, "%d ", n2);
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n2);
      res2 = fscanf_s(B, "%i", &n2);
    }
  }
  fclose(inputFile);
  fclose(A);
  fclose(B);
  if (inputFile_count == outputFile_count) {
    *rp += sprintf_s(report + *rp, REPORTSIZE - *rp,
                     "\n\nв серию вошел весь массив => он %sотсортирован%s\n",
                     SORTEDARRAY, STDCOLOR);
    return 1;
  } else
    return 0;
}
int DualPhaseMerging(const char *fileName, int max_seria, char *report,
                     int *rp) {
  FILE *inputFile, *A, *B;
  fopen_s(&inputFile, fileName, "r");
  fopen_s(&A, "A.txt", "w");
  fopen_s(&B, "B.txt", "w");
  int n, current_seria = 0, res, fileSwitcher = 0, somthInBfile = 0;
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\n%s# Распределение:%s\n",
                   COLOR_BLUE, STDCOLOR);
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\tf1 < ");
  res = fscanf_s(inputFile, "%i", &n);
  while (res != EOF) {
    if (fileSwitcher == 0) {
      fprintf(A, "%d ", n);
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n);
    } else {
      fprintf(B, "%d ", n);
      somthInBfile = 1;
      *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n);
    }
    ++current_seria;
    if (current_seria == max_seria) {
      if (fileSwitcher == 0) {
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\tf2 < ");
        //*rp += sprintf_s(report + *rp, REPORTSIZE - *rp, " > f1\n", n);
      } else {
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n\tf1 < ");
        //*rp += sprintf_s(report + *rp, REPORTSIZE - *rp, " > f2\n", n);
      }
      fileSwitcher = (fileSwitcher + 1) % 2;
      current_seria = 0;
    }
    res = fscanf_s(inputFile, "%i", &n);
  };
  if (somthInBfile == 0) {
    *rp += sprintf_s(
        report + *rp, REPORTSIZE - *rp,
        "серия равна количеству елементов =>%s массив отсортирован%s\n",
        SORTEDARRAY, STDCOLOR);
    fclose(inputFile);
    fclose(A);
    fclose(B);
    return 1;
  }
  // слияние
  freopen_s(&inputFile, fileName, "wt", inputFile);
  freopen_s(&A, "A.txt", "r", A);
  freopen_s(&B, "B.txt", "r", B);
  int n1, n2, res1, res2, l1, l2;
  res1 = fscanf_s(A, "%i", &n1);
  res2 = fscanf_s(B, "%i", &n2);
  *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "\n%s## Cлияние:%s\n\t",
                   COLOR_CYAN, STDCOLOR);
  while (1) {
    l1 = l2 = 0;
    while (l1 < max_seria && l2 < max_seria) {
      if (res1 == EOF || res2 == EOF)
        break;
      if (n1 < n2) {
        fprintf(inputFile, "%d ", n1);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n1);
        ++l1;
        res1 = fscanf_s(A, "%i", &n1);
      } else {
        fprintf(inputFile, "%d ", n2);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n2);
        ++l2;
        res2 = fscanf_s(B, "%i", &n2);
      }
    }
    if (l1 < max_seria) {
      while (l1 < max_seria) {
        if (res1 == EOF)
          break;
        fprintf(inputFile, "%d ", n1);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n1);
        ++l1;
        res1 = fscanf_s(A, "%i", &n1);
      }
    } else if (l2 < max_seria) {
      while (l2 < max_seria) {
        if (res2 == EOF)
          break;
        fprintf(inputFile, "%d ", n2);
        *rp += sprintf_s(report + *rp, REPORTSIZE - *rp, "%i ", n2);
        ++l2;
        res2 = fscanf_s(B, "%i", &n2);
      }
    }
    if (res1 == EOF && res2 == EOF) {
      break;
    } else {
      continue;
    }
  }
  fclose(inputFile);
  fclose(A);
  fclose(B);
  return 0;
}