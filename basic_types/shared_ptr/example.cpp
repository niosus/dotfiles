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
  UniquePtr<int> ptr{new int{42}};
  UniquePtr<A> ptr_a{new A{42}};
  UniquePtr<A> ptr_b{std::move(ptr_a)};
  std::cerr << "ptr: " << *ptr << std::endl;
  std::cerr << "ptr: " << *(ptr.get()) << std::endl;
  std::cerr << "ptr: " << ptr_b->a << std::endl;
  auto ptr_released = ptr_b.release();
  std::cerr << "ptr: " << ptr_released->a << std::endl;
  delete ptr_released;
  return 0;
}
