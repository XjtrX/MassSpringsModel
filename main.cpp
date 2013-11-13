#include <QtGui/QApplication>
#include "scenewindow.h"
#include <GL/glut.h>

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();

    return a.exec();
}
