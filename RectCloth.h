#ifndef RECTCLOTH_H
#define RECTCLOTH_H

#include "Particle.h"
#include "Spring.h"

class RectCloth
{
    friend void paintGL();
public:
    RectCloth(int cols, int rows, int width, int height);
    ~RectCloth();
    void Collide();
public:
    int _particlesCount;
    int _springsCount;
    Particle* _particles;
    Spring* _springs;
};

#endif // RECTCLOTH_H
