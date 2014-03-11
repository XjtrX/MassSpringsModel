#include "RectRungeKuttaCloth.h"

#include "3DMath/MathRotation.h"
#include "Model/ModelSamples/RungeKuttaParticle.h"

void ConnectParticles(Particle* p1, Particle* p2, Spring* s)
{
    dynamic_cast<RungeKuttaParticle*>(p1)->AddConnection(s, p2);
    dynamic_cast<RungeKuttaParticle*>(p2)->AddConnection(s, p1);
}

RectRungeKuttaCloth::RectRungeKuttaCloth(int cols, int rows, float width, float height
                                         , float massVolume, float stiffnes
                                         , float thickness
                                         , Point3D<float> rotation
                                         , Point3D<float> translation
                                         , const int &withBendSprings)
    : RungeKuttaSpringsObject(cols * rows
                              , (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1)
                              + ((cols - 2) * rows + cols * (rows - 2)) * (withBendSprings == 1 ? 1 : 0)
                              , (cols - 1) * rows + cols * (rows - 1)
                              , (cols - 1) * (rows - 1) * 2, thickness)
{
    //_particlesCount = cols * rows;: SpringsObject(particlesCount, springsCount)
    //_springsCount = (cols - 1) * rows + cols * (rows - 1) + 2 * (cols - 1) * (rows - 1);
    //_particles = new particle[_particlesCount];
    //_springs = new Spring[_springsCount];

    float massOfParticle = massVolume / _particlesCount;

    float sW = 1.0 * width / (cols - 1);
//    float sMW = sW * 2;
    float sH = 1.0 * height / (rows - 1);
//    float sMH = sH * 2;
    MathRotation m;
    float* rotMatr = m.RotationMatrix(rotation.getX()
                                                 , rotation.getY()
                                                 , rotation.getZ());
    int structSpnNum = 0;

    int i = 0;

    int t = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            _particles[r * cols + c] = new RungeKuttaParticle(
                        ParticleState(
                            m.RotateAndTranslatePoint(
                                Point3D<float>(1.0 * width * c / cols, 1.0 * height * r / rows)
                                , rotMatr, translation), Point3D<float>(0, 0, 0))
                        , massOfParticle);
            if (c > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c - 1]
                        , _particles[r * cols + c]
                        , stiffnes, sW);

                ConnectParticles(_particles[r * cols + c - 1]
                        , _particles[r * cols + c]
                        , _springs[i - 1]);
                _structuralSprings[structSpnNum++] = _springs[i - 1];
            }
            if (r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c]
                        , stiffnes, sH);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c]
                        , _springs[i - 1]);
                _structuralSprings[structSpnNum++] = _springs[i - 1];
            }
            if (c > 0 && r > 0)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c - 1]
                        , stiffnes, 0, shear);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[(r - 1) * cols + c - 1]
                        , _springs[i - 1]);

                _springs[i++] = new Spring(_particles[r * cols + c - 1]
                        , _particles[(r - 1) * cols + c]
                        , stiffnes, 0, shear);

                ConnectParticles(_particles[r * cols + c - 1]
                        , _particles[(r - 1) * cols + c]
                        , _springs[i - 1]);
            }


            //---------------------triangleCloth
            if (c > 0 && r > 0)
            {
                _clothTriangles[t++] = new ClothTriangle(_particles[(r - 1) * cols + c - 1], _particles[(r - 1) * cols + c], _particles[r * cols + c]);
                _clothTriangles[t++] = new ClothTriangle(_particles[(r - 1) * cols + c - 1], _particles[r * cols + c - 1], _particles[r * cols + c]);
            }


            //---------------------------------------------------
            if (!withBendSprings)
            {
                continue;
            }

            if (c > 1)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[r * cols + c - 2]
                        , stiffnes / 4, sW * 2, bend);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[r * cols + c - 2]
                        , _springs[i - 1]);
            }
            if (r > 1)
            {
                _springs[i++] = new Spring(_particles[r * cols + c]
                        , _particles[(r - 2) * cols + c]
                        , stiffnes / 4, sH * 2, bend);

                ConnectParticles(_particles[r * cols + c]
                        , _particles[(r - 2) * cols + c]
                        , _springs[i - 1]);
            }

        }
    }
    delete[] rotMatr;
}

RectRungeKuttaCloth::~RectRungeKuttaCloth()
{
    for (int i = 0; i < _particlesCount; i++)
    {
        delete _particles[i];
    }
}
