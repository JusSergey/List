#ifndef LIST_H
#define LIST_H

#include <functional>
#include <initializer_list>

template <typename T>
class List
{
public:

    struct Block {

        Block *next;    // следующий
        Block *prev;    // предыдущий
        Block *curr;
        T data;

        Block (const T &obj) :
            data(obj),
            next(nullptr),
            prev(nullptr),
            curr(this) {}

        Block () :
            next(nullptr),
            prev(nullptr) {}

    };

    struct Iterator {

        bool operator == (const Iterator  &iter) {
            return currBlock == iter.currBlock;
        }

        bool operator != (const Iterator  &iter) {
            return currBlock != iter.currBlock;
        }

        Block *currBlock;

        inline T &data() { return currBlock->data; }

        Iterator &operator ++ () {
            currBlock->next->prev = currBlock;
            currBlock = currBlock->next;
            return *this;
        }

        Iterator &operator -- () {
            currBlock = currBlock->prev;
            return *this;
        }

        Iterator(Block *_iter) : currBlock(_iter) {}
        Iterator(const Iterator &_iter) : currBlock(_iter.currBlock) {}

        void operator = (const Iterator &iter) {
            currBlock = iter.currBlock;
        }
        void operator = (Block *block) {
            currBlock = block;
        }
    };

    List(const std::initializer_list<T> &init_list);
    List();
   ~List();

public:
    inline bool operator <  (const List<T> &comp_list) { return this->_size <  comp_list._size; }
    inline bool operator >  (const List<T> &comp_list) { return this->_size >  comp_list._size; }
    inline bool operator <= (const List<T> &comp_list) { return this->_size <= comp_list._size; }
    inline bool operator >= (const List<T> &comp_list) { return this->_size >= comp_list._size; }
    bool operator == (const List<T> &comp_list);
    List<T> &operator = (const List<T> &src);

public:
    void push_back(const T &value);
    void push_back(T &&value);
    void pop_back();

    void push_front(const T &value);
    void pop_front();

    void reverse();
    void clear();
    void erase(Iterator iter);
    void erase(Iterator iter_begin, Iterator iter_end);
    void remove(const T &compare);
    void remove_if(const std::function<bool(const T &obj)> call_comp);
    void insert(Iterator iter, const T &obj);

    Iterator find(const T &value) {
        for (auto i = begin(); i != end(); ++i)
            if (i.data() == value)
                return i;

        return Iterator(nullptr);
    }

    Iterator find_if(const std::function<bool(const T &obj)> call_comp) {
        for (auto i = begin(); i != end(); ++i)
            if (call_comp(i.data()))
                return i;

        return Iterator(nullptr);
    }

    T &front();
    T &back();

    inline Iterator begin()  const { return Iterator(_begin); }
    inline Iterator end()    const { return Iterator(_end);   }
    inline Iterator rbegin() const { return Iterator(_end->prev);   }
    inline Iterator rend()   const { return Iterator(_begin->prev); }
    inline const Iterator cbegin()  const { return Iterator(_begin); }
    inline const Iterator cend()    const { return Iterator(_end);   }
    inline const Iterator crbegin() const { return Iterator(_end->prev);   }
    inline const Iterator crend()   const { return Iterator(_begin->prev); }
    inline size_t   size()   const { return _size; }
    inline bool     empty()  const { return!_size; }

public:
    typedef T ObjType;

private:
    Block *_begin;
    Block *_end;
    size_t _size;
    friend class List<List<T>>;

private:
    void _movedListObj();

};

#endif // LIST_H
