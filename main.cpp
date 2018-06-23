#include <iostream>
#include <initializer_list>

namespace stu
{

template<class T>
class forward_list
{

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;

    struct Node
    {
        Node* m_next = nullptr;
        T m_value;
        Node() = default;
        explicit Node(T value) : m_value(value) {};
    };

    class _iterator
    {
    public:
        Node* m_current = nullptr;
        _iterator() = default;
        explicit _iterator(Node* current) : m_current(current){};

        value_type operator*();
        iterator& operator=(const _iterator& that);
        iterator& operator++();
        bool operator!=(const _iterator& oper2);
    };

    Node* m_head = nullptr;

    size_type m_size = 0;
    forward_list() = default;
    forward_list(std::initializer_list<T> l)
    {
        for(typename std::initializer_list<T>::iterator i = l.begin(); i != l.end(); ++i)
        {
            push_back(*i);
        }
    }

    void push_back(value_type value);
    Node* getLast();
    void printforward_list();
    iterator begin();
    iterator end();


};


//---------------------------------------------
template<class T>
void forward_list<T>::push_back(value_type value)
{
    if(m_head == nullptr)
        m_head = new Node(value);
    else
    {
        Node* temp = getLast();
        temp->m_next = new Node(value);
    }
    m_size++;
}

template<class T>
typename forward_list<T>::Node* forward_list<T>::getLast()
{

    Node* i = m_head;
    for(; i->m_next != nullptr; i = i->m_next);
    return i;
}

template<class T>
void forward_list<T>::printforward_list()
{
    Node* i = m_head;
    for(; i != nullptr; i = i->m_next)
        std::cout << i->m_value <<" ";
}

template<class T>
typename forward_list<T>::iterator forward_list<T>::begin()
{
    return iterator(m_head);
}


//------------------------------------------------------------

template<class T>
T forward_list<T>::_iterator::operator*()
{
    return m_current->m_value;
}

template<class T>
typename forward_list<T>::iterator&
forward_list<T>::_iterator::operator=(const forward_list<T>::_iterator& that)
{
    this->m_current = that->m_current;
    return *this;
}

template<class T>
typename forward_list<T>::iterator&
forward_list<T>::_iterator::operator++()
{
    m_current = m_current->m_next;
    return *this;
}

template<class T>
bool forward_list<T>::_iterator::operator!=(const forward_list<T>::_iterator& oper2)
{
    return m_current != oper2.m_current;
}

//------------------------------------------------------------------------

template<class T>
typename forward_list<T>::iterator
forward_list<T>::end()
{
    Node* temp = getLast();
    return iterator(temp->m_next);
}

}

int main()
{
    stu::forward_list<int> arr;
    arr.push_back(3);
    arr.push_back(4);
    arr.printforward_list();
    return 0;
}
