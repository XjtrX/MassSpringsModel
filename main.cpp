#include <QApplication>
//#include <QtGui/QApplication>
#include "SceneWindow.h"
#include <GL/glut.h>

//#include "3DMath/Matrix3x3D.h"

int main(int argc, char* argv[])
{
//    Matrix3x3D<float> m(Point3D<float>(1, 7, 5), Point3D<float>(2, 5, 6), Point3D<float>(3, 4, 0));
//    try
//    {
//        Matrix3x3D<float> iM = m.getInverse();
//        iM.Print("inverse");

//        Matrix3x3D<float> b = m * iM;

//        b.Print("gdf");
//    }
//    catch (CustomException& cE)
//    {
//        cout << "exception has occured\n";
//        cout << cE.getMessage();
//    }
//    Matrix3x3D<float> m = Matrix3x3D<float>::Kronecker_Product(Point3D<float>(1, 2, 3), Point3D<float>(3, 4, 5));
//    m.Print("Kronecker_Product");
//    Matrix3x3D<float> m(Point3D<float>(1, 2, 3), Point3D<float>(4, 1234, 6), Point3D<float>(7, 8, 9));
//    Point3D<float> p(3, 5, 65);
//    Matrix3x3D<float>::Mult(m, p).Print("res");
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();
    return a.exec();
}
