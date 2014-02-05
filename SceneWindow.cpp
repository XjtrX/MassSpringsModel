#include "SceneWindow.h"
#include "ui_scenewindow.h"

#include "iostream"
using namespace std;

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(MouseMoveSignal()), this, SLOT(MouseMoveSlot()));
    connect(ui->widget, SIGNAL(MousePressSignal(QMouseEvent *))
            , this, SLOT(MousePressSlot(QMouseEvent *)));
    connect(ui->widget, SIGNAL(MouseReleaseSignal()), this, SLOT(MouseReleaseSlot()));
    connect(ui->widget, SIGNAL(LeaveSignal()), this, SLOT(LeaveSlot()));

    connect(this, SIGNAL(StartSimulation()), ui->widget, SLOT(StartSimulation()));
    connect(this, SIGNAL(StopSimulation()), ui->widget, SLOT(StopSimulation()));
    connect(this, SIGNAL(NextIteration()),  ui->widget, SLOT(NextIteration()));
    connect(this, SIGNAL(UpdatePerspective(int))
            , ui->widget, SLOT(ChangePerspective(int)));

    _mousePressed = 0;
}

SceneWindow::~SceneWindow()
{
    delete ui;
}

void SceneWindow::MouseMoveSlot()
{
    int mPX = this->ui->widget->mousePosX();
    int mPY = this->ui->widget->mousePosY();
    int x = mPX - _prevMousePos.getX();
    int y = mPY - _prevMousePos.getY();
    _prevMousePos.setX(mPX);
    _prevMousePos.setY(mPY);
    //cout << x << " " << y << endl;
    //cout.flush();
    if (_mousePressed > 0)
    {
        if (_mousePressed == 1)
        {
            this->ui->widget->Rotate(-y, -x, 0);
        }
        else
        {
            this->ui->widget->Translate(-x, y, 0);
        }
        if (0 == ui->widget->getSimulationStatus())
        {
            ui->widget->repaint();
        }
    }
}

void SceneWindow::MousePressSlot(QMouseEvent *ev)
{
    _mousePressed = 1;
    _prevMousePos.setX(this->ui->widget->mousePosX());
    _prevMousePos.setY(this->ui->widget->mousePosY());
    if (ev->button() == Qt::RightButton)
    {
        _mousePressed = 2;
    }
}

void SceneWindow::MouseReleaseSlot()
{
    _mousePressed = 0;
    //cout << "Mouse Release\n";
    //cout.flush();
}


void SceneWindow::LeaveSlot()
{
    //cout << "Leave\n";
    //cout.flush();
}

void SceneWindow::wheelEvent(QWheelEvent *we)
{
    int val = we->angleDelta().y() > 0 ? 1 : -1;
    emit UpdatePerspective(-val);
}

void SceneWindow::on_pB_Start_released()
{
    emit StartSimulation();
}

void SceneWindow::on_pB_Stop_released()
{
    emit StopSimulation();
}

void SceneWindow::on_pB_Next_pressed()
{
    emit NextIteration();
}
