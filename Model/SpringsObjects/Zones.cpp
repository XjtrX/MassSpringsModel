#include "SpringsObject.h"

void SpringsObject::FlushZones()
{
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        _clothTriangles[i]->_zoneNum = -1;
    }
}

void SpringsObject::MergingToZones()
{
    this->FlushZones();
    for (int i = 0; i < _clothTrianglesCount; i++)
    {
        for (int j = 0; j < _clothTrianglesCount; j++)
        {
            if (j == i)
            {
                continue;
            }
            int testRes = CheckProximity(_clothTriangles[i], _clothTriangles[j]);
            if (1 == testRes)
            {
                MergeTriangles(_clothTriangles[i], _clothTriangles[j]);
            }
        }
    }
}

void SpringsObject::MergeTriangles(ClothTriangle *a, ClothTriangle *b)
{
    if (a->_zoneNum != -1 && a->_zoneNum == b->_zoneNum)
    {
        return;
    }
    if (-1 == a->_zoneNum && -1 == b->_zoneNum)
    {
        int zoneNum = _impactZones.size();
        a->_zoneNum = zoneNum;
        a->_zoneNum = zoneNum;
        _impactZones.push_back(vector<ClothTriangle*>());
        _impactZones.back().push_back(a);
        _impactZones.back().push_back(b);
        return;
    }
    if (-1 != a->_zoneNum && -1 == b->_zoneNum)
    {
        int zoneNum = a->_zoneNum;
        b->_zoneNum = zoneNum;
        _impactZones[zoneNum].push_back(b);
        return;
    }
    if (-1 == a->_zoneNum && -1 != b->_zoneNum)
    {
        int zoneNum = b->_zoneNum;
        a->_zoneNum = zoneNum;
        _impactZones[zoneNum].push_back(a);
        return;
    }
    MergeZones(a->_zoneNum, b->_zoneNum);
}

void SpringsObject::MergeZones(int a, int b)
{
    if (    a == b
        || -1 == a || -1 == b
        || (int)_impactZones.size() <= a
        || (int)_impactZones.size() <= b)
    {
        return;
    }
    if (a > b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (vector<ClothTriangle*>::iterator it = _impactZones[b].begin(); it != _impactZones[b].end(); ++it)
    {
        (*it)->_zoneNum = a;
    }
    _impactZones[a].insert(_impactZones[a].end(), _impactZones[b].begin(), _impactZones[b].end());

    _impactZones.erase(_impactZones.begin() + b);
}

void SpringsObject::CombineZones()
{
    for (uint i = 0; i < _impactZones.size(); i++)
    {
        int res = 0;
        for (uint j = i + 1; j < _impactZones.size(); j++)
        {
            for (vector<ClothTriangle*>::iterator a = _impactZones.at(i).begin(); a != _impactZones.at(i).end(); ++a)
            {
                for (vector<ClothTriangle*>::iterator b = _impactZones.at(j).begin(); b != _impactZones.at(j).end(); ++b)
                {
                    if ((*a)->isNeighbour(**b))
                    {
                        this->MergeZones(i, j);
                        res = 1;
                        break;
                    }
                }
                if (res)
                {
                    break;
                }
            }
            if (res)
            {
                break;
            }
        }
    }
}

void SpringsObject::ResolveImpactZones(const float &timestep)
{
    vector<vector<ClothTriangle*> >::iterator it;
    for (it = _impactZones.begin(); it != _impactZones.end(); ++it)
    {
        PointsManifold pM(*it);
        pM.ComputeAngularMomentum();
        pM.RecalculatePoinsState(timestep);
        it->erase(it->begin(), it->end());
    }
    _impactZones.erase(_impactZones.begin(), _impactZones.end());
}

void SpringsObject::EraseImpactZones()
{    vector<vector<ClothTriangle*> >::iterator it;
     for (it = _impactZones.begin(); it != _impactZones.end(); ++it)
     {
         it->erase(it->begin(), it->end());
     }
     _impactZones.erase(_impactZones.begin(), _impactZones.end());
}
