#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
using namespace std;
class Particle
{
public:
    QString _str;

    Particle()
    {

    }

    Particle(string str)
    {
        _str = str;
    }

    ~Particle()
    {

    }
};

#endif // PARTICLE_H
