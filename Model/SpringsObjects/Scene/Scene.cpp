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
