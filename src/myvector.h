#pragma once

#include <stdexcept>
#include <iostream>
#include <utility>
#include <memory>

template <typename T> 
class myvector {
    private:
    std::unique_ptr<T[]> data;
    int capacity = 1;
    int length = 0;

    void resize(){
        capacity*=2;
        std::unique_ptr<T[]> newData(new T[capacity]);
        for(int i = 0; i<length; ++i){
            newData[i] = data[i];
        }
        data = std::move(newData);
    }

    public:
        myvector(){
            capacity = 1;
            length = 0;
            data = std::unique_ptr<T[]>(new T[capacity]);
        }
        myvector(myvector&& vect){
            data = std::move(vect.data);
            capacity = vect.capacity;
            length = vect.length;

            vect.data = nullptr;
            vect.capacity = 0;
            vect.length = 0;
        }
        ~myvector() = default;

        int size(){
            return length;
        }
        void push_back(T& value){
            if(length == capacity){
                resize();
            }
            data[length] = value;
            length++;
        }
        void push_back(T&& value){
            if(length == capacity){
                resize();
            }
            data[length] = std::move(value);
            length++;
        }

        void insert(T&& value, int position){
            if (position > length || position < 0) throw std::out_of_range("Index out of range");;
            if (length == capacity){
                resize();
            }
            for(int i = length; i > position; --i){
                data[i] = data[i-1];
            }
            data[position] = std::move(value);
            length++;
        }

        void insert(T& value, int position){
            if (position > length || position < 0) throw std::out_of_range("Index out of range");;
            if (length == capacity){
                resize();
            }
            for(int i = length; i > position; --i){
                data[i] = data[i-1];
            }
            data[position] = value;
            length++;
        }

        void erase(int position){
            if(position >=length || position <0) throw std::out_of_range("Index out of range");
            for(int i = position; i<length-1; ++i){
                data[i]=data[i+1];
            }
            length--;
        }

        T& operator[](int index){
            if(index<0 || index >= length) throw std::out_of_range("Index out of range");
            return data[index];
        }
        
        void print(){
            for(int i = 0; i < length; ++i){
                std::cout<< data[i] << ' ';
            }
            std::cout << '\n';
        }

        myvector& operator=(myvector&& vect){
            if(this == &vect){
                return *this;
            }
            else{
                data = std::move(vect.data);
                capacity = vect.capacity;
                length = vect.length;

                vect.data = nullptr;
                vect.capacity = 0;
                vect.length = 0;
                return *this;
            }
        }
        myvector& operator=(myvector& vect){
            if(this == &vect){
                return *this;
            }
            else{
                std::unique_ptr<T[]> newData(new T[vect.capacity]);
                for (int i = 0; i < vect.length; ++i) {
                    newData[i] = vect.data[i];
                }
                data = std::move(newData);
                capacity = vect.capacity;
                length = vect.length;

                return *this;
            }
        }

        class Iterator {
        T* ptr;
        public:
            Iterator(T* p){
                ptr = p;
            }
            T& operator*() {return *ptr;}
            T& get() {return *ptr;}
            Iterator& operator++() {++ptr; return *this;}
            bool operator!=(const Iterator& other) {return ptr != other.ptr;}
        };

    Iterator begin() {return Iterator(data.get());}
    Iterator end() {return Iterator(data.get() + length);}
};
