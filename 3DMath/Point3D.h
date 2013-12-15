#ifndef POINT3D_H
#define POINT3D_H

template<class A>
class Point3D
{
public:
    Point3D(A x = 0, A y = 0, A z = 0)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    Point3D(const Point3D& p)
    {
        this->_x = p._x;
        this->_y = p._y;
        this->_z = p._z;
    }

    ~Point3D()
    {

    }

    Point3D& operator=(const Point3D& other)
    {
        if (this != &other)
        {
            _x = other._x;
            _y = other._y;
            _z = other._z;
        }
        return *this;
    }

    Point3D& operator +=(const Point3D& other)
    {
        this->_x += other._x;
        this->_y += other._y;
        this->_z += other._z;

        return *this;
    }

    Point3D& operator -=(const Point3D& other)
    {
        this->_x -= other._x;
        this->_y -= other._y;
        this->_z -= other._z;

        return *this;
    }
/*
    Point3D& operator *(const float& f)
    {
        this->_x *= f;
        this->_y *= f;
        this->_z *= f;

        return *this;
    }

    Point3D& operator /(const float& f)
    {
        this->_x /= f;
        this->_y /= f;
        this->_z /= f;

        return *this;
    }
*/
    A getX()
    {
        return _x;
    }

    A getY()
    {
        return _y;
    }

    A getZ()
    {
        return _z;
    }

    void setX(A x)
    {
        _x = x;
    }

    void setY(A y)
    {
        _y = y;
    }

    void setZ(A z)
    {
        _z = z;
    }

    void set(A x, A y, A z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    void PlusX(const A& x)
    {
        _x += x;
    }

    void PlusY(const A& y)
    {
        _y += y;
    }

    void PlusZ(const A& z)
    {
        _z += z;
    }

public:
    A _x;
    A _y;
    A _z;
};

#endif // POINT3D_H