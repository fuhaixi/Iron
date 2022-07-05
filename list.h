#include<stdlib.h>

template<typename T> class list
{
    struct node{
        T a;
        node * next;
    }
    
private:
    T** heads;
    size_t tail;
    size_t _size;
    size_t data_cap;
    size_t heads_size;
    size_t heads_cap;
public:
    list(/* args */);
    ~list();

    size_t size();

    void push_back(T a);

    T& operator[](const size_t i)const;
};


template<typename T> list<T>::list(/* args */)
{
    heads = new T*[10];
    T* sub_data = new T[100];
    data_cap = 100;
    heads[0] = sub_data;
    tail = 0;
    _size = 0;
}

template<typename T> list<T>::~list()
{

}

template<typename T>T& list<T>::operator[](const size_t i)const{
    return data[i/100][i%100];
}


template <typename T> void list<T>::push_back(T a){
    _size++;
    
}

template <typename T> size_t list<T>::size(){
    return _size;
}