#include "SpringsObject.h"

#include <math.h>
using namespace std;

#include "exact-ccd/vec.h"
#include "exact-ccd/rootparitycollisiontest.h"

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
    return;
    for (int i = 0; i < _particlesCount; i++)
    {
        delete _particles[i];
    }
    for (int i = 0; i < _springsCount; i++)
    {
        delete _springs[i];
    }
}

SpringsObject::SpringsObject(const int &particlesCount, const int &springsCount, const int &structuralSpringsCount, const int &clothTrianglesCount, const float &thickness)
{
    _particlesCount = particlesCount;
    _particles = vector<Particle*>(particlesCount);
    _springsCount = springsCount;
    _springs = vector<Spring*>(springsCount);
    _structuralSpringsCount = structuralSpringsCount;
    _structuralSprings = vector<Spring*>(structuralSpringsCount);
    _clothTrianglesCount = clothTrianglesCount;
    _clothTriangles = vector<ClothTriangle*>(clothTrianglesCount);

    _thickness = thickness;
}

void SpringsObject::Draw(const DrawType &type)
{
//    glBegin(GL_TRIANGLES);
    glBegin(GL_LINES);
    for (int i = 0; i < this->_clothTrianglesCount; i++)
    {
        this->_clothTriangles[i]->Draw(type);
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

void SpringsObject::Accelerate(const float &timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Accelerate(timestep);
    }
}

void SpringsObject::CalculateAverageVelocity(const float &timestep)
{
    return;
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->CalculateAverageVelocity(timestep);
    }
}

void SpringsObject::Move(const float &timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->Move(timestep);
    }
}

void SpringsObject::setVelocity(const Point3D<float> &newVelocity, const float &timestep)
{
    for (int i = 0; i < _particlesCount; i++)
    {
        _particles[i]->setVelocity(newVelocity, timestep);
    }
}

Point3D<float> SpringsObject::getVelocity()
{
    //unresolved
    return Point3D<float>(0, 0, 0);
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

    if (distance(&(a->_particleA->_state._position), &(b->_particleA->_state._position)) > 3)
    {
        return 0;
    }

    Point3D<float>& aAP = a->_particleA->_prevState._position;
    Point3D<float>& aAC = a->_particleA->_state._position;
    Point3D<float>& aBP = a->_particleB->_prevState._position;
    Point3D<float>& aBC = a->_particleB->_state._position;

    Point3D<float>& bAP = b->_particleA->_prevState._position;
    Point3D<float>& bAC = b->_particleA->_state._position;
    Point3D<float>& bBP = b->_particleB->_prevState._position;
    Point3D<float>& bBC = b->_particleB->_state._position;


    Vec3d verts_old[4]={Vec3d(aAP._x,aAP._y,aAP._z),Vec3d(aBP._x,aBP._y,aBP._z),Vec3d(bAP._x,bAP._y,bAP._z),Vec3d(bBP._x,bBP._y,bBP._z)};
    Vec3d verts_new[4]={Vec3d(aAC._x,aAC._y,aAC._z),Vec3d(aBC._x,aBC._y,aBC._z),Vec3d(bAC._x,bAC._y,bAC._z),Vec3d(bBC._x,bBC._y,bBC._z)};

    bool is_edge_edge = true;

    rootparity::RootParityCollisionTest test(
        verts_old[0],verts_old[1],verts_old[2],verts_old[3],
        verts_new[0],verts_new[1],verts_new[2],verts_new[3],is_edge_edge);

    int result = test.run_test();

    return result;
}

/*
void Print(const Vec3d& v, char* desc)
{
    cout << desc << v[0] << ", " << v[1] << ", " << v[2] << endl;
}
*/

#include <iostream>
using namespace std;

int SpringsObject::TestTriangles(ClothTriangle* a, ClothTriangle* b)
{
    if (a->isNeighbour(*b))
    {
        return 0;
    }

    Point3D<float>& b0P = b->_p[0]->_prevState._position;
    Point3D<float>& b1P = b->_p[1]->_prevState._position;
    Point3D<float>& b2P = b->_p[2]->_prevState._position;

    Point3D<float>& b0C = b->_p[0]->_state._position;
    Point3D<float>& b1C = b->_p[1]->_state._position;
    Point3D<float>& b2C = b->_p[2]->_state._position;


    Vec3d vb0P(b0P._x, b0P._y, b0P._z);
    Vec3d vb1P(b1P._x, b1P._y, b1P._z);
    Vec3d vb2P(b2P._x, b2P._y, b2P._z);

    Vec3d vb0C(b0C._x, b0C._y, b0C._z);
    Vec3d vb1C(b1C._x, b1C._y, b1C._z);
    Vec3d vb2C(b2C._x, b2C._y, b2C._z);

    int result = 0;
//    int myRes = 0;
    bool is_edge_edge = false;
    for (int i = 0; i < 3; i++)
    {      
        Point3D<float>& aIP = a->_p[i]->_prevState._position;
        Point3D<float>& aIC = a->_p[i]->_state._position;

        Vec3d vaIP(aIP._x, aIP._y, aIP._z);
        Vec3d vaIC(aIC._x, aIC._y, aIC._z);

        rootparity::RootParityCollisionTest test(
            vaIP, vb0P, vb1P, vb2P,
            vaIC, vb0C, vb1C, vb2C, is_edge_edge);
        int testResult = test.run_test();
        if (testResult)
        {
            PointTriangleManifold* m = new PointTriangleManifold(a->_p[i], b);
            _manifolds.push_back(m);
            result = 1;
/*
            Print(vaIP, "prev\n");
            Print(vb0P, "");
            Print(vb1P, "");
            Print(vb2P, "");

            Print(vaIC, "curr\n");
            Print(vb0C, "");
            Print(vb1C, "");
            Print(vb2C, "");
*/
        }

        Point3D<float> prP = b->CalculatePrevProjection(aIP);
        Point3D<float> prC = b->CalculateProjection(aIC);

        Point3D<float> vecP = prP;
        vecP -= aIP;

        Point3D<float> vecC = prC;
        vecC -= aIC;

        float dPP = vecP.DotProduct(b->_prevNormal);
        float dPC = vecC.DotProduct(b->_normal);
        /*
        if (b->isInTriangle(prN))
        {
            cout << "isInTriangle 1" << endl;
        }
        */
        if (  /* b->isInPrevTriangle(prP)
            &&*/ b->isInTriangle(prC)
            && (vecC.getSquaredLength() <= (_thickness * _thickness))
            && (  ((dPP > 0) && (dPC < 0))
               || ((dPP < 0) && (dPC > 0)))
            )
        {
//            myRes = 1;
            if (!testResult)
            {
                cout << "error\n";
                PointTriangleManifold* m = new PointTriangleManifold(a->_p[i], b);
                _manifolds.push_back(m);
            }
            else
            {
                cout << "yeah\n";
            }
            cout.flush();
        }

    }
    return result;
}

int SpringsObject::MyTestTriangles(ClothTriangle *a, ClothTriangle *b)
{
    if (a->isNeighbour(*b))
    {
        return 0;
    }
/*
    Point3D<float>& b0P = b->_p[0]->_prevState._position;
    Point3D<float>& b1P = b->_p[1]->_prevState._position;
    Point3D<float>& b2P = b->_p[2]->_prevState._position;

    Point3D<float>& b0C = b->_p[0]->_state._position;
    Point3D<float>& b1C = b->_p[1]->_state._position;
    Point3D<float>& b2C = b->_p[2]->_state._position;
*/
    int result = 0;
    for (int i = 0; i < 3; i++)
    {
        Point3D<float>& aIP = a->_p[i]->_prevState._position;
        Point3D<float>& aIC = a->_p[i]->_state._position;


        Point3D<float> prP = b->CalculatePrevProjection(aIP);
        Point3D<float> prC = b->CalculateProjection(aIC);

        Point3D<float> vecP = prP;
        vecP -= aIP;

        Point3D<float> vecC = prC;
        vecC -= aIC;

        float dPP = vecP.DotProduct(b->_prevNormal);
        float dPC = vecC.DotProduct(b->_normal);
        if (  /* b->isInPrevTriangle(prP)
            &&*/ b->isInTriangle(prC)
            && (vecC.getSquaredLength() <= (_thickness * _thickness))
            && (  ((dPP > 0) && (dPC < 0))
               || ((dPP < 0) && (dPC > 0)))
            )
        {
            PointTriangleManifold* m = new PointTriangleManifold(a->_p[i], b);
            _manifolds.push_back(m);
            result = 1;
        }
    }
    return result;
}

void SpringsObject::Collide(const float &timestep)
{
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        ClothTriangle* a = _clothTriangles[i];
        a->RecalculatePlane();
        for (int j = 0; j < _clothTrianglesCount; j++)
        {
            if (i == j)
            {
                continue;
            }
            ClothTriangle* b = _clothTriangles[j];
            if (MyTestTriangles(a, b))
            {
                a->_highlighted = 1;
                b->_highlighted = 1;
                /*
                cout << i << " " << j << endl;
                cout << "triangle i " << i << endl;
                cout << "prev\n";
                a->_p[0]->_prevState._position._position.Print("");
                a->_p[1]->_prevState._position._position.Print("");
                a->_p[2]->_prevState._position._position.Print("");
                cout << "curr\n";
                a->_p[0]->_position._position.Print("");
                a->_p[1]->_position._position.Print("");
                a->_p[2]->_position._position.Print("");

                cout << "triangle j " << j << endl;
                cout << "prev\n";
                b->_p[0]->_prevState._position._position.Print("");
                b->_p[1]->_prevState._position._position.Print("");
                b->_p[2]->_prevState._position._position.Print("");
                cout << "curr\n";
                b->_p[0]->_position._position.Print("");
                b->_p[1]->_position._position.Print("");
                b->_p[2]->_position._position.Print("");

                cout << "check b a " << TestTriangles(b, a) << endl;
                */
            }
        }
    }
    this->ResolveCollisions(timestep);
}

void SpringsObject::FlushHighlighting()
{
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        _clothTriangles[i]->_highlighted = 0;
    }
}

void SpringsObject::ResolveSelfCollision(const float &timestep)
{
    //1. select a collision timestep size
    //2. advance to candidate position position and veloities an time t(n+1) with the cloth internal dynamics
    //3. compute the average velocity
//    this->SpringsObject::CalculateAverageVelocity(timestep);
    //4. check for priximity, then apply repulsion impulses and friction to the average velocity to get approximate velocity
    this->Collide(timestep);
    //5. check linear trajectories for collusion
    //6. compute the final position
    this->ResolveCollisions(timestep);
    //7.
}


void SpringsObject::ResolveCollisions(const float& timestep)
{
    if (_manifolds.empty())
    {
        return;
    }
    while(!_manifolds.empty())
    {
        _manifolds.back()->ResolveCollision(timestep);
        _manifolds.pop_back();
    }
}
