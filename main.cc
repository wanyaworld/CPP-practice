#include <string>
#include <iostream>
#include <string.h>

class DataClass {
  public:
  char *data;
  DataClass() { init(); }
  DataClass(const DataClass&) { init(); }
  ~DataClass() { 
    if (data) delete[] data; }
  void init() {
    data = new char[10000]();
  }
  DataClass& operator=(const DataClass& param) {
    for (int i = 0 ; i < 100000 ; i++)
      data[i] = param.data[i];
    std::cout << "Copy assigned !!" << std::endl;
    return *this;
  }
  DataClass& operator=(DataClass&& param) {
    char *tmp = data;
    data = param.data;
    param.data = tmp;
    std::cout << "Move assigned !!" << std::endl;
    return *this;
  }
};

class MyClass {
  public:
    DataClass dc;
};

void func_lval(MyClass param) {
  MyClass lval;
  strcpy(param.dc.data, "data");
  lval = (param);
  printf("%s\n", lval.dc.data);
}

void func_rval(MyClass param) {
  MyClass lval;
  strcpy(param.dc.data, "data");
  lval = std::move(param);
  printf("%s\n", lval.dc.data);
}

int main() {
  func_lval(MyClass());
  func_rval(MyClass());
  return 0;
}
