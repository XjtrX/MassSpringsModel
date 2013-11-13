#include <QtGui/QApplication>
#include "scenewindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();

    return a.exec();
}
