#include "list.h"

template<typename T>
List<T>::List(const std::initializer_list<T> &init_list) : List<T>()
{
    for (const auto &i : init_list)
        push_back(i);
}

template<typename T>
List<T>::List() /*:
    _begin(nullptr),
    _end(new Block(0))/*,
    _size(0)*/
{
    _begin = nullptr,
            _end = new Block(T()),
            _size = 0;
}

template<typename T>
List<T>::~List()
{
    size_t sz = size();
    Block *tmp;
#include <iostream>
    while (sz > 0) {
        std::cout << "Delete " << _begin << '\n';
        tmp = _begin->next;
        delete _begin;
        _begin = tmp;
        --sz;
    }
    if (_end)
        delete _end;
}

template<typename T>
bool List<T>::operator == (const List<T> &comp_list)
{
    if (this->_size != comp_list._size)
        return false;

    auto iter1 = this->begin();
    auto iter2 = comp_list.begin();

    for (; iter1 != this->end(); ++iter1, ++iter2)
        if (iter1.data() != iter2.data())
            return false;

    return true;
}

template<typename T>
List<T> &List<T>::operator =(const List<T> &src)
{

    const size_t count = std::min(_size, src._size);

    auto iter_my = begin();
    auto iter_src = src.begin();

    for (int i = 0; i < count; ++i, ++iter_my, ++iter_src) {
        iter_my.data() = iter_src.data();
    }

    if (src._size > _size) {

        for (; iter_src != src.end(); ++iter_src){
            push_back(iter_src.data());
        }
    }
    else {
        size_t sz = _size - count;
        for (int i = 0; i < sz; i++)
            pop_front();
    }
    return *this;
}

template<typename T>
void List<T>::push_back(const T &value)
{
    if (empty()){
        push_front(value);
        return;
    }
    Block *tmp = new Block(value);

    if (!_begin) {

        _begin = tmp;
        _end->prev = _begin;
        _begin->next = _end;
    }

    else {

        tmp->next = _end;
        tmp->prev = _end->prev;
        _end->prev->next = tmp;
        _end->prev = tmp;

    }

    ++_size;
}

template<typename T>
void List<T>::push_back(T &&value)
{
    const T &tmp = value;
    push_back(tmp);
    value._movedListObj();
}


template<typename T>
void List<T>::pop_back()
{
    if (_size == 1) {
        delete _begin;
        _begin = nullptr;
        _end = nullptr;
    }

    else {
        delete _end->prev;
        _end->prev = _end->prev->prev;
        _end->prev->next = _end;
    }

    --_size;
}

template<typename T>
void List<T>::push_front(const T &value)
{
    Block *tmp = new Block(value);

    if (!_begin) {
        _begin = tmp;
        _end->prev = _begin;
        _begin->next = _end;
    }

    else {
        tmp->next = _begin;
        _begin->prev = tmp;
        _begin = tmp;

    }

    ++_size;
}

template<typename T>
void List<T>::pop_front()
{
    _begin = _begin->next;
    delete _begin->prev;
    _begin->prev = nullptr;
    --_size;
}

template<typename T>
void List<T>::reverse()
{
    const int count = _size / 2;
    auto iter_begin = begin();
    auto iter_end = --end();

    for (int i = 0; i < count; ++i, ++iter_begin, --iter_end)
        std::swap(iter_begin.data(), iter_end.data());

}

template<typename T>
void List<T>::clear()
{
    erase(begin(), end());
}

template<typename T>
void List<T>::erase(List::Iterator iter)
{
    if (iter.currBlock == _begin)
        pop_front();

    else if (iter.currBlock == _end)
        pop_back();

    else {
        iter.currBlock->prev->next = iter.currBlock->next;
        iter.currBlock->next->prev = iter.currBlock->prev;

        Block *prev = iter.currBlock->prev;
        delete iter.currBlock;
        iter.currBlock = prev;

        --_size;
    }
}

template<typename T>
void List<T>::erase(Iterator iter_begin, Iterator iter_end)
{
    while (iter_begin != iter_end) {
        List<T>::Iterator titer = iter_begin;
        ++iter_begin;
        erase(titer);
    }
}

template<typename T>
void List<T>::remove(const T &compare)
{
    for (List<T>::Iterator iter = begin(); iter != end(); ) {
        if (compare == iter.data()){
            List<T>::Iterator titer = iter;
            ++iter;
            erase(titer);
        }
        else ++iter;
    }
}

template<typename T>
void List<T>::remove_if(const std::function<bool (const T &obj)> call_comp)
{
    for (List<T>::Iterator iter = begin(); iter != end(); ) {
        if (call_comp(iter.data())){
            List<T>::Iterator titer = iter;
            ++iter;
            erase(titer);
        }
        else ++iter;
    }
}

template<typename T>
void List<T>::insert(List::Iterator iter, const T &obj)
{
    if (iter.currBlock == _end)
        push_back(obj);

    else {
        Block *ins = new Block(obj);

        ins->next = iter.currBlock->next;
        ins->prev = iter.currBlock;
        iter.currBlock->next->prev = ins;
        iter.currBlock->next = ins;
    }
}

template<typename T>
void List<T>::_movedListObj()
{
    _size = 0;
    _end = 0;
}

template<typename T>
T &List<T>::front()
{
    return _begin->data;
}

template<typename T>
T &List<T>::back()
{
    return _end->prev->data;
}
