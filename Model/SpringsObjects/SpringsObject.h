#ifndef SPRINGSOBJECT_H
#define SPRINGSOBJECT_H

#include "Model/ModelSamples/Spring.h"

#include <vector>
using namespace std;

class SpringsObject
{
public:
    SpringsObject(int particlesCount, int springsCount);
    ~SpringsObject();
    void Draw();
//protected:
public:
    int _particlesCount;
    int _springsCount;
    vector<Particle> _particles;
    vector<Spring> _springs;
};

#endif // SPRINGSOBJECT_H
