#include "PointTriangleMainfold.h"

#include <math.h>

PointTriangleMainfold::PointTriangleMainfold(Particle *p, ClothTriangle *t)
{
    _p = p;
    _t = t;
}

PointTriangleMainfold::~PointTriangleMainfold()
{
}

void PointTriangleMainfold::ResolveCollision()
{
    Point3D<float>& A = _t->_p[0]->_position._position;
    Point3D<float>& B = _t->_p[1]->_position._position;
    Point3D<float>& C = _t->_p[2]->_position._position;
    Point3D<float>& D = _p->_position._position;

//    A.Print("A");
//    B.Print("B");
//    C.Print("C");
//    D.Print("D");
    Point3D<float> AB = B;
    AB -= A;
//    AB.Print("AB");
    Point3D<float> AC = C;
    AC -= A;
//    AC.Print("AC");

    Point3D<float> normalP;
    normalP = normalP.CrossProduct(AB, AC);

//    normalP.Print("normalP");

    float planeDCoeff = -normalP.DotProduct(A);
//    cout << "palneDCoeff " << planeDCoeff << endl;

    Point3D<float> col1(normalP._y, normalP._z, normalP._x);
    Point3D<float> col2(normalP._x, 0         , normalP._y);
    Point3D<float> col3(0         , normalP._x, normalP._z);

    Point3D<float> colRes(  normalP._y * D._x - normalP._x * D._y
                          , normalP._z * D._x - normalP._x * D._z
                          , planeDCoeff);

//    col1.Print("col1");
//    col2.Print("col2");
//    col3.Print("col3");
//    colRes.Print("colRes");

    Point3D<float> projection(0, 0, 0);

    float dA = AB.Determinant(col1, col2, col3);
//    cout << "da " << dA << endl;
    if (0 != dA)
    {
        float d1 = AB.Determinant(colRes, col2  , col3  );
        float d2 = AB.Determinant(col1  , colRes, col3  );
        float d3 = AB.Determinant(col1  , col2  , colRes);
        projection.set(d1 / dA, d2 / dA, d3 /dA);
    }
    Point3D<float> bCPr = projection.BarycentricCoordinates(A, B, C);
    bCPr.Print("barycentricProjection");
    Point3D<float> disp = D;
    disp -= projection;

    disp.Print("disp");

    float coeff = -0.005;

    disp *= coeff;

    _p->ApplyForce(disp._x, disp._y, disp._z);
//    return;
    disp *= -1;
    _t->_p[0]->ApplyForce(disp._x * bCPr._x, disp._y * bCPr._x, disp._z * bCPr._x);
    _t->_p[1]->ApplyForce(disp._x * bCPr._y, disp._y * bCPr._y, disp._z * bCPr._y);
    _t->_p[2]->ApplyForce(disp._x * bCPr._z, disp._y * bCPr._z, disp._z * bCPr._z);
}
