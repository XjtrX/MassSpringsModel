#include "sceneglwidget.h"
#include <GL/glut.h>

#include <math.h>
using namespace std;
#define PI 3.14159265

SceneGLWidget::SceneGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void SceneGLWidget::initializeGL()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}
void SceneGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0.6, 0);
    glBegin(GL_QUADS);
        DrawRectangle(Point3D<float>(0, 0, 0), Point3D<float>(1, 0, 0)
                    , Point3D<float>(1, -1, 0.5), Point3D<float>(0, -1, 0.5));
        DrawRectangle(Point3D<float>(-1, 1, 0.5), Point3D<float>(0, 1, 0.5)
                    , Point3D<float>(0, 0, 0), Point3D<float>(-1, 0, 0));
    glEnd();
}

void SceneGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    UpdateViewPoint();
}

void SceneGLWidget::mousePressEvent(QMouseEvent *ev)
{
    this->_mousePosX = ev->x();
    this->_mousePosY = ev->y();
    emit MousePressSignal();
}

void SceneGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    this->_mousePosX = ev->x();
    this->_mousePosY = ev->y();
    emit MouseMoveSignal();
}

void SceneGLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    emit MouseReleaseSignal();
}

void SceneGLWidget::leaveEvent(QEvent *)
{
    emit LeaveSignal();
}

void SceneGLWidget::UpdateViewPoint()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  _transition.getX()/10 + (5 * sin(_rotation.getY()*PI/180))
              , _transition.getY()/10 - (5 * cos(_rotation.getY()*PI/180) * sin(_rotation.getX()*PI/180))
              , _transition.getZ()/10 + (5 * cos(_rotation.getX()*PI/180) * cos(_rotation.getY()*PI/180))
              , _transition.getX()/10
              , _transition.getY()/10
              , _transition.getZ()/10
                , -sin(_rotation.getZ()*PI/180), cos(_rotation.getZ()*PI/180), 0);
}

void SceneGLWidget::DrawRectangle(Point3D<float> a, Point3D<float> b
                                , Point3D<float> c, Point3D<float> d)
{
//front
    glVertex3f(a.getX(), a.getY(), a.getZ());
    glVertex3f(b.getX(), b.getY(), b.getZ());
    glVertex3f(c.getX(), c.getY(), c.getZ());
    glVertex3f(d.getX(), d.getY(), d.getZ());
/*
    glVertex3f(center.getX() + mainPoint.getX()/2, center.getY() + mainPoint.getY()/2, center.getZ() - mainPoint.getZ()/2);
    glVertex3f(center.getX() - mainPoint.getX()/2, center.getY() + mainPoint.getY()/2, center.getZ() - mainPoint.getZ()/2);
    glVertex3f(center.getX() - mainPoint.getX()/2, center.getY() - mainPoint.getY()/2, center.getZ() - mainPoint.getZ()/2);
    glVertex3f(center.getX() + mainPoint.getX()/2, center.getY() - mainPoint.getY()/2, center.getZ() - mainPoint.getZ()/2);
*/
// rd ld lu ru

}

int SceneGLWidget::mousePosX()
{
    return _mousePosX;
}

int SceneGLWidget::mousePosY()
{
    return _mousePosY;
}


void SceneGLWidget::Rotate(int x, int y, int z)
{
    _rotation.PlusX(x);
    _rotation.PlusY(y);
    _rotation.PlusZ(z);
    UpdateViewPoint();
    this->repaint();
}
