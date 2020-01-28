#ifndef HOME_IGOR_CODE_INTERVIEW_QUESTIONS_BASIC_TYPES_VECTOR_VECTOR_H_pp
#define HOME_IGOR_CODE_INTERVIEW_QUESTIONS_BASIC_TYPES_VECTOR_VECTOR_H_pp

#include <iostream>

template <typename T> class Vector {
  const std::size_t kMinCapacity{10ul};

public:
  Vector() { ReallocateIfNeeded(0ul); }
  Vector(std::size_t size, T value_init) {
    ReallocateIfNeeded(size);
    std::fill(data_, data_ + size, value_init);
  }
  ~Vector() noexcept {
    if (data_) {
      delete[] data_;
      data_ = nullptr;
    }
  }

  void PushBack(const T &obj) {
    ReallocateIfNeeded(size_ + 1);
    data_[size_] = obj;
    size_++;
  }

  void PushBack(T &&obj) {
    ReallocateIfNeeded(size_ + 1);
    data_[size_] = std::move(obj);
    size_++;
  }

  void Erase(std::size_t index) {
    std::move(data_ + index + 1, data_ + size_, data_ + index);
    size_--;
    ReallocateIfNeeded(size_);
  }

  T &front() noexcept { return data_[0]; }
  const T &front() const noexcept { return data_[0]; }
  T &back() noexcept { return data_[size_ - 1]; }
  const T &back() const noexcept { return data_[size_ - 1]; }

private:
  void ReallocateIfNeeded(std::size_t new_size) {
    const auto new_capacity = CalculateNewCapacity(new_size);
    if (new_capacity != capacity_) {
      Reallocate(new_capacity);
      capacity_ = new_capacity;
    }
  }

  void Reallocate(std::size_t new_capacity) {
    T *new_data = new T[new_capacity];
    if (data_) {
      std::move(data_, data_ + size_, new_data);
      delete[] data_;
    }
    data_ = new_data;
  }

  std::size_t CalculateNewCapacity(std::size_t new_size) const noexcept {
    if (new_size < 1ul) {
      return capacity_;
    }
    std::size_t new_capacity{std::max(capacity_, kMinCapacity)};
    while (new_size > new_capacity / 2ul) {
      new_capacity *= 2ul;
    }
    while (new_size < new_capacity / 4ul) {
      new_capacity /= 2ul;
    }
    return std::max(new_capacity, kMinCapacity);
  }

  T *data_{};
  std::size_t size_{};
  std::size_t capacity_{};
};

#endif // HOME_IGOR_CODE_INTERVIEW_QUESTIONS_BASIC_TYPES_VECTOR_VECTOR_H_pp
