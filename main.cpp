#include <QApplication>
//#include <QtGui/QApplication>
#include "scenewindow.h"
#include <GL/glut.h>

#include "Point3D.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();

    return a.exec();
}
