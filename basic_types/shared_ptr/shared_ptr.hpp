#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtr {
  class ControlBlock {
  public:
    ControlBlock(T *ptr, int reference_counter, Deleter deleter) = default;
    void FreeMemory() {
      if (ptr_) {
        deleter_(ptr_);
      }
    }
    void DecreaseCounter() { reference_counter_--; }
    void IncreaseCounter() { reference_counter_++; }
    void NeedToFreeMemory() { return reference_counter_ < 1; }
    int reference_counter() const { return reference_counter_; }

  private:
    T *ptr_;
    int reference_counter_;
    Deleter deleter_;
  };

public:
  explicit SharedPtr(T *ptr)
      : managed_ptr_{ptr}, control_block_{new ControlBlock{ptr, {}, {}}} {}

  SharedPtr(const SharedPtr &other)
      : managed_ptr_{other.managed_ptr_}, control_block_{other.control_block_} {
    if (control_block_) {
      control_block_->IncreaseCounter();
    }
  }
  SharedPtr &operator=(const SharedPtr &other) {
    managed_ptr_ = other.managed_ptr_;
    control_block_ = other.control_block_;
    control_block_->IncreaseCounter();
  }
  SharedPtr(SharedPtr &&other) = default;
  SharedPtr &operator=(SharedPtr &&other) = default;

  ~SharedPtr() {
    if (control_block_) {
      control_block_->DecreaseCounter();
      if (control_block_->NeedToFreeMemory) {
        control_block_->FreeMemory();
      }
    }
  }

  T *get() { return managed_ptr_; }

  void reset(T *ptr) {
    if (control_block_) {
      control_block_->DecreaseCounter();
      if (control_block_->NeedToFreeMemory()) {
        control_block_->FreeMemory();
      }
    }
    delete control_block_;
    control_block_ = new ControlBlock{ptr, 1, {}};
    managed_ptr_ = ptr;
  }

  T *release() {
    T *ptr = managed_ptr_;
    managed_ptr_ = nullptr;
    delete control_block_;
    control_block_ = nullptr;
    return ptr;
  }

  void swap(const SharedPtr &other) {
    std::swap(other.managed_ptr_, managed_ptr_);
    std::swap(other.control_block_, control_block_);
  }

  const T &operator*() const { return *managed_ptr_; }
  T &operator*() { return *managed_ptr_; }
  T *operator->() { return managed_ptr_; }
  operator bool() const { return managed_ptr_ != nullptr; }

private:
  T *managed_ptr_{};
  ControlBlock *control_block_{};
};
