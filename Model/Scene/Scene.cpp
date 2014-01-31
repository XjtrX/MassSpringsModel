#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        VerletSpringsObject* sO = _springsObjects.at(i);
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

    l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Draw();
    }

    /*
    glBegin(GL_LINES);
    l = _springs.size();
    for (int i = 0; i < l; i++)
    {
        _springs.at(i)->Draw();
    }
    glEnd();
    */
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
}

void Scene::ApplyAcceleration(const float &fX, const float &fY, const float &fZ)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->ApplyAcceleration(fX, fY, fZ);
    }
}

void Scene::Accelerate(const float &timeStep)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Accelerate(timeStep);
    }
}

void Scene::Move()
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Move();
    }
}

void Scene::Collide(int flag)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        VerletParticle* p1 = (VerletParticle*)_particles.at(i);
        for (int j = i + 1; j < l; j++)
        {
            VerletParticle* p2 = (VerletParticle*)_particles.at(j);

            Point3D<float> dist = p1->getPosition();
            dist -= p2->getPosition();

            float sLength = dist.getSquaredLength();
            float length = sqrt(sLength);

            float target = p1->getBorderRadius() + p2->getBorderRadius();

            if (length < target)
            {
                float factor = (length - target) / length;

                if (!p1->isStatic())
                {
                p1->getPosition().MinusCorresp(dist, factor / 2);
                }
                if (!p2->isStatic())
                {
                    p2->getPosition().PlusCorresp(dist, factor / 2);
                }
                if (flag)
                {
                    Point3D<float> v1 = p1->getPosition();
                    v1 -= p1->PrevPosition();

                    Point3D<float> v2 = p2->getPosition();
                    v2 -= p2->PrevPosition();

                    float f1 = (0.05 * (   dist.getX() * v1.getX()
                                         + dist.getY() * v1.getY()
                                         + dist.getZ() * v1.getZ())
                                / sLength);
                    float f2 = (0.05 * (   dist.getX() * v2.getX()
                                         + dist.getY() * v2.getY()
                                         + dist.getZ() * v2.getZ())
                                / sLength);

                    v1.PlusCorresp(p1->getPosition(), f2);
                    v1.MinusCorresp(p1->getPosition(), f1);

                    v2.PlusCorresp(p1->getPosition(), f1);
                    v2.MinusCorresp(p1->getPosition(), f2);

                    if (!p1->isStatic())
                    {
                        p1->PrevPosition() = p1->getPosition();
                        p1->PrevPosition().MinusCorresp(v1, 1);
                    }

                    if (!p2->isStatic())
                    {
                        p2->PrevPosition() = p2->getPosition();
                        p2->PrevPosition().MinusCorresp(v2, 1);
                    }
                }
            }
        }
    }
}

void Scene::AddSpringsObject(VerletSpringsObject *springsObject)
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

void Scene::AddVerletParticle(VerletParticle *particle)
{
    _particles.push_back(particle);
    _freeParticles.push_back(particle);
}
