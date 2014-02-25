#include "SpringsObject.h"

#include <math.h>
using namespace std;

#include "vec.h"
#include "rootparitycollisiontest.h"

#include "3DMath/ParticleState.h"

SpringsObject::SpringsObject()
{
}

SpringsObject::~SpringsObject()
{
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        delete _clothTriangles[i];
    }
    for (int i = 0; i < _particlesCount; i++)
    {
        delete _particles[i];
    }

    for (int i = 0; i < _springsCount; i++)
    {
        delete _springs[i];
    }
}

SpringsObject::SpringsObject(int particlesCount, int springsCount, int structuralSpringsCount, int clothTrianglesCount)
{
    _particlesCount = particlesCount;
    _particles = vector<Particle*>(particlesCount);
    _springsCount = springsCount;
    _springs = vector<Spring*>(springsCount);
    _structuralSpringsCount = structuralSpringsCount;
    _structuralSprings = vector<Spring*>(structuralSpringsCount);
    _clothTrianglesCount = clothTrianglesCount;
    _clothTriangles = vector<ClothTriangle*>(clothTrianglesCount);
}

void SpringsObject::Draw()
{
    glBegin(GL_LINES);
    for (int i = 0; i < this->_clothTrianglesCount; i++)
    {
        this->_clothTriangles[i]->Draw();
    }
    glEnd();
}

void SpringsObject::RecalculateSprings()
{
    for (int i = 0; i < _springsCount; i++)
    {
        _springs[i]->Recalculate();
    }
}

void SpringsObject::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->ApplyForce(fX, fY ,fZ);
    }
}

void SpringsObject::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->ApplyAcceleration(fX, fY ,fZ);
    }
}

void SpringsObject::Accelerate(const float &timeStep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Accelerate(timeStep);
    }
}

void SpringsObject::Move()
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Move();
    }
}

inline float distance(Point3D<float>* p1, Point3D<float>* p2)
{
    Point3D<float> dist = *p1;
    dist -= *p2;
    return sqrt(dist.getSquaredLength());
}

int TestSprings(Spring* a, Spring* b)
{
    if (a->getParticleA() == b->getParticleA()
            || a->getParticleA() == b->getParticleB()
            || a->getParticleB() == b->getParticleA()
            || a->getParticleB() == b->getParticleB())
    {
        return 0;
    }

    if (distance(&(a->_particleA->_position._position), &(b->_particleA->_position._position)) > 3)
    {
        return 0;
    }

    Point3D<float>& aAP = a->_particleA->_prevPosition._position;
    Point3D<float>& aAC = a->_particleA->_position._position;
    Point3D<float>& aBP = a->_particleB->_prevPosition._position;
    Point3D<float>& aBC = a->_particleB->_position._position;

    Point3D<float>& bAP = b->_particleA->_prevPosition._position;
    Point3D<float>& bAC = b->_particleA->_position._position;
    Point3D<float>& bBP = b->_particleB->_prevPosition._position;
    Point3D<float>& bBC = b->_particleB->_position._position;


    Vec3d verts_old[4]={Vec3d(aAP._x,aAP._y,aAP._z),Vec3d(aBP._x,aBP._y,aBP._z),Vec3d(bAP._x,bAP._y,bAP._z),Vec3d(bBP._x,bBP._y,bBP._z)};
    Vec3d verts_new[4]={Vec3d(aAC._x,aAC._y,aAC._z),Vec3d(aBC._x,aBC._y,aBC._z),Vec3d(bAC._x,bAC._y,bAC._z),Vec3d(bBC._x,bBC._y,bBC._z)};

    bool is_edge_edge = true;

    rootparity::RootParityCollisionTest test(
        verts_old[0],verts_old[1],verts_old[2],verts_old[3],
        verts_new[0],verts_new[1],verts_new[2],verts_new[3],is_edge_edge);

    int result = test.run_test();

    return result;
}

int SpringsObject::TestTriangles(ClothTriangle* a, ClothTriangle* b)
{
    if (a->isNeighbour(*b))
    {
        return 0;
    }

    Point3D<float>& b0P = b->_p[0]->_prevPosition._position;
    Point3D<float>& b1P = b->_p[1]->_prevPosition._position;
    Point3D<float>& b2P = b->_p[2]->_prevPosition._position;

    Point3D<float>& b0C = b->_p[0]->_position._position;
    Point3D<float>& b1C = b->_p[1]->_position._position;
    Point3D<float>& b2C = b->_p[2]->_position._position;


    Vec3d vb0P(b0P._x, b0P._y, b0P._z);
    Vec3d vb1P(b1P._x, b1P._y, b1P._z);
    Vec3d vb2P(b2P._x, b2P._y, b2P._z);

    Vec3d vb0C(b0C._x, b0C._y, b0C._z);
    Vec3d vb1C(b1C._x, b1C._y, b1C._z);
    Vec3d vb2C(b2C._x, b2C._y, b2C._z);

    int result = 0;
    bool is_edge_edge = false;
    for (int i = 0; i < 3; i++)
    {
        Point3D<float>& aIP = a->_p[i]->_prevPosition._position;
        Point3D<float>& aIC = a->_p[i]->_position._position;

        Vec3d vaIP(aIP._x, aIP._y, aIP._z);
        Vec3d vaIC(aIC._x, aIC._y, aIC._z);

        rootparity::RootParityCollisionTest test(
            vaIP, vb0P, vb1P, vb2P,
            vaIC, vb0C, vb1C, vb2C, is_edge_edge);
        int testResult = test.run_test();
        if (testResult)
        {
            PointTriangleMainfold* m = new PointTriangleMainfold(a->_p[i], b);
            _mainfolds.push_back(m);
            result = 1;
        }
    }
    return result;
}

void SpringsObject::Collide(int)
{
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        _clothTriangles[i]->_highlighted = 0;
    }
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        ClothTriangle* a = _clothTriangles[i];
        for (int j = 0; j < _clothTrianglesCount; j++)
        {
            ClothTriangle* b = _clothTriangles[j];
            if (TestTriangles(a, b))
            {
                a->_highlighted = 1;
                b->_highlighted = 1;
            }
        }
    }
    ResolveCollisions();
}


#include <iostream>
using namespace std;

void SpringsObject::ResolveCollisions()
{
    while(!_mainfolds.empty())
    {
        _mainfolds.back()->ResolveCollision();
        _mainfolds.pop_back();
    }
}
