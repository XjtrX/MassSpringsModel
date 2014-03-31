#ifndef MATRIX3X3D_H
#define MATRIX3X3D_H

#include "3DMath/Point3D.h"
#include "CustomException.h"

#include <iostream>
using namespace std;

template <class A>
class Matrix3x3DContainer
{
public:
    A _a[3][3];

    A& _a11;
    A& _a12;
    A& _a13;

    A& _a21;
    A& _a22;
    A& _a23;

    A& _a31;
    A& _a32;
    A& _a33;

public:

    Matrix3x3DContainer()
        :_a11(_a[0][0])
        ,_a12(_a[0][1])
        ,_a13(_a[0][2])
        ,_a21(_a[1][0])
        ,_a22(_a[1][1])
        ,_a23(_a[1][2])
        ,_a31(_a[2][0])
        ,_a32(_a[2][1])
        ,_a33(_a[2][2])
    {

    }

    virtual ~Matrix3x3DContainer()
    {

    }

    void setZeros()
    {
        _a11 = 0;
        _a12 = 0;
        _a13 = 0;

        _a21 = 0;
        _a22 = 0;
        _a23 = 0;

        _a31 = 0;
        _a32 = 0;
        _a33 = 0;
    }

    void Print(const char* description)
    {
        cout << description << endl;
        for (int j = 0; j < 3; j++)
        {
            cout << _a[0][j] << " " << _a[1][j] << " " << _a[2][j] << endl;
        }
        cout << "--\n";
    }
};

template <class A>
class Matrix3x3D: public Matrix3x3DContainer<A>
{
public:
    Matrix3x3D()
    {
        this->setZeros();
    }

    virtual ~Matrix3x3D()
    {

    }

    static Matrix3x3D getDelta()
    {
        Matrix3x3D res;
        res.setZeros();
        res._a11 = 1;
        res._a22 = 1;
        res._a33 = 1;

        return res;
    }

    static Matrix3x3D getDelta(const Point3D<A>& p)
    {
        Matrix3x3D res;
        res.setZeros();
        res._a11 = p._x;
        res._a22 = p._y;
        res._a33 = p._z;

        return res;
    }

    Matrix3x3D(const Matrix3x3D& other)
    {
        this->_a11 = other._a11;
        this->_a12 = other._a12;
        this->_a13 = other._a13;

        this->_a21 = other._a21;
        this->_a22 = other._a22;
        this->_a23 = other._a23;

        this->_a31 = other._a31;
        this->_a32 = other._a32;
        this->_a33 = other._a33;
    }

    Matrix3x3D(const Point3D<A>& col1, const Point3D<A> &col2, const Point3D<A> &col3)
    {
        this->_a11 = col1._x;
        this->_a12 = col1._y;
        this->_a13 = col1._z;

        this->_a21 = col2._x;
        this->_a22 = col2._y;
        this->_a23 = col2._z;

        this->_a31 = col3._x;
        this->_a32 = col3._y;
        this->_a33 = col3._z;
    }

    A getDeterminant()
    {
        A res;
        res =     this->_a11 * (this->_a22 * this->_a33 - this->_a32 * this->_a23)
                - this->_a21 * (this->_a12 * this->_a33 - this->_a32 * this->_a13)
                + this->_a31 * (this->_a12 * this->_a23 - this->_a22 * this->_a13);
        return res;

    }

    A getMinor(const int& col, const int& row)
    {
        int col1 = (0 < col) ? 0 : 1;
        int col2 = (2 > col) ? 2 : 1;

        int row1 = (0 < row) ? 0 : 1;
        int row2 = (2 > row) ? 2 : 1;

        return   this->_a[col1][row1] * this->_a[col2][row2]
               - this->_a[col2][row1] * this->_a[col1][row2];

    }

    Matrix3x3D getTransposed()
    {
        Matrix3x3D res;
        res._a11 = this->_a11;
        res._a12 = this->_a21;
        res._a13 = this->_a31;

        res._a21 = this->_a12;
        res._a22 = this->_a22;
        res._a23 = this->_a32;

        res._a31 = this->_a13;
        res._a32 = this->_a23;
        res._a33 = this->_a33;

        return res;
    }

    Matrix3x3D getInverse()
    {
        Matrix3x3D res = *this;

        Matrix3x3D t = this->getTransposed();

        A det = this->getDeterminant();
        if (0 == det)
        {
            throw CustomException("determinant equal 0");
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                res._a[i][j] = t.getMinor(i, j) * (2 * ((i + j + 1) % 2) - 1);
            }
        }

//        A resDet = res.getDeterminant();
        A coeff = 1 / det;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                res._a[i][j] *= coeff;
            }
        }

        return res;
    }

    Matrix3x3D operator +(const Matrix3x3D& other)
    {
        Matrix3x3D res = *this;

        res._a11 += other._a11;
        res._a12 += other._a12;
        res._a13 += other._a13;

        res._a21 += other._a21;
        res._a22 += other._a22;
        res._a23 += other._a23;

        res._a31 += other._a31;
        res._a32 += other._a32;
        res._a33 += other._a33;

        return res;
    }

    Matrix3x3D operator +=(const Matrix3x3D& other)
    {
        this->_a11 += other._a11;
        this->_a12 += other._a12;
        this->_a13 += other._a13;

        this->_a21 += other._a21;
        this->_a22 += other._a22;
        this->_a23 += other._a23;

        this->_a31 += other._a31;
        this->_a32 += other._a32;
        this->_a33 += other._a33;

        return *this;
    }

    Matrix3x3D operator -(const Matrix3x3D& other)
    {
        Matrix3x3D res = *this;

        res._a11 -= other._a11;
        res._a12 -= other._a12;
        res._a13 -= other._a13;

        res._a21 -= other._a21;
        res._a22 -= other._a22;
        res._a23 -= other._a23;

        res._a31 -= other._a31;
        res._a32 -= other._a32;
        res._a33 -= other._a33;

        return res;
    }

    Matrix3x3D operator *(const float& n)
    {
        Matrix3x3D res = *this;

        res._a11 *= n;
        res._a12 *= n;
        res._a13 *= n;

        res._a21 *= n;
        res._a22 *= n;
        res._a23 *= n;

        res._a31 *= n;
        res._a32 *= n;
        res._a33 *= n;

        return res;
    }

    Matrix3x3D operator *(const Matrix3x3D& other)
    {
        Matrix3x3D res;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                A sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += this->_a[k][j] * other._a[i][k];
                }
                res._a[i][j] = sum;
            }
        }
        return res;
    }

    static Point3D<A> Mult(const Matrix3x3D& m, const Point3D<A>& p)
    {
        Point3D<A> res;
        A x = p._x;
        A y = p._y;
        A z = p._z;

        res._x = m._a11 * x + m._a12 * y + m._a13 * z;
        res._y = m._a21 * x + m._a22 * y + m._a23 * z;
        res._z = m._a31 * x + m._a32 * y + m._a33 * z;

        return res;
    }

    static Matrix3x3D KroneckerProduct(const Point3D<A>& p1)
    {
        Matrix3x3D res(p1, p1, p1);
        res._a11 *= p1._x;
        res._a12 *= p1._x;
        res._a13 *= p1._x;

        res._a21 *= p1._y;
        res._a22 *= p1._y;
        res._a23 *= p1._y;

        res._a31 *= p1._z;
        res._a32 *= p1._z;
        res._a33 *= p1._z;

        return res;
    }

    static Matrix3x3D KroneckerProduct(const Point3D<A>& p1, const Point3D<A>& p2)
    {
        Matrix3x3D res(p2, p2, p2);
        res._a11 *= p1._x;
        res._a12 *= p1._x;
        res._a13 *= p1._x;

        res._a21 *= p1._y;
        res._a22 *= p1._y;
        res._a23 *= p1._y;

        res._a31 *= p1._z;
        res._a32 *= p1._z;
        res._a33 *= p1._z;

        return res;
    }

    static Matrix3x3D InertiaTensor(const Point3D<A>& p, const float mass)
    {
        Matrix3x3D res;

        A x = p._x;
        A y = p._y;
        A z = p._z;

        res._a11 = (y * y + z * z) * mass;
        res._a12 = -1 * y * x * mass;
        res._a13 = -1 * z * x * mass;

//        res._a21 = -1 * x * y * mass;
        res._a21 = res._a12;
        res._a22 = (x * x + z * z) * mass;
        res._a23 = -1 * z * y * mass;

//        res._a31 = -1 * x * z * mass;
        res._a31 = res._a13;
//        res._a32 = -1 * y * z * mass;
        res._a32 = res._a23;
        res._a33 = (x * x + y * y) * mass;

        return res;
    }
};

#endif // MATRIX3X3D_H
