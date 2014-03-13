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
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();
    return a.exec();
}
