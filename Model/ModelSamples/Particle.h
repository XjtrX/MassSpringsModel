#ifndef PARTICLE_H
#define PARTICLE_H

#include <Point3D.h>
class Particle
{
public:
    Point3D<float> _prevPosition;
    Point3D<float> _position;
    Point3D<float> _appliedForce;
    //float _massVolume;
    int _static;

    Particle()
    {

    }

    Particle(Point3D<float> initialPosition, int st = 0)
    {
        _prevPosition = initialPosition;
        _position = initialPosition;
        _appliedForce.set(0, 0, 0);
        _static = st;
    }

    ~Particle()
    {

    }

    void Verlet()
    {
        if (_static)
        {
            _appliedForce.set(0, 0, 0);
            return;
        }

        Point3D<float> temp = _position;
        _position.Plus(_position);
        _position.Minus(_prevPosition);
        //_position.Plus(_appliedForce);
        _prevPosition = temp;
        //_appliedForce.set(0, 0, 0);
    }

    void Accelerate(float timeStep)
    {
        _position.PlusX(_appliedForce.getX() * timeStep * timeStep / 2);
        _position.PlusY(_appliedForce.getY() * timeStep * timeStep / 2);
        _position.PlusZ(_appliedForce.getZ() * timeStep * timeStep / 2);
        _appliedForce.set(0, 0, 0);
    }

    Point3D<float> getPrevPosition()
    {
        return _prevPosition;
    }

    Point3D<float> getPosition()
    {
        return _position;
    }

    void ApplyForce(const float& fX, const float& fY, const float& fZ)
    {
        _appliedForce.PlusX(fX);
        _appliedForce.PlusY(fY);
        _appliedForce.PlusZ(fZ);
    }

    int isStatic()
    {
        return _static;
    }

    void setStatic(int st)
    {
        _static = st;
    }
};

#endif // PARTICLE_H
