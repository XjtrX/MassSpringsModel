#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Spring.h"
#include "Model/ModelSamples/Unresolved/Particle.h"
#include "Model/Interfaces/MovableObject.h"
#include "Model/ModelSamples/ClothTriangle.h"
#include "Model/Collision/PointTriangleManifold.h"

#include <vector>
#include <list>
using namespace std;

class SpringsObject: public MovableObject, public DrawableObject
{
public:
    SpringsObject();

    SpringsObject(const int& particlesCount, const int& springsCount, const int& structuralSpringsCount, const int& clothTrianglesCount, const float& thickness);
    virtual ~SpringsObject();

    virtual void Draw(const DrawType &type);

    virtual void Iteration(float timeInterval) = 0;

    virtual void RecalculateSprings();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    virtual void Accelerate(const float &timestep);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Move(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();

    virtual void ComputeFinalPosition(const float &timestep);

    virtual void Collide(const float &timestep);
    void FlushHighlighting();
    virtual void ResolveSelfCollision(const float& timestep);

    int TestTriangles(ClothTriangle* a, ClothTriangle* b);
    int MyTestTriangles(ClothTriangle* a, ClothTriangle* b);
    void ResolveCollisions(const float& timestep);

public:
    int _particlesCount;
    int _springsCount;
    int _structuralSpringsCount;
    int _clothTrianglesCount;
    vector<Particle*> _particles;
    vector<Spring*> _springs;
    vector<Spring*> _structuralSprings;
    vector<ClothTriangle*> _clothTriangles;

    float _thickness;

    list<PointTriangleManifold*> _manifolds;
    list<list<ClothTriangle*> > _impactZones;
};

#endif // SPRINGSOBJECT_H
