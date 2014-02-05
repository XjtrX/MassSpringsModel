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
    void MousePressSignal(QMouseEvent *ev);
    void MouseMoveSignal();
    void MouseReleaseSignal();
    void LeaveSignal();

public slots:
    void UpdateScene();

    void StartSimulation();
    void StopSimulation();
    void NextIteration();
    void ChangePerspective(int val);

public:
    void Rotate(int x, int y, int z);
    void Translate(int x, int y, int z);
    int getSimulationStatus();

private:
    void UpdatePerspective();
    void UpdateViewPoint();

public:
    int mousePosX();
    int mousePosY();

private:
    int _mousePosX;
    int _mousePosY;
    int _width;
    int _height;
    RotationHolder<int> _rotation;
    Point3D<float> _transition;
    float _perspectiveAngle;
    Scene _scene;
    float _timeInterval;
    float _repaintDelay;
    float _timeToFrame;
    QTimer _timer;
};

#endif // SCENEGLWIDGET_H
