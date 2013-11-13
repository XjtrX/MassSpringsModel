#include "sceneglwidget.h"
#include <GL/glut.h>

SceneGLWidget::SceneGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    _timer.start(16);
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

    glRotatef(0.5, 1, 1, 1);
    glColor3f(1, 0.6, 0);
    glutSolidTeapot(0.6);
    /*
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0, 1, 0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0, 0, 1);
        glVertex3f( 0.5,  0.5, 0);
    glEnd();
    */
}

void SceneGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    //return;
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}
