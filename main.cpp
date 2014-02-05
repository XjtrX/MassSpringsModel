#include <QApplication>
//#include <QtGui/QApplication>
#include "SceneWindow.h"
#include <GL/glut.h>

#include <iostream>
using namespace std;

#include "vec.h"
#include "rootparitycollisiontest.h"

#include <QDebug>


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    SceneWindow sW;
    sW.show();


     bool result =false;

     {
         //test vertex-triangle
         Vec3d verts_old[4]={Vec3d(-2,0,1.0000001),Vec3d(0,0,1),Vec3d(-1,0,-1),Vec3d(1,0,-1)};
         Vec3d verts_new[4]={Vec3d(2.1,0,0.999999),Vec3d(0,0,1),Vec3d(-1,0,-1),Vec3d(1,0,-1)};

         bool is_edge_edge = false;

         rootparity::RootParityCollisionTest test(
             verts_old[0],verts_old[1],verts_old[2],verts_old[3],
             verts_new[0],verts_new[1],verts_new[2],verts_new[3],is_edge_edge);

         result = test.run_test();
         qDebug() << result;
     }

     {
         //test edge-edge
         Vec3d verts_old[4]={Vec3d(-1,0,0),Vec3d(1,0,0),Vec3d(0,1,-1),Vec3d(0,1,1)};
         Vec3d verts_new[4]={Vec3d(-1,0,0),Vec3d(1,0,0),Vec3d(0,0,-1),Vec3d(0,0,1)};

         bool is_edge_edge = true;

         rootparity::RootParityCollisionTest test(
             verts_old[0],verts_old[1],verts_old[2],verts_old[3],
             verts_new[0],verts_new[1],verts_new[2],verts_new[3],is_edge_edge);

         result = test.run_test();
         qDebug() << result;
     }







    return a.exec();
}
