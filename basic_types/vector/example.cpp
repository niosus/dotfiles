#include "vector/vector.hpp"

#include <iostream>

struct A {
  int a;
  A() : a{} {}
  A(int a_) : a{a_} {}
  A(const A &other) : a{other.a} { std::cerr << "copy " << a << std::endl; }
  A(A &&other) : a{std::move(other.a)} {
    std::cerr << "move " << a << std::endl;
  }
  A &operator=(A &&other) {
    a = std::move(other.a);
    std::cerr << "move assign " << a << std::endl;
    return *this;
  }
  ~A() { std::cerr << "deleter " << a << std::endl; }
};

struct B : public A {
  int b;
};

int main(int argc, char const *argv[]) {
  Vector<A> vector_a;
  std::cerr << "push" << std::endl;
  vector_a.PushBack(A{42});
  std::cerr << vector_a.front().a << std::endl;
  std::cerr << "push" << std::endl;
  vector_a.PushBack(A{23});
  std::cerr << vector_a.front().a << std::endl;
  std::cerr << "erase" << std::endl;
  vector_a.Erase(0);
  std::cerr << vector_a.front().a << std::endl;
  return 0;
}
