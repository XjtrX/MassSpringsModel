#include "sceneglwidget.h"
#include <GL/glut.h>

#include <math.h>
#include <iostream>
using namespace std;
#define PI 3.14159265

SceneGLWidget::SceneGLWidget(QWidget *parent)
    : QGLWidget(parent)
    , _rectCloth(30, 30, 30, 30)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(UpdateScene()));
    _timer.start(1000 / 24);

    _rectCloth._particles[870].setStatic(1);
    _rectCloth._particles[899].setStatic(1);
//    _rectCloth._particles[_rectCloth._mass.size() - 1].setStatic(1);
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
    glLineWidth(1.5);
    glBegin(GL_LINES);

    for (int i = 0; i < _rectCloth._springsCount; i++)
    {
        Point3D<float> p = _rectCloth._springs[i].getParticleA()->getPosition();
        glVertex3f(p.getX(), p.getY(), p.getZ());
        p = _rectCloth._springs[i].getParticleB()->getPosition();
        glVertex3f(p.getX(), p.getY(), p.getZ());
    }

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

void SceneGLWidget::mouseReleaseEvent(QMouseEvent *)
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
    gluLookAt(  _transition.getX()/100 + (50 * sin(_rotation.getY()*PI/180))
              , _transition.getY()/100 - (50 * cos(_rotation.getY()*PI/180) * sin(_rotation.getX()*PI/180))
              , _transition.getZ()/100 + (50 * cos(_rotation.getX()*PI/180) * cos(_rotation.getY()*PI/180))
              , _transition.getX()/100
              , _transition.getY()/100
              , _transition.getZ()/100
                , -sin(_rotation.getZ()*PI/180), cos(_rotation.getZ()*PI/180), 0);
}

void SceneGLWidget::UpdateScene()
{
    int sL = _rectCloth._springsCount;
    int mL = _rectCloth._particlesCount;
    for (int i = 0; i < sL; i++)
    {
        _rectCloth._springs[i].Recalculate();
    }
    for (int i = 0; i < mL; i++)
    {
        _rectCloth._particles[i].ApplyForce(0, -0.001, 0);
        _rectCloth._particles[i].Move(0.016);
    }

    this->repaint();
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
