#pragma once
#include <iostream>
#include "tvectoriter.h"
template<class T>
class TVector
{
protected:
    size_t sz;
    T* pMem;

public:
    TVector(size_t size = 1);
    TVector(T* arr, size_t s);
    TVector(const TVector& v);
    TVector(TVector&& v) noexcept;
    ~TVector();

    TVector& operator=(const TVector& v);
    TVector& operator=(TVector&& v) noexcept;

    size_t size() const noexcept;

    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;

    bool operator==(const TVector& v) const noexcept;
    bool operator!=(const TVector& v) const noexcept;

    TVector operator+(T val);
    TVector operator-(T val);
    TVector operator*(T val);

    TVector operator+(const TVector& v);
    TVector operator-(const TVector& v);
    T operator*(const TVector& v);

    friend void swap(TVector& lhs, TVector& rhs) noexcept;
    friend std::istream& operator>>(std::istream& istr, TVector& v);
    friend std::ostream& operator<<(std::ostream& ostr, const TVector& v);

    virtual TVectorIterator<T> begin();
    virtual TVectorIterator<T> end();
};

// Реализации методов с inline
template<class T>
inline TVector<T>::TVector(size_t size) : sz(size)
{
    if (sz == 0)
        throw std::out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw std::out_of_range("Vector size should be lower");
    pMem = new T[sz]();
}

template<class T>
inline TVector<T>::TVector(T* arr, size_t s) : sz(s)
{
    assert(arr != nullptr && "TVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
}

template<class T>
inline TVector<T>::TVector(const TVector& v)
{
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
}

template<class T>
inline TVector<T>::TVector(TVector&& v) noexcept
{
    pMem = nullptr;
    sz = 0;
    swap(*this, v);
}

template<class T>
inline TVector<T>::~TVector()
{
    delete[] pMem;
    pMem = nullptr;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(const TVector& v)
{
    if (this == &v)
        return *this;

    if (sz != v.sz)
    {
        T* p = new T[v.sz];
        delete[] pMem;
        pMem = p;
        sz = v.sz;
    }
    std::copy(v.pMem, v.pMem + sz, pMem);
    return *this;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(TVector&& v) noexcept
{
    swap(*this, v);
    return *this;
}

template<class T>
inline size_t TVector<T>::size() const noexcept
{
    return sz;
}

template<class T>
inline T& TVector<T>::operator[](size_t ind)
{
    if (ind < 0 || ind >= sz) throw std::out_of_range("");
    return pMem[ind];
}

template<class T>
inline const T& TVector<T>::operator[](size_t ind) const
{
    if (ind < 0 || ind >= sz) throw std::out_of_range("");
    return pMem[ind];
}

template<class T>
inline bool TVector<T>::operator==(const TVector& v) const noexcept
{
    if (sz != v.sz) return 0;
    for (size_t i = 0; i < sz; i++)
    {
        if (pMem[i] != v.pMem[i]) return 0;
    }
    return 1;
}

template<class T>
inline bool TVector<T>::operator!=(const TVector& v) const noexcept
{
    return !(*this == v);
}

template<class T>
inline TVector<T> TVector<T>::operator+(T val)
{
    TVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
        tmp.pMem[i] = pMem[i] + val;
    }
    return tmp;
}

template<class T>
inline TVector<T> TVector<T>::operator-(T val)
{
    TVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
        tmp.pMem[i] = pMem[i] - val;
    }
    return tmp;
}

template<class T>
inline TVector<T> TVector<T>::operator*(T val)
{
    TVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
        tmp.pMem[i] = pMem[i] * val;
    }
    return tmp;
}

template<class T>
inline TVector<T> TVector<T>::operator+(const TVector& v)
{
    if (sz != v.sz)
        throw std::exception("");
    TVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
        tmp.pMem[i] = pMem[i] + v.pMem[i];
    }
    return tmp;
}

template<class T>
inline TVector<T> TVector<T>::operator-(const TVector& v)
{
    if (sz != v.sz)
        throw std::exception("");
    TVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
    {
        tmp.pMem[i] = pMem[i] - v.pMem[i];
    }
    return tmp;
}

template<class T>
inline T TVector<T>::operator*(const TVector& v)
{
    if (sz != v.sz)
        throw std::exception("");
    T tmp = 0;
    for (size_t i = 0; i < sz; i++)
    {
        tmp += pMem[i] * v.pMem[i];
    }
    return tmp;
}

template<class T>
TVectorIterator<T> TVector<T>::begin()
{
    return TVectorIterator<T>(*this, 0);
}

template<class T>
TVectorIterator<T> TVector<T>::end()
{
    return TVectorIterator<T>(*this, 0);
}

template<class T>
inline void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept
{
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
}

template<class T>
inline std::istream& operator>>(std::istream& istr, TVector<T>& v)
{
    for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i];
    return istr;
}

template<class T>
inline std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v)
{
    for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << ' ';
    return ostr;
}