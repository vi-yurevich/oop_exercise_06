#ifndef OOP_EXERCISE_06_ALLOCATOR_H
#define OOP_EXERCISE_06_ALLOCATOR_H

#include <stack>
#include <iostream>
#include <vector>

template<class T, std::size_t BLOCK_SIZE>
class Allocator {
    private:
        std::vector<T*> vec;
        T* buffer;
        size_t countUsed;
    public:
    using allocator_type = Allocator;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

    Allocator(): countUsed(0), buffer(nullptr) {
        static_assert(BLOCK_SIZE > 0, " ");
    }

    ~Allocator() {
        delete[] buffer;
    }

    template<class U> 
    struct rebind {
        using other = Allocator<U, BLOCK_SIZE>;
    };

    T* allocate(std::size_t n) {
        if (buffer == nullptr) {
            buffer = new T [BLOCK_SIZE];
            for (std::size_t i = 0; i < BLOCK_SIZE; ++i){
                vec.push_back(&buffer[i]);
            }
        }
        else if ((vec.size() - countUsed) < n) {
            std::bad_alloc err;
            throw err;
        }
        T* res = nullptr;
        res = vec[countUsed];
        countUsed += n; 
        return (res);
    }

    void deallocate (T* p, std::size_t ) {}

    void destroy(T* p) {
        p->~T();
    }

    template<typename U, typename... Args> 
    void construct(U * p, Args&&...args) {
        new (p) U(std::forward<Args>(args)...);
    }  
};

#endif //OOP_EXERCISE_06_ALLOCATOR_H