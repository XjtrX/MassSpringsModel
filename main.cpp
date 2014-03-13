#include <QApplication>
//#include <QtGui/QApplication>
#include "SceneWindow.h"
#include <GL/glut.h>

#include "3DMath/Matrix3x3D.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    /*
    Matrix3x3D<float> m(Point3D<float>(1, 7, 5), Point3D<float>(2, 5, 6), Point3D<float>(3, 4, 0));
    try
    {
        Matrix3x3D<float> iM = m.getInverse();
        iM.Print("inverse");

        Matrix3x3D<float> b = m * iM;

        b.Print("gdf");
    }
    catch (CustomException& cE)
    {
        cout << "exception has occured\n";
        cout << cE.getMessage();
    }
    */
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();
    return a.exec();
}
