#pragma once
#include <memory>

template<typename T>
struct DoubleNode{
    T value;
    std::shared_ptr<DoubleNode<T>> next;
    std::weak_ptr<DoubleNode<T>> prev;
    DoubleNode(T& val){
        value = val;
        next = nullptr;
        prev = nullptr;
    }
    DoubleNode(T&& val){
        value = std::move(val);
        next = nullptr;
        prev = nullptr;
    }
};

template<typename T>
class doublyLinkedList {
    private:
    std::shared_ptr<DoubleNode<T>> head;
    int length;

    public:
    doublyLinkedList(){
        head = nullptr;
        length = 0;
    }
    doublyLinkedList(doublyLinkedList&& list){
            head = std::move(list.head);
            length = list.length;

            list.head = nullptr;
            list.length = 0;
        }
    ~doublyLinkedList() = default;

    void push_back(T& value){
        std::shared_ptr<DoubleNode<T>> newNode = std::make_shared<DoubleNode<T>>(value);
        if (head == nullptr) {
            head = newNode;
            length++;
            return;
        }

        auto cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        newNode->prev = cur;
        cur->next = newNode;
        length++;
    }

    void push_back(T&& value){
        std::shared_ptr<DoubleNode<T>> newNode = std::make_shared<DoubleNode<T>>(std::move(value));
        if (head == nullptr) {
            head = newNode;
            length++;
            return;
        }

        auto cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        newNode->prev = cur;
        cur->next = newNode;
        length++;
    }

    void print() {
        auto cur = head;
        while (cur!= nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }
    int size(){
        return length;
    }
    T& operator[](int index){
        if(index<0 || index >= length) throw std::out_of_range("Index out of range");

        int cnt = 0;
        auto cur = head;
        while(cnt < index){
            cur = cur->next;
            cnt++;
        }
        return cur->value;
    }

    void insert(T&& value, int position){
        if (position > length || position < 0) throw std::out_of_range("Index out of range");;

        std::shared_ptr<DoubleNode<T>> newNode = std::make_shared<DoubleNode<T>>(std::move(value));
        if(position == 0){
            if (head!= nullptr) {
                head->prev = newNode;
                newNode->next = head;
            }
            head = newNode;
            length++;
            return;
        }
        auto cur = head;
        int cnt = 0;
        while(cnt < position-1){
            cur = cur->next;
            cnt++;
        }
        newNode->next = cur->next;
        if(newNode->next != nullptr){
            newNode->next->prev = newNode;
        }
        newNode->prev = cur;
        cur->next = newNode;
        length++;
    }

    void insert(T& value, int position){
        if (position > length || position < 0) throw std::out_of_range("Index out of range");;

        std::shared_ptr<DoubleNode<T>> newNode = std::make_shared<DoubleNode<T>>(value);
        if(position == 0){
            if (head!= nullptr) {
                head->prev = newNode;
                newNode->next = head;
            }
            head = newNode;
            length++;
            return;
        }
        auto cur = head;
        int cnt = 0;
        while(cnt < position-1){
            cur = cur->next;
            cnt++;
        }
        newNode->next = cur->next;
        if(newNode->next != nullptr){
            newNode->next->prev = newNode;
        }
        newNode->prev = cur;
        cur->next = newNode;
        length++;
    }

    void erase(int position){
        if(position >=length || position <0) throw std::out_of_range("Index out of range");
        if(position == 0){
            if (head->next == nullptr) {
                head.reset();
            } else {
                auto newHead = head->next;
                newHead->prev.reset();
                head = newHead;
            }
            length--;
            return;
        }
        int cnt = 0;
        auto cur = head;
        while(cnt < position-1){
            cur = cur->next;
            cnt++;
        }
        cur->next = cur->next->next;
        if(cur-> next != nullptr){
           cur-> next-> prev = cur; 
        }
        length--;
    }

    doublyLinkedList& operator=(doublyLinkedList&& list){
            if(this == &list){
                return *this;
            }
            else{
                head = std::move(list.head);
                length = list.length;

                list.head = nullptr;
                list.length = 0;
                return *this;
            }
        }
    
    doublyLinkedList& operator=(doublyLinkedList& list){
            if(this == &list){
                return *this;
            }
            else{
                head.reset();
                length = 0;
                auto cur = list.head;
                while(cur != nullptr) {
                    push_back(cur->value);
                    cur = cur->next;
                }

                return *this;
            }
        }
};