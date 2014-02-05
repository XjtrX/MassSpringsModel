#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

class MovableObject
{
public:
    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ) = 0;
    virtual void Move() = 0;
    virtual void Collide(int flag) = 0;
};

#endif // MOVABLEOBJECT_H
