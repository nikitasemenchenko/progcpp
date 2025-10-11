#pragma once
#include <memory>

template<typename T>
struct Node{
    T value;
    std::unique_ptr<Node<T>> next;
    Node(T& val){
        value = val;
        next = nullptr;
    }
    Node(T&& val){
        value = std::move(val);
        next = nullptr;
    }
};

template<typename T>
class singlyLinkedList {
    private:
    std::unique_ptr<Node<T>> head;
    int length;

    public:
    singlyLinkedList(){
        head = nullptr;
        length = 0;
    }
    singlyLinkedList(singlyLinkedList&& list){
            head = std::move(list.head);
            length = list.length;

            list.head = nullptr;
            list.length = 0;
        }
    ~singlyLinkedList() = default;

    void push_back(T& value){
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(value);
        if (head == nullptr) {
            head = std::move(newNode);
            length++;
            return;
        }

        Node<T>* cur = head.get();
        while (cur->next != nullptr) {
            cur = cur->next.get();
        }

        cur->next = std::move(newNode);
        length++;
    }

    void push_back(T&& value){
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(std::move(value));
        if (head == nullptr) {
            head = std::move(newNode);
            length++;
            return;
        }

        Node<T>* cur = head.get();
        while (cur->next != nullptr) {
            cur = cur->next.get();
        }

        cur->next = std::move(newNode);
        length++;
    }

    void print() {
        Node<T>* cur = head.get();
        while (cur!= nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->next.get();
        }
        std::cout << '\n';
    }
    int size(){
        return length;
    }
    T& operator[](int index){
        if(index<0 || index >= length) throw std::out_of_range("Index out of range");

        int cnt = 0;
        Node<T>* cur = head.get();
        while(cnt < index){
            cur = cur->next.get();
            cnt++;
        }
        return cur->value;
    }

    void insert(T&& value, int position){
        if (position > length || position < 0) throw std::out_of_range("Index out of range");;

        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(std::move(value));
        if(position == 0){
            newNode->next = std::move(head);
            head = std::move(newNode);
            length++;
            return;
        }
        int cnt = 0;
        Node<T>* cur = head.get();
        while(cnt < position-1){
            cur = cur->next.get();
            cnt++;
        }
        newNode->next = std::move(cur->next);
        cur->next = std::move(newNode);
        length++;
    }

    void insert(T& value, int position){
        if (position > length || position < 0) throw std::out_of_range("Index out of range");;

        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(std::move(value));
        if(position == 0){
            newNode->next = std::move(head);
            head = std::move(newNode);
            length++;
            return;
        }
        int cnt = 0;
        Node<T>* cur = head.get();
        while(cnt < position-1){
            cur = cur->next.get();
            cnt++;
        }
        newNode->next = std::move(cur->next);
        cur->next = std::move(newNode);
        length++;
    }

    void erase(int position){
        if(position >=length || position <0) throw std::out_of_range("Index out of range");
        if(position == 0){
            head = std::move(head->next);
            length--;
            return;
        }
        int cnt = 0;
        Node<T>* cur = head.get();
        while(cnt < position-1){
            cur = cur->next.get();
            cnt++;
        }
        cur->next = std::move(cur->next->next);
        length--;
    }

    singlyLinkedList& operator=(singlyLinkedList&& list){
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
    
    singlyLinkedList& operator=(singlyLinkedList& list){
            if(this == &list){
                return *this;
            }
            else{
                head.reset();
                length = 0;
                Node<T>* cur = list.head.get();
                while(cur != nullptr) {
                    push_back(cur->value);
                    cur = cur->next.get();
                }

                return *this;
            }
        }
};