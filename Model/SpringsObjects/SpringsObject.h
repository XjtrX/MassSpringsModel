#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/Interfaces/DrawableObject.h"
#include "Model/ModelSamples/Spring.h"
#include "Model/ModelSamples/Particle.h"
#include "Model/Interfaces/MovableObject.h"
#include "Model/ModelSamples/ClothTriangle.h"
#include "Model/Collision/PointTriangleManifold.h"
#include "Model/Collision/PointsManifold.h"

#include <vector>
#include <list>
using namespace std;

class SpringsObject: public MovableObject, public DrawableObject
{
public:
    SpringsObject(const int& particlesCount, const int& springsCount, const int& structuralSpringsCount
                  , const int& clothTrianglesCount, const float& thickness);
    void ConnectParticles(const int &cols, const int &rows, const float &width, const float &height
                  , const float &stiffnes
                  , const int &withBendSprings);

//    RectRungeKuttaCloth(int cols, int rows, float width, float height
//              , float massVolume, float stiffnes, float thickness
//              , Point3D<float> rotation, Point3D<float> translation, const int &withBendSprings);


    virtual ~SpringsObject();

    virtual void Draw(const DrawType &type);

    virtual void Iteration(float timeInterval) = 0;

    virtual void RecalculateSprings();

    virtual void ApplyForce(const float &fX, const float &fY, const float &fZ);
    virtual void ApplyAcceleration(const float &aX, const float &aY, const float &aZ);
    virtual void Accelerate(const float &timestep);
    virtual void CalculateAverageVelocity(const float &timestep);
    virtual void Inertia(const float &timestep);

    virtual void setVelocity(const Point3D<float> &newVelocity, const float &timestep);
    virtual Point3D<float> getVelocity();

    virtual void ComputeFinalPosition(const float &timestep);
    virtual void ApplyCorrection(const float &timestep);

    virtual void Collide(const float &timestep);
    void FlushHighlighting();
    virtual void ResolveSelfCollision(const float& timestep);

    int TestTriangles(ClothTriangle* a, ClothTriangle* b);
    int MyTestTriangles(ClothTriangle* a, ClothTriangle* b);
    void ResolveCollisions(const float& timestep);
    int CheckProximity(ClothTriangle* a, ClothTriangle* b);

    void FlushZones();
    void MergingToZones();
    void MergeTriangles(ClothTriangle* a, ClothTriangle* b);
    void MergeZones(int a, int b);
    void CombineZones();

    void ResolveImpactZones(const float& timestep);
    void EraseImpactZones();

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

    list<PointTriangleManifold*> _ptManifolds;
    list<PointsManifold*> _tManifolds;
    vector<vector<ClothTriangle*> > _impactZones;
};

#endif // SPRINGSOBJECT_H
