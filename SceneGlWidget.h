#ifndef SCENEGLWIDGET_H
#define SCENEGLWIDGET_H

#include <QGLWidget>

#include <QMouseEvent>
#include <QEvent>

#include <QTimer>

#include "3DMath/Point3D.h"
#include "3DMath/RotationHolder.h"
#include "Model/Scene/Scene.h"

class SceneGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit SceneGLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

signals:
    void MousePressSignal();
    void MouseMoveSignal();
    void MouseReleaseSignal();
    void LeaveSignal();

public:
    void Rotate(int x, int y, int z);

private:
    void UpdateViewPoint();
private slots:
    void UpdateScene();

public:
    int mousePosX();
    int mousePosY();

private:
    int _mousePosX;
    int _mousePosY;
    RotationHolder<int> _rotation;
    Point3D<int> _transition;
    Scene _scene;
    QTimer _timer;
};

#endif // SCENEGLWIDGET_H