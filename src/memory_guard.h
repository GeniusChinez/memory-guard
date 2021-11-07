#pragma once

#include <cstddef>
#include <cstdlib>

#include <utility>

namespace gc {
  template <typename T>
  struct MemoryGuard {
    MemoryGuard(T*);
    MemoryGuard() = default;
    MemoryGuard(const MemoryGuard<T>&) = delete;
    MemoryGuard(MemoryGuard<T>&&);

    MemoryGuard<T>& operator=(const MemoryGuard<T>&) = delete;
    MemoryGuard<T>& operator=(MemoryGuard<T>&&);

    MemoryGuard<T>& operator=(T*);

    ~MemoryGuard();

    void free();
    void try_freeing();

    T* get_data();
    T* steal_data();

  private:
    void reset();
    T* data {nullptr};
  };
}
