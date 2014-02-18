#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QMainWindow>
#include "SceneGlWidget.h"

#include "3DMath/Point2D.h"

namespace Ui {
class SceneWindow;
}

class SceneWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SceneWindow(QWidget *parent = 0);
    ~SceneWindow();
    
private slots:
    void MouseMoveSlot();
    void MousePressSlot(QMouseEvent *ev);
    void MouseReleaseSlot();
    void LeaveSlot();
    void wheelEvent(QWheelEvent *we);

    void on_pB_Start_released();

    void on_pB_Stop_released();

    void on_pbCollide_released();

    void on_pb_Step_clicked();

signals:
    void StartSimulation();
    void StopSimulation();
    void NextIteration();
    void UpdatePerspective(int val);
    void Collide();

private:
    int _mousePressed;
    Point2D<int> _prevMousePos;
    Ui::SceneWindow *ui;
};

#endif // SCENEWINDOW_H
