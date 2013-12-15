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
    void MousePressSlot();
    void MouseReleaseSlot();
    void LeaveSlot();

private:
    int _mousePressed;
    Point2D<int> _prevMousePos;
    Ui::SceneWindow *ui;
};

#endif // SCENEWINDOW_H
