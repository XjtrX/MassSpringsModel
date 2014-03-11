#include "Scene.h"

#include <stdlib.h>

#include <fstream>
using namespace std;

Scene::Scene()
{
    _directory = "/home";
    _iteration = 0;
}

Scene::~Scene()
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        SpringsObject* sO = _springsObjects.at(i);
        delete sO;
    }
//    /*
//    l = _triangleObstacles.size();
//    for (int i = 0; i < l; i++)
//    {
//        TriangleObstacle* tO = _triangleObstacles.at(i);
//        delete tO;
//    }
//    */

//    l = _particles.size();
//    for (int i = 0; i < l; i++)
//    {
//        Particle* p = _particles.at(i);
//        delete p;
//    }

//    l = _springs.size();
//    for (int i = 0; i < l; i++)
//    {
//        Spring* s = _springs.at(i);
//        delete s;
//    }
}

void Scene::Draw(const DrawType &type)
{
    /*
    int l = _triangleObstacles.size();
    for (int i = 0; i < l; i++)
    {
        _triangleObstacles.at(i)->Draw();
    }
    */
    /*
    l = _freeParticles.size();
    for (int i = 0; i < l; i++)
    {
        _freeParticles.at(i)->Draw();
    }
    */

    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Draw(type);
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

void Scene::Iteration(float timeInterval)
{
    int l = _springsObjects.size();
    for (int i = 0; i < l; i++)
    {
        _springsObjects.at(i)->Iteration(timeInterval);
    }
    _iteration++;
}

/*
void Scene::RecalculateSprings()
{
    int l = _springs.size();
    for (int i = 0; i < l; i++)
    {
        _springs.at(i)->Recalculate();
    }

    //    int l = _springsObjects.size();
    //    for (int i = 0; i < l; i++)
    //    {
    //        _springsObjects.at(i)->RecalculateSprings();
    //    }
}

void Scene::ApplyForce(const float &fX, const float &fY, const float &fZ)
{
    int l = _particles.size();
    for (int i = 0ui->widget->; i < l; i++)
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

void Scene::Accelerate(const float &timestep)
{
    int l = _particles.size();
    for (int i = 0; i < l; i++)
    {
        _particles.at(i)->Accelerate(timestep);
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
*/

void Scene::AddSpringsObject(SpringsObject *springsObject)
{
    _springsObjects.push_back(springsObject);
    /*
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
    */
}

void Scene::Collide(const float &timestep)
{
    for (uint i = 0; i < _springsObjects.size(); i++)
    {
        _springsObjects.at(i)->Collide(timestep);
    }
}

void Scene::FlushHighlighting()
{
    for (uint i = 0; i < _springsObjects.size(); i++)
    {
        _springsObjects.at(i)->FlushHighlighting();
    }
}

string Scene::getDirectrory()
{
    return this->_directory;
}

void Scene::setDirectory(string directory)
{
    if ("" == directory)
    {
        this->_directory = "/home";
        return;
    }
    this->_directory = directory;
}

void Scene::WriteToFile()
{
    char buffer[10];

    ofstream myFile;
    sprintf(buffer, "%d", _iteration);
    myFile.open((_directory + "/" + buffer + ".springsobject").c_str());
    myFile << "Iteration " << _iteration << endl;
    myFile << "ParticlesCount " << _particlesCount << endl;
    myFile.close();
}

void Scene::ResolveSelfCollision(const float &timestep)
{
    for (uint i = 0; i < _springsObjects.size(); i++)
    {
        _springsObjects.at(i)->ResolveSelfCollision(timestep);
    }
}

/*
void Scene::AddTriangleObstacle(TriangleObstacle *triangleObstacle)
{
    _triangleObstacles.push_back(triangleObstacle);
}

void Scene::AddVerletParticle(VerletParticle *particle)
{
    _particles.push_back(particle);
    _freeParticles.push_back(particle);
}
*/
