#pragma once
#include <vector>
#include <memory>
#include <limits>
#include <iostream>

template<typename T>
class myAllocator {
    private:
    size_t capacity; //максимальная вместимость пула
    size_t index; //индекс текущего свободный элемент
    size_t blockSize; //размер пула
    T* curBlock; //указатель на текущий пул
    std::vector<T*> blocks; // вектор указателей на пулы
    std::vector<T*> vecOfFree; // вектор их ранее освобождённых слотов 

    public:
    using value_type = T;  //  с каким типом работает аллокатор
    using pointer = T*;  // какой тип указателя возвращает аллокейт
    using const_pointer = const T*;
    using reference = T&; //ссылки в аллокаторе
    using const_reference = const T&; 
    using size_type = std::size_t;// тип используемый для размеров
    using difference_type = std::ptrdiff_t; //тип для разницы между двумя указателями

    template <class U>
    struct rebind {
        using other = myAllocator<U>;
    };

    //конструктор с параметром кол-ва выделяемых за раз элементов
    explicit myAllocator(size_t Blocksize = 1)
        : blockSize(Blocksize ? Blocksize : 1), capacity(0), index(0), curBlock(nullptr) {}

    // конструктор копирования для разных типов
    template<typename U>
    myAllocator(const myAllocator<U>& other)
        : capacity(0), index(0), blockSize(other.getBlockSize()), curBlock(nullptr) {}

    ~myAllocator() { //деструктор все освобождает
        free_all(); 
    }

    //создает объект в уже выделенной памяти
    //на вход принимает тип объекта который мы хотим создать и переменное количество аргументов
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new ((void*)p) U(std::forward<Args>(args)...); //вызывает только конструктор типа U
        // (void*) приводит к указателю без типа потому что new его приниммает
        //форвард передаёт каждый аргумент в том же виде в каком он пришёл чтобы правильный конструктор выбрался
    }

    //удаляет объект оставляет память
    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    T* allocate(size_t n) {
    if (n == 0) return nullptr;

    if (n == 1) {
        // Используем пул только для n = 1
        if (!vecOfFree.empty()) {
            T* ptr = vecOfFree.back();
            vecOfFree.pop_back();
            return ptr;
        }
        if (curBlock == nullptr || index >= capacity) {
            expand();
        }
        T* ptr = curBlock + index;
        ++index;
        std::cout << "\nUse " << index << " memory of " << capacity;
        return ptr;
    } else {
        // Для n > 1 всегда используем блоки
        std::cout << "\nblock allocated: " << n;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
}

    void expand() {
        T* new_block = static_cast<T*>(::operator new(blockSize * sizeof(T)));
        blocks.push_back(new_block);
        curBlock = new_block;
        index = 0;
        capacity = blockSize;
        std::cout << "\nallocated new block with size " << blockSize;
    }

    void free_all() {
        for (T* block : blocks) {
            ::operator delete(block);
        }
        blocks.clear();
        vecOfFree.clear();
        index = 0;
        capacity = 0;
        curBlock = nullptr;
        std::cout << "\nmemory cleared";
    }
    //поэлементное освобождение
    void deallocate(T* p, size_t n) noexcept {
    if (n == 1) {
        vecOfFree.push_back(p);
    } else {
        ::operator delete(p);
    }
}

    size_t getBlockSize() const {
        return blockSize;
    }

    //это говорит что все экземпляры этого аллокатора равны
    //это для совместимости
    bool operator==(const myAllocator&) const noexcept { return true; }
    bool operator!=(const myAllocator&) const noexcept { return false; }
};
