#ifndef CUBE_H
#define CUBE_H

#include <vector>
using namespace std;

#include "ModelSamples/Spring.h"
class Cube
{
public:
    Cube();
    ~Cube();
public:
    int _particlesCount;
    int _springsCount;
    vector<Particle> _particles;
    vector<Spring> _springs;
};

#endif // CUBE_H
