#include "sceneglwidget.h"
#include <GL/glut.h>

#include <math.h>
using namespace std;
#define PI 3.14159265

SceneGLWidget::SceneGLWidget(QWidget *parent)
    : QGLWidget(parent)
    , _rectCloth(30, 30, 1, 1)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(UpdateScene()));
    _timer.start(200);

    _rectCloth._mass[0].setStatic(1);
    _rectCloth._mass[_rectCloth._mass.size() - 1].setStatic(1);
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
    for (uint i = 0; i < _rectCloth._sprigs.size(); i++)
    {
        Point3D<float> p = _rectCloth._sprigs[i].getMassA()->getPosition();
        glVertex3f(p.getX(), p.getY(), p.getZ());
        p = _rectCloth._sprigs[i].getMassB()->getPosition();
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
    gluLookAt(  _transition.getX()/10 + (5 * sin(_rotation.getY()*PI/180))
              , _transition.getY()/10 - (5 * cos(_rotation.getY()*PI/180) * sin(_rotation.getX()*PI/180))
              , _transition.getZ()/10 + (5 * cos(_rotation.getX()*PI/180) * cos(_rotation.getY()*PI/180))
              , _transition.getX()/10
              , _transition.getY()/10
              , _transition.getZ()/10
                , -sin(_rotation.getZ()*PI/180), cos(_rotation.getZ()*PI/180), 0);
}

void SceneGLWidget::UpdateScene()
{
    int sL = _rectCloth._sprigs.size();
    int mL = _rectCloth._mass.size();
    for (int i = 0; i < sL; i++)
    {
        _rectCloth._sprigs[i].Recalculate();
    }
    for (int i = 0; i < mL; i++)
    {
        _rectCloth._mass[i].ApplyForce(0, 0, -0.1);
        _rectCloth._mass[i].Move(0.0016);
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
