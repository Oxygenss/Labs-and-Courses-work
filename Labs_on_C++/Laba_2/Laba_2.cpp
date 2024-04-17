#include <Windows.h>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <string>
    HANDLE hConsole;
enum ColorConsole {
  Red = 4,
  White = 7,
  Red_back = 64,
};
// Сделать так, чтобы поле string а классе инициализировалась не в функции
// remove_space, а в конструкторе, при создании объекта класса check
using namespace std;
class check_bracket {
protected:
  string str;

public:
  check_bracket(string temp) { str = temp; }
  void remove_space() {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
  }
  bool search_key_struct() {
    if (str.find("struct") != -1) {
      return 1;
    } else {
      return 0;
    }
  }
  bool search_key_bracket() {
    if ((str.find("}") != -1 && str.find(";") != -1) &&
        (str.find("}") < str.find(";"))) {
      return 1;
    } else {
      return 0;
    }
  }
  void write_str(fstream &temp) { temp << str << endl; }
  void output() {
    for (int i = 0; i < str.size(); i++) {
      cout << str[i];
    }
    cout << endl;
  }
  void output_red() {
    SetConsoleTextAttribute(hConsole, Red);
    for (int i = 0; i < str.size(); i++) {
      cout << str[i];
    }
    SetConsoleTextAttribute(hConsole, White);
    cout << endl;
  }
};
class check_string : public check_bracket {
public:
  check_string(string temp) : check_bracket(temp) {}
  bool check_end_bracket() {
    int i = 3;
    if (str[i] != '}') {
      return false;
    }
    if (isdigit(str[4])) {
      return false;
    }
    if (str.back() != ';') {
      return false;
    }
    for (i = str.find(';'); i < str.size(); i++) {
      if (isalpha(str[i])) {
        return false;
      }
    }
    return true;
  }
  bool check_key_struct(int *flag) {
    if (str.find("{") != -1) {
      (*flag) = 1;
    }
    int i = 3;
    if (str[3] != 's' || str[4] != 't' || str[5] != 'r' || str[6] != 'u' ||
        str[7] != 'c' || str[8] != 't') {
      return false;
    }
    if (isdigit(str[9])) {
      return false;
    }
    return true;
  }
  bool check_inside_string() {
    int flag = 0;
    if (str.find("int") != -1) {
      if (str.find("unsigned") != -1) {
        if (str[3] != 'u' || str[4] != 'n' || str[5] != 's' || str[6] != 'i' ||
            str[7] != 'g' || str[8] != 'n' || str[9] != 'e' || str[10] != 'd' ||
            str[11] != 'i' || str[12] != 'n' || str[13] != 't') {
          return false;
        }
        if (isdigit(str[14])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 15; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else if (str[3] == 'i' || str[4] == 'n' || str[5] == 't') {
        if (isdigit(str[6])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 7; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else {
        return false;
      }
      return true;
    } else if (str.find("short") != -1) {
      if (str.find("unsigned") != -1) {
        if (str[3] != 'u' || str[4] != 'n' || str[5] != 's' || str[6] != 'i' ||
            str[7] != 'g' || str[8] != 'n' || str[9] != 'e' || str[10] != 'd' ||
            str[11] != 's' || str[12] != 'h' || str[13] != 'o' ||
            str[14] != 'r' || str[15] != 't') {
          return false;
        }
        if (isdigit(str[16])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 17; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else if (str[3] == 's' || str[4] == 'h' || str[5] == 'o' ||
                 str[6] == 'r' || str[7] == 't') {
        if (isdigit(str[8])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 9; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else {
        return false;
      }
      return true;
    } else if (str.find("char") != -1) {
      if (str.find("unsigned") != -1) {
        if (str[3] != 'u' || str[4] != 'n' || str[5] != 's' || str[6] != 'i' ||
            str[7] != 'g' || str[8] != 'n' || str[9] != 'e' || str[10] != 'd' ||
            str[11] != 'c' || str[12] != 'h' || str[13] != 'a' ||
            str[14] != 'r') {
          return false;
        }
        if (isdigit(str[15])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 16; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j]) && isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else if (str[3] == 'c' || str[4] == 'h' || str[5] == 'a' ||
                 str[6] == 'r') {
        if (isdigit(str[7])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 8; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else {
        return false;
      }
      return true;
    } else if (str.find("float") != -1) {
      if (str[3] != 'f' || str[4] != 'l' || str[5] != 'o' || str[6] != 'a' ||
          str[7] != 't') {
        return false;
      }
      if (isdigit(str[8])) {
        return false;
      }
      if (str.back() != ';') {
        return false;
      }
      for (int i = 9; i < str.size(); i++) {
        flag = 0;
        if (str[i] == '=') {
          for (int j = i; j < str.size(); j++) {
            if (str[j] == ',' || str[j] == ';') {
              if (!flag) {
                return false;
              }
              break;
            }
            if (isalpha(str[j])) {
              return false;
            } else if (isdigit(str[j])) {
              flag = 1;
            }
          }
        }
      }
      return true;
    } else if (str.find("double") != -1) {
      if (str.find("unsigned") != -1) {
        if (str[3] != 'l' || str[4] != 'o' || str[5] != 'n' || str[6] != 'g' ||
            str[7] != 'd' || str[8] != 'o' || str[9] != 'u' || str[10] != 'b' ||
            str[11] != 'l' || str[12] != 'e') {
          return false;
        }
        if (isdigit(str[13])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 14; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else if (str[3] == 'd' || str[4] == 'o' || str[5] == 'u' ||
                 str[6] == 'b' || str[7] == 'l' || str[8] == 'e') {
        if (isdigit(str[9])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 10; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else {
        return false;
      }
      return true;
    } else if (str.find("bool") != -1) {
      if (str[3] != 'b' || str[4] != 'o' || str[5] != 'o' || str[6] != 'l') {
        return false;
      }
      if (isdigit(str[7])) {
        return false;
      }
      if (str.back() != ';') {
        return false;
      }
      for (int i = 8; i < str.size(); i++) {
        flag = 0;
        if (str[i] == '=') {
          for (int j = i; j < str.size(); j++) {
            if (str[j] == ',' || str[j] == ';') {
              if (!flag) {
                return false;
              }
              break;
            }
            if (isalpha(str[j])) {
              return false;
            } else if (isdigit(str[j])) {
              flag = 1;
            }
          }
        }
      }
      return true;
    } else if (str.find("long") != -1) {
      if (str.find("unsigned") != -1) {
        if (str[3] != 'u' || str[4] != 'n' || str[5] != 's' || str[6] != 'i' ||
            str[7] != 'g' || str[8] != 'n' || str[9] != 'e' || str[10] != 'd' ||
            str[11] != 'l' || str[12] != 'o' || str[13] != 'n' ||
            str[14] != 'g') {
          return false;
        }
        if (isdigit(str[15])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 16; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else if (str[3] == 'l' || str[4] == 'o' || str[5] == 'n' ||
                 str[6] == 'g') {
        if (isdigit(str[7])) {
          return false;
        }
        if (str.back() != ';') {
          return false;
        }
        for (int i = 8; i < str.size(); i++) {
          flag = 0;
          if (str[i] == '=') {
            for (int j = i; j < str.size(); j++) {
              if (str[j] == ',' || str[j] == ';') {
                if (!flag) {
                  return false;
                }
                break;
              }
              if (isalpha(str[j])) {
                return false;
              } else if (isdigit(str[j])) {
                flag = 1;
              }
            }
          }
        }
      } else {
        return false;
      }
      return true;
    }
  }
  int check_key() {
    if (str[1] == 's' && str[2] == 't') {
      return 1;
    }
    if (str[1] == 'e' && str[2] == 'n') {
      return 2;
    }
    if (str[1] == 'i' && str[2] == 'n') {
      return 3;
    }
    if (str[1] == 'a' && str[2] == 'l') {
      return 4;
    }
    return 0;
  }
};
int main() {
  setlocale(LC_ALL, "ru");
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  ifstream file;
  fstream temp;
  string buff, buff1;
  int flag = 0;
  file.open("file.txt");
  temp.open("temp.txt", fstream::in | fstream::out);
  if (file.is_open()) {
    while (!file.eof()) {
      getline(file, buff);
      check_bracket str(buff);
      str.remove_space();
      if (str.search_key_struct()) {
        flag = 1;
        temp << "!st";
        str.write_str(temp);
      } else if (str.search_key_bracket()) {
        flag = 0;
        temp << "!en";
        str.write_str(temp);
      } else if (flag) {
        temp << "!in";
        str.write_str(temp);
      } else {
        temp << "!ou";
        str.write_str(temp);
      }
    }
    getline(file, buff);
    check_bracket str(buff);
    temp << "!al ";
  } else {
    cout << "Ошибка открытия файла";
  }
  file.close();
  temp.close();
  //////////////////////////////////////
  temp.open("temp.txt");
  file.open("file.txt");
  flag = 1;
  int flagBracket = 0;
  if (temp.is_open()) {
    while (!temp.eof()) {
      getline(temp, buff);
      getline(file, buff1);
      check_string original(buff1);
      check_string str(buff);
      if (str.check_key() == 1) {
        if (flag) {
          if (!str.check_key_struct(&flagBracket)) {
            if (flagBracket == 0) {
              original.output_red();
            } else {
              flagBracket = 0;
              original.output();
            }
          } else {
            if (flagBracket == 0) {
              original.output_red();
            } else {
              flagBracket = 0;
              original.output();
            }
          }
        } else {
          original.output_red();
        }
        flag = 0;
      } else if (str.check_key() == 2) {
        flag = 1;
        if (!str.check_end_bracket()) {
          original.output_red();
        } else {
          original.output();
        }
      } else if (str.check_key() == 3) {
        if (!str.check_inside_string()) {
          original.output_red();
        } else {
          original.output();
        }
      } else if (str.check_key() == 4) {
        if (!flag) {
          SetConsoleTextAttribute(hConsole, Red_back);
          cout << " " << endl;
          SetConsoleTextAttribute(hConsole, White);
        }
        break;
      } else {
        original.output();
      }
    }
  } else {
    cout << "Ошибка открытия файла";
  }
  temp.close();
  file.close();
  return 0;
}