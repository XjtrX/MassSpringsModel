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
}

void Scene::Draw()
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Draw();
    }

    l = _triangleObstacles.size();
    for (int i = 0; i < l; i++)
    {
        _triangleObstacles.at(i)->Draw();
    }

    l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Draw();
    }
}

void Scene::RecalculateSprings()
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->RecalculateSprings();
    }
}

void Scene::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->ApplyForce(fX, fY, fZ);
    }
}

void Scene::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->ApplyAcceleration(fX, fY, fZ);
    }
}

void Scene::Accelerate(float timeStep)
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Accelerate(timeStep);
    }
}

void Scene::Move()
{
     int l = _springsObjects.size();
     for (int i = 0; i < l; i++)
     {
         _springsObjects.at(i)->Move();
     }
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
