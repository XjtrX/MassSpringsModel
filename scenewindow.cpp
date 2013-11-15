#include "scenewindow.h"
#include "ui_scenewindow.h"

#include "iostream"
using namespace std;

SceneWindow::SceneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);
    connect(ui->widget, SIGNAL(MouseMoveSignal()), this, SLOT(MouseMoveSlot()));
    connect(ui->widget, SIGNAL(MousePressSignal()), this, SLOT(MousePressSlot()));
    connect(ui->widget, SIGNAL(MouseReleaseSignal()), this, SLOT(MouseReleaseSlot()));
    connect(ui->widget, SIGNAL(LeaveSignal()), this, SLOT(LeaveSlot()));
}

SceneWindow::~SceneWindow()
{
    delete ui;
}

void SceneWindow::MouseMoveSlot()
{
    cout << this->ui->widget->x() - this->ui->widget->width() / 2 << " "
         << this->ui->widget->y() - this->ui->widget->height() / 2 << endl;
    cout.flush();
}

void SceneWindow::MousePressSlot()
{
    cout << "Mouse Pressed\n";
    cout.flush();
}

void SceneWindow::MouseReleaseSlot()
{
    cout << "Mouse Release\n";
    cout.flush();
}


void SceneWindow::LeaveSlot()
{
    cout << "Leave\n";
    cout.flush();
}
