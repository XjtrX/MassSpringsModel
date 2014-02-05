#include "SpringsObject.h"

#include "vec.h"
#include "rootparitycollisiontest.h"

SpringsObject::SpringsObject()
{
}

SpringsObject::~SpringsObject()
{
}

SpringsObject::SpringsObject(int particlesCount, int springsCount, int structuralSpringsCount)
{
    _particlesCount = particlesCount;
    _particles = vector<Particle*>(particlesCount);
    _springsCount = springsCount;
    _springs = vector<Spring*>(springsCount);
    _structuralSpringsCount = structuralSpringsCount;
    _structuralSprings = vector<Spring*>(structuralSpringsCount);
}

void SpringsObject::Draw(const int& flushColor)
{
    glBegin(GL_LINES);

    for (int i = 0; i < this->_springsCount; i++)
    {
        this->_springs[i]->Draw(flushColor);
        /*
        Point3D<float> p = this->_springs[i]->getParticleA()->getPosition();
        glVertex3f(p.getX(), p.getY(), p.getZ());
        p = this->_springs[i]->getParticleB()->getPosition();
        glVertex3f(p.getX(), p.getY(), p.getZ());
        */
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

#include <math.h>
using namespace std;

inline float distance(Point3D<float>* p1, Point3D<float>* p2)
{
    Point3D<float> dist = *p1;
    dist -= *p2;
    return sqrt(dist.getSquaredLength());
}

int testSprings(Spring* a, Spring* b)
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

void SpringsObject::Collide(int)
{
    for (int i = 0; i < _structuralSpringsCount; i++)
    {
        Spring* a = _structuralSprings[i];
        for (int j = i + 1; j < _structuralSpringsCount; j++)
        {
            Spring* b = _structuralSprings[j];
            if (testSprings(a, b))
            {
                a->_highlighted = 1;
                b->_highlighted = 1;
            }
        }
    }
//    cout << "collide finished\n";
//    cout.flush();
}
