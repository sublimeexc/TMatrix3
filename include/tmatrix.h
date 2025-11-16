// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TMatrix_H__
#define __TMatrix_H__

#include <iostream>
#include <tvector.h>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти

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
