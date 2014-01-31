#ifndef RUNGEKUTTAOBJECT_H
#define RUNGEKUTTAOBJECT_H

class RungeKuttaObject
{
    virtual void ComputeK1() = 0;
    virtual void ComputeK2() = 0;
    virtual void ComputeK3() = 0;
    virtual void ComputeK4() = 0;
};

#endif // RUNGEKUTTAOBJECT_H
