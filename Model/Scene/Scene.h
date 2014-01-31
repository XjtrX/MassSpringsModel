#ifndef SCENE_H
#define SCENE_H

#include "Model/Interfaces/VerletObject.h"
#include "Model/SpringsObjects/VerletSpringsObject.h"
#include "Model/ModelSamples/TriangleObstacle.h"

#include "Model/ModelSamples/VerletParticle.h"

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
    void Accelerate(const float &timeStep);
    void Move();
    void Collide(int flag);

    void AddSpringsObject(VerletSpringsObject* springsObject);
    void AddTriangleObstacle(TriangleObstacle* triangleObstacle);
    void AddVerletParticle(VerletParticle* particle);
private:
    vector<Particle*> _particles;
    vector<Particle*> _freeParticles;
    vector<Spring*> _springs;
    vector<VerletSpringsObject*> _springsObjects;
    vector<TriangleObstacle*> _triangleObstacles;
};

#endif // SCENE_H
