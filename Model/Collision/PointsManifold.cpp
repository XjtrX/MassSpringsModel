#include "PointsManifold.h"

template <class ForwardIterator>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last)
{
  if (first==last) return last;

  ForwardIterator result = first;
  while (++first != last)
  {
    if (!(*result == *first))  // or: if (!pred(*result,*first)) for version (2)
      *(++result)=*first;
  }
  return ++result;
}

PointsManifold::PointsManifold(const vector<ClothTriangle *> &triangles)
    :_particles(triangles.size() * 3)
{
    int tLen = triangles.size();
    for (int i = 0; i < tLen; i++)
    {
        ClothTriangle* ct = triangles[i];
        for (int j = 0; j < 3; j++)
        {
            _particles[i * 3 + j] = ct->_p[j];
        }
    }
    vector<Particle*>::iterator it = unique(_particles.begin(), _particles.end());
    _particles.resize(distance(_particles.begin(), it));
}

PointsManifold::~PointsManifold()
{
}

void PointsManifold::ComputeAngularMomentum()
{
    _vCM.set(0, 0, 0);
    _xCM.set(0, 0, 0);
    float sumOfMAsses = 0;
    int pLen = _particles.size();
    for (int i = 0; i < pLen; i++)
    {
        Particle* p = _particles[i];
        float massVolume = p->_massVolume;
        _xCM = p->_prevState._position * massVolume;
        _vCM = p->_approximateVelocity * massVolume;
        sumOfMAsses += massVolume;
    }
    _xCM /= sumOfMAsses;
    _vCM /= sumOfMAsses;

    _L.set(0, 0, 0);
    _I.setZeros();
    for (int i = 0; i < pLen; i++)
    {
        Particle* p = _particles[i];
        _L += Point3D<float>::CrossProduct((p->_prevState._position - _xCM), (p->_approximateVelocity - _vCM)) * p->_massVolume;

        _I += (Matrix3x3D<float>::getDelta() * (p->_prevState._position - _xCM).getSquaredLength() - Matrix3x3D<float>::KroneckerProduct(p->_prevState._position - _xCM)) * p->_massVolume;
    }

    _omega = Matrix3x3D<float>::Mult(_I.getInverse(), _L);
}

void PointsManifold::RecalculatePoinsState(const float &timestep)
{
    int pLen  = _particles.size();
    float angle = timestep * _omega.getLength();
    for (int i = 0; i < pLen; i++)
    {
        Particle* p = _particles[i];
        Point3D<float> xF = p->_prevState._position - _xCM;
        Point3D<float> xR = p->_prevState._position - _xCM -xF;

        p->_state._position = _xCM + _vCM * timestep + xR * cos(angle) + Point3D<float>::CrossProduct(_omega.getUnit() * sin(angle), xR);
        p->_averageVelocity = (p->_state._position - p->_prevState._position) / timestep;
    }
}
