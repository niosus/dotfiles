#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
public:
  using pointer_type = T *;
  using deleter_type = Deleter;

  UniquePtr(const UniquePtr &other) = delete;
  UniquePtr &operator=(const UniquePtr &other) = delete;

  explicit UniquePtr(T *ptr) : managed_ptr_{ptr}, deleter_{} {}

  UniquePtr(UniquePtr &&other) = default;
  UniquePtr &operator=(UniquePtr &&other) = default;

  template <typename U, typename UDeleter = Deleter,
            typename = std::enable_if<std::is_convertible<U *, T *>::value>>
  UniquePtr(UniquePtr<U, UDeleter> &&other) {
    managed_ptr_ = other.release();
    deleter_ = UDeleter{};
  }

  ~UniquePtr() {
    if (managed_ptr_) {
      deleter_(managed_ptr_);
    }
  }

  T *get() { return managed_ptr_; }

  void reset(T *ptr) {
    if (managed_ptr_) {
      deleter_(managed_ptr_);
    }
    managed_ptr_ = ptr;
  }

  T *release() {
    T *ptr = managed_ptr_;
    managed_ptr_ = nullptr;
    return ptr;
  }

  void swap(const UniquePtr &other) {
    using std::swap;
    swap(other.managed_ptr_, managed_ptr_);
    swap(other.deleter_, deleter_);
  }

  const T &operator*() const { return *managed_ptr_; }
  T &operator*() { return *managed_ptr_; }

  T *operator->() { return managed_ptr_; }

  operator bool() const { return managed_ptr_ != nullptr; }

private:
  T *managed_ptr_{};
  Deleter deleter_;
};
