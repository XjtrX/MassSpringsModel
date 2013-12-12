#ifndef SCENE_H
#define SCENE_H

#include "Model/SpringsObjects/SpringsObject.h"

#include <vector>
using namespace std;

class Scene
{
public:
    Scene();
    ~Scene();
    void Draw();
public:
    vector<SpringsObject> _springsObjects;
};

#endif // SCENE_H
