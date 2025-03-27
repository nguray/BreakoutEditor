#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RLevelArea.h"
#include "RBrickBar.h"
#include <QtWidgets/QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    RLevelArea		*m_levelArea;
    RBrickBar		*m_brickBar;
    QImage      m_imgBricks;
    QString     m_fileName;

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
