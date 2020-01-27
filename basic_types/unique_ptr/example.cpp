#include "unique_ptr/unique_ptr.hpp"

#include <iostream>

struct A
{
  int a;
};

struct B
{
  int a;
};

int main(int argc, char const *argv[])
{
  UniquePtr<A> ptr{new A};
  std::cerr << "ptr: " << ptr.get() << std::endl;
  return 0;
}
