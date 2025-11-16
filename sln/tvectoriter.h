#pragma once

template <class T>
class TVector;

template <class T>
class TVectorIterator
{
protected:
    TVector<T>& v;
    int index;

public:
    TVectorIterator(TVector<T>& v, int index_ = 0);
    T& operator*();
    TVectorIterator<T>& operator++();
    TVectorIterator<T>& operator++(int);
    bool operator!=(const TVectorIterator<T>& c);
};

template<class T>
inline TVectorIterator<T>::TVectorIterator(TVector<T>& v, int index_) : v(v), index(index_)
{
}

template<class T>
inline T& TVectorIterator<T>::operator*()
{
    return v[index];
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator++()
{
    index++;
    return *this;
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator++(int)
{
    TVectorIterator<T> temp = *this;
    ++index;
    return temp;
}

template<class T>
inline bool TVectorIterator<T>::operator!=(const TVectorIterator<T>& c)
{
    return index != c.index;
}