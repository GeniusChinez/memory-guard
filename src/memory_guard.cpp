#pragma once
#include "memory_guard.h"

namespace gc {
  template <typename T>
  MemoryGuard<T>::MemoryGuard(T* data) {
    this->data = data;
  }

  template <typename T>
  MemoryGuard<T>::~MemoryGuard() {
    try_freeing();
  }

  template <typename T>
  MemoryGuard<T>::MemoryGuard(MemoryGuard<T>&& another) {
    data = another.steal_data();
  }

  template <typename T>
  MemoryGuard<T>& MemoryGuard<T>::operator=(MemoryGuard<T>&& another) {
    try_freeing();
    data = another.steal_data();
    return *this;
  }

  template <typename T>
  void MemoryGuard<T>::free() {
    std::free(data);
    reset();
  }

  template <typename T>
  void MemoryGuard<T>::try_freeing() {
    if (data) {
      free();
    }
  }

  template <typename T>
  MemoryGuard<T>& MemoryGuard<T>::operator=(T* data) {
    this->data = data;
    return *this;
  }

  template <typename T>
  T* MemoryGuard<T>::get_data() {
    return data;
  }

  template <typename T>
  void MemoryGuard<T>::reset() {
    data = NULL;
  }

  template <typename T>
  T* MemoryGuard<T>::steal_data() {
    auto temp = data;
    data = NULL;
    return temp;
  }

  template <typename T>
  using memory_guard_t = MemoryGuard<T>;

  template <typename T>
  using guarded_memory_t = std::pair<T*, memory_guard_t<T>>;

  template <typename T, typename ...Args>
  guarded_memory_t<T> new_object(Args&&... args) {
    auto buffer = std::malloc(sizeof(T));
    auto item = new (buffer) T(std::forward<Args>(args)...);
    return {item, item};
  }
}
