#ifndef SCENE_H
#define SCENE_H

#include "Model/SpringsObjects/SpringsObject.h"

#include <string>

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
    virtual void Collide(const float &timestep);
    virtual void FlushHighlighting();
    //void AddTriangleObstacle(TriangleObstacle* triangleObstacle);
    //void AddVerletParticle(VerletParticle* particle);
//    void WriteToFile(const string* filename);
    string getDirectrory();
    void setDirectory(string directory);
    void WriteToFile();

    virtual void ResolveSelfCollision(const float &timestep);
private:
//    vector<Particle*> _particles;
//    vector<Particle*> _freeParticles;
//    vector<Spring*> _springs;
    vector<SpringsObject*> _springsObjects;
//    vector<TriangleObstacle*> _triangleObstacles;

    string _directory;
    int _iteration;
};

#endif // SCENE_H
