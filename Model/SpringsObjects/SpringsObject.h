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

    SpringsObject(int particlesCount, int springsCount, int structuralSpringsCount, int clothTrianglesCount);
    virtual ~SpringsObject();

    virtual void Draw();

    virtual void Iteration(float timeInterval) = 0;

    virtual void RecalculateSprings();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    virtual void Accelerate(const float &timeStep);
    virtual void Move();
    virtual void Collide(int flag);
    virtual void FlushHighlighting();

    int TestTriangles(ClothTriangle* a, ClothTriangle* b);
    void ResolveCollisions();

public:
    int _particlesCount;
    int _springsCount;
    int _structuralSpringsCount;
    int _clothTrianglesCount;
    vector<Particle*> _particles;
    vector<Spring*> _springs;
    vector<Spring*> _structuralSprings;
    vector<ClothTriangle*> _clothTriangles;

    list<PointTriangleManifold*> _manifolds;
};

#endif // SPRINGSOBJECT_H
