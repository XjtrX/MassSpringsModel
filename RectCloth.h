#ifndef RECTCLOTH_H
#define RECTCLOTH_H

#include "Mass.h"
#include "Spring.h"

#include <vector>
using namespace std;

class RectCloth
{
    friend void paintGL();
public:
    RectCloth(int col, int row, int width, int height);
    ~RectCloth();
public:
    vector<Mass> _mass;
    vector<Spring> _sprigs;
};

#endif // RECTCLOTH_H
