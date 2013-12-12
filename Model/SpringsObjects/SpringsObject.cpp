#include "SpringsObject.h"

#include <GL/glut.h>

SpringsObject::SpringsObject(int particlesCount, int springsCount)
    : _particlesCount(particlesCount), _springsCount(springsCount)
    , _particles(particlesCount), _springs(springsCount)
{
}

SpringsObject::~SpringsObject()
{

}

void SpringsObject::Draw()
{
    glBegin(GL_LINES);

     for (int i = 0; i < this->_springsCount; i++)
     {
         Point3D<float> p = this->_springs[i].getParticleA()->getPosition();
         glVertex3f(p.getX(), p.getY(), p.getZ());
         p = this->_springs[i].getParticleB()->getPosition();
         glVertex3f(p.getX(), p.getY(), p.getZ());
     }

     glEnd();
}
