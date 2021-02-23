# Memory Guard
A safer replacement for 'new', allowing automatic memory management in C++.
Memory that is allocated through 'gc::new_object' is automatically freed
when the guard goes out of scope. To extend the lifetime of the buffer, 
the guard can be moved around, but cannot be copied.

## Member functions:
```c++
MemoryGuard(T*); // initialized with a buffer previously allocated by malloc
MemoryGuard(MemoryGuard<T>&&);
MemoryGuard<T>& operator=(MemoryGuard<T>&&);
MemoryGuard<T>& operator=(T*); // the buffer must have been created by malloc
~MemoryGuard(); // frees the associated memory if it is not already freed
void free(); // unconditionally calls 'std::free' on the associated memory, and
// sets the buffer pointer to NULL

void try_freeing(); // calls 'this->free' is the buffer pointer is not NULL
T* get_data(); // retrieves the buffer pointer
T* steal_data(); // retrieves the buffer pointer, leaving it NULL internally
```

## Allocating
In order to have access to a memory guard, you allocate memory through 
'`gc::new_object`'. This function can take arguments which are forwarded
to the constructor of the type being created. The following is the 
signature of the type:
```c++
template <typename T, typename ...Args>
guarded_memory_t<T> new_object(Args&&... args)
```

## Other Types
```c++
template <typename T>
using memory_guard_t = MemoryGuard<T>;

template <typename T>
using guarded_memory_t = std::pair<T*, memory_guard_t<T>>;
```

## Example:
```c++
auto [data, guard] = gc::new_object<int>();
guard.try_freeing();
```
