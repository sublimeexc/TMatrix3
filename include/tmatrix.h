// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TMatrix_H__
#define __TMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be lower");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TVector(const TVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TVector(TVector&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
    }
    ~TVector()
    {
        delete[] pMem;
        pMem = nullptr;
    }
    TVector& operator=(const TVector& v)
    {
        if (this == &v)
            return *this;

        if (sz != v.sz)
        {
            T* p = new T[v.sz];
            delete[] pMem;  // Сначала удаляем старую память
            pMem = p;
            sz = v.sz;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);  // Копируем данные
        return *this;
    }

    TVector& operator=(TVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept
    {
        return sz;
    }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TVector& v) const noexcept
    {
        if (sz != v.sz) return 0;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i]) return 0;
        }
        return 1;
    }
    bool operator!=(const TVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TVector operator+(T val)
    {
        TVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + val;
        }
        return tmp;
    }
    TVector operator-(T val)
    {

        TVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - val;
        }
        return tmp;
    }
    TVector operator*(T val)
    {
        TVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // векторные операции
    TVector operator+(const TVector& v)
    {
        if (sz != v.sz)
            throw exception("");
        TVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }
    TVector operator-(const TVector& v)
    {
        if (sz != v.sz)
            throw exception("");
        TVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }
    T operator*(const TVector& v)
    {
        if (sz != v.sz)
            throw exception("");
        T tmp = 0;
        for (size_t i = 0; i < sz; i++)
        {
            tmp += pMem[i] * v.pMem[i];
        }
        return tmp;
    }

    friend void swap(TVector& lhs, TVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TMatrix : private TVector<TVector<T>>
{
    using TVector<TVector<T>>::pMem;
    using TVector<TVector<T>>::sz;
public:
    TMatrix(size_t s = 1) : TVector<TVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE)
            throw out_of_range("");
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TVector<T>(sz);
        }
    }

    TMatrix(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TVector requires non-nullptr arg");
        pMem = new TVector<T>[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TMatrix(const TMatrix& v)
    {
        if (sz != v.sz)
            sz = v.sz;
        pMem = new TVector<T>[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TMatrix(TMatrix&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
    }
    ~TMatrix()
    {
        delete[] pMem;
        pMem = nullptr;
    }
    using TVector<TVector<T>>::operator[];
    using TVector<TVector<T>>::size;

    friend void swap(TMatrix& lhs, TMatrix& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    TMatrix& operator=(const TMatrix& m)
    {
        if (this == &m)
            return *this;

        if (sz != m.sz)
        {
            TVector<T>* p = new TVector<T>[m.sz];
            delete[] pMem;  // Сначала удаляем старую память
            pMem = p;
            sz = m.sz;
        }
        std::copy(m.pMem, m.pMem + sz, pMem);  // Копируем данные
        return *this;
    }
    TMatrix& operator=(TMatrix&& m) noexcept
    {
        swap(*this, m);
        return *this;
    }

    // сравнение
    bool operator==(const TMatrix& m) const noexcept
    {
        return TVector<TVector<T>>::operator==(m);
    }
    bool operator!=(const TMatrix& m) const noexcept
    {
        return !(this == m);
    }
    // матрично-скалярные операции
    TMatrix operator*(const T& val)
    {
        TMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TVector<T> operator*(const TVector<T>& v)
    {
        if (sz != v.size())
            throw invalid_argument();

        TVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] * v;
        return res;
    }

    // матрично-матричные операции
    TMatrix operator+(const TMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Exception");
        TMatrix res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            res[i] = pMem[i] + m[i];
        }
        return res;
    }
    TMatrix operator-(const TMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Exception");
        TMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res[i] = pMem[i] - m[i];
        }
        return res;
    }
    TMatrix operator*(const TMatrix& m)
    {
        if (sz != m.sz) throw exception("Exception");
        TMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                for (size_t k = 0; k < sz; k++)
                {
                    res[i][j] += pMem[i][k]* m[k][j];
                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << endl; // требуется оператор>> для типа T
        return ostr;
    }
};

#endif
