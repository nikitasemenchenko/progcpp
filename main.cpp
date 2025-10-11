#include <iostream>
#include "myvector.h"
#include "singlyLinkedList.h"

int main(){
    std::cout << "myvector: "<<std::endl;
    myvector<int> x;
    for(int i = 0; i< 10; ++i){
        x.push_back(i);
    }
    x.print();
    std::cout<<x[2]<<std::endl;
    std::cout << x.size() << std::endl;
    x.erase(6); 
    x.erase(4); 
    x.erase(2);
    x.print();
    x.insert(10, 0);
    x.print();
    x.insert(20, x.size()/2);
    x.print();
    x.insert(30, x.size());
    x.print();

    myvector<int> a = std::move(x);
    x.print();
    a.print();

    myvector<int> b;
    b = a;
    a.print();
    b.print();

    myvector<int> c;
    c = std::move(b);
    b.print();
    c.print();

    std::cout << "\nsinglyLinkedList: "<<std::endl;
    singlyLinkedList<int> l;

    for(int i = 0; i< 10; ++i){
        l.push_back(i);
    }
    l.print();
    std::cout<<l[2]<<std::endl;
    std::cout<<l.size()<<std::endl;
    l.erase(6); 
    l.erase(4); 
    l.erase(2);
    l.print();
    l.insert(10, 0);
    l.print();
    l.insert(20, l.size()/2);
    l.print();
    l.insert(30, l.size());
    l.print();

    singlyLinkedList<int> m = std::move(l);
    l.print();
    m.print();

    singlyLinkedList<int> n;
    n = m;
    m.print();
    n.print();

    singlyLinkedList<int> k;
    k = std::move(n);
    n.print();
    k.print();

    std::cout << "\ndoublyLinkedList: "<<std::endl;
    singlyLinkedList<int> w;

    for(int i = 0; i< 10; ++i){
        w.push_back(i);
    }
    w.print();
    std::cout<<w[2]<<std::endl;
    std::cout<<w.size()<<std::endl;
    w.erase(6); 
    w.erase(4); 
    w.erase(2);
    w.print();
    w.insert(10, 0);
    w.print();
    w.insert(20, w.size()/2);
    w.print();
    w.insert(30, w.size());
    w.print();

    singlyLinkedList<int> v = std::move(w);
    w.print();
    v.print();

    singlyLinkedList<int> u;
    u = v;
    v.print();
    u.print();

    singlyLinkedList<int> y;
    y = std::move(u);
    u.print();
    y.print();

}
