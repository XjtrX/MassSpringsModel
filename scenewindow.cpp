#include "scenewindow.h"
#include "ui_scenewindow.h"

//#include "iostream"
//using namespace std;

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(MouseMoveSignal()), this, SLOT(MouseMoveSlot()));
    connect(ui->widget, SIGNAL(MousePressSignal()), this, SLOT(MousePressSlot()));
    connect(ui->widget, SIGNAL(MouseReleaseSignal()), this, SLOT(MouseReleaseSlot()));
    connect(ui->widget, SIGNAL(LeaveSignal()), this, SLOT(LeaveSlot()));

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
    if (_mousePressed)
    {
        this->ui->widget->Rotate(-y, -x, 0);
//    this->ui->widget->Rotate(0, y, 0);
    }
}

void SceneWindow::MousePressSlot()
{
    _mousePressed = 1;
    _prevMousePos.setX(this->ui->widget->mousePosX());
    _prevMousePos.setY(this->ui->widget->mousePosY());
    //cout << "Mouse Pressed\n";
    //cout.flush();
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
