#ifndef SCENE_H
#define SCENE_H

#include "Model/SpringsObjects/SpringsObject.h"

class Scene: public SpringsObject
{
public:
    Scene();
    virtual ~Scene();
    virtual void Draw(const DrawType &type);

    /*
    void RecalculateSprings();

    void ApplyForce(const float &fX, const float &fY, const float &fZ);
    void ApplyAcceleration(const float &fX, const float &fY, const float &fZ);
    void Accelerate(const float &timestep);
    void Move();
    void Collide(int flag);
    */
    void Iteration(float timeInterval);

    void AddSpringsObject(SpringsObject* springsObject);
    virtual void Collide(int flag);
    virtual void FlushHighlighting();
    //void AddTriangleObstacle(TriangleObstacle* triangleObstacle);
    //void AddVerletParticle(VerletParticle* particle);
private:
    vector<Particle*> _particles;
//    vector<Particle*> _freeParticles;
    vector<Spring*> _springs;
    vector<SpringsObject*> _springsObjects;
//    vector<TriangleObstacle*> _triangleObstacles;
};

#endif // SCENE_H
