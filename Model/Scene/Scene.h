#ifndef SCENE_H
#define SCENE_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/SpringsObjects/SpringsObject.h"
#include "Model/ModelSamples/TriangleObstacle.h"

#include <vector>
using namespace std;

class Scene: public VerletObject
{
public:
    Scene();
    virtual ~Scene();
    void Draw();

    void RecalculateSprings();

    void ApplyForce(const float &fX, const float &fY, const float &fZ);
    void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    void Accelerate(float timeStep);
    void Move();
    void Collusion();
public:
    vector<SpringsObject*> _springsObjects;
    vector<TriangleObstacle*> _triangleObstacles;
    vector<Particle*> _particles;
};

#endif // SCENE_H
