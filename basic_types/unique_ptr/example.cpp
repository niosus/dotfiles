#include "unique_ptr/unique_ptr.hpp"

#include <iostream>

struct A
{
  int a;
};

struct B : public A
{
  int b;
};

int main(int argc, char const *argv[])
{
  UniquePtr<int> ptr{new int{42}};
  UniquePtr<B> ptr_b{new B};
  ptr_b->a = 23;
  ptr_b->b = 42;
  UniquePtr<A> ptr_a{new A{42}};
  std::cerr << "ptr: " << *ptr << std::endl;
  std::cerr << "ptr: " << *(ptr.get()) << std::endl;
  std::cerr << "ptr: " << ptr_b->b << std::endl;
  UniquePtr<A> ptr_bb{std::move(ptr_b)};
  std::cerr << "ptr: " << ptr_bb->a << std::endl;
  auto ptr_released = ptr_bb.release();
  std::cerr << "ptr: " << ptr_released->a << std::endl;
  delete ptr_released;
  return 0;
}
