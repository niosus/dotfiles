template <typename T> class UniquePtr {
public:
  UniquePtr(const UniquePtr& other) = delete;

  explicit UniquePtr(T *ptr) : managed_ptr_{ptr} {}
  ~UniquePtr() { delete managed_ptr_; }

  T *get() { return managed_ptr_; }
  void reset(T *ptr) {
    // TODO
  }

  void swap(const UniquePtr &other) {}

private:
  T *managed_ptr_{};
};

