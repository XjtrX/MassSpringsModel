#include <QApplication>
//#include <QtGui/QApplication>
#include "SceneWindow.h"
#include <GL/glut.h>

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
