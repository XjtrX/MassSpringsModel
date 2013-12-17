#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        SpringsObject* sO = _springsObjects.at(i);
        delete sO;
    }
    l = _triangleObstacles.size();
    for (int i = 0; i < l; i++)
    {
        TriangleObstacle* tO = _triangleObstacles.at(i);
        delete tO;
    }

    l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        Particle* p = _particles.at(i);
        delete p;
    }

    l = _springs.size();
    for (int i = 0; i < l; i++)
    {
        Spring* s = _springs.at(i);
        delete s;
    }
}

void Scene::Draw()
{
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Draw();
    }
    */
    int l = _triangleObstacles.size();
    for (int i = 0; i < l; i++)
    {
        _triangleObstacles.at(i)->Draw();
    }

    l = _freeParticles.size();
    for (int i = 0; i < l; i++)
    {
        _freeParticles.at(i)->Draw();
    }

    glBegin(GL_LINES);
    l = _springs.size();
    for (int i = 0; i < l; i++)
    {
        _springs.at(i)->Draw();
    }
    glEnd();
}

void Scene::RecalculateSprings()
{
    int l = _springs.size();
    for (int i = 0; i < l; i++)
    {
        _springs.at(i)->Recalculate();
    }
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->RecalculateSprings();
    }
    */
}

void Scene::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->ApplyForce(fX, fY, fZ);
    }
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->ApplyForce(fX, fY, fZ);
    }
    */
}

void Scene::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->ApplyAcceleration(fX, fY, fZ);
    }
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->ApplyAcceleration(fX, fY, fZ);
    }
    */
}

void Scene::Accelerate(const float &timeStep)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Accelerate(timeStep);
    }
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Accelerate(timeStep);
    }
    */
}

void Scene::Move()
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Move();
    }
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Move();
    }
    */
}

void Scene::Collusion()
{
    /*
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i).Collusion();
    }
    */
}

void Scene::AddSprongsObject(SpringsObject *springsObject)
{
    _springsObjects.push_back(springsObject);
    for (vector<Particle*>::iterator it = springsObject->_particles.begin();
         it != springsObject->_particles.end(); ++it)
    {
        _particles.push_back(*it);
    }

    for (vector<Spring*>::iterator it = springsObject->_springs.begin();
         it != springsObject->_springs.end(); ++it)
    {
        _springs.push_back(*it);
    }
}

void Scene::AddTriangleObstacle(TriangleObstacle *triangleObstacle)
{
    _triangleObstacles.push_back(triangleObstacle);
}

void Scene::AddParticle(Particle *particle)
{
    _particles.push_back(particle);
    _freeParticles.push_back(particle);
}
