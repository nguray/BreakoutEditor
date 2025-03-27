#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_imgBricks.load(":/images/Bricks.png", "PNG");

    m_levelArea = new RLevelArea(this, &m_imgBricks);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(20, 6, 48));
    m_levelArea->setAutoFillBackground(true);
    m_levelArea->setPalette(pal);

    // m_levelArea->setStyleSheet("QWidget {background-color:rgb(20, 6, 48)}");

    m_brickBar  = new RBrickBar(this, &m_imgBricks);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(m_levelArea);
    hbox->addWidget(m_brickBar);
    int w = width();
    hbox->setStretch(0, w);
    hbox->setStretch(1, 80);

    //--
    ui->centralwidget->setLayout(hbox);

    //--
    connect(m_brickBar, &RBrickBar::brickChanged, m_levelArea, &RLevelArea::setSelectedBrickSlot);

    setFixedSize(700,740);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    //---------------------------------------------
    close();

}


void MainWindow::on_actionOpen_triggered()
{
    QString         fileName;
    //----------------------------------------------------
    QString currentDir = QDir::currentPath();

    fileName = QFileDialog::getOpenFileName(this, tr("Open Level"),
                                      fileName, tr("Text Files (*.txt)"));

    if (!fileName.isNull()) {
        //--
        m_fileName = fileName;
        //--
        m_levelArea->LoadLevel(m_fileName);
        //--
        QDir dir(m_fileName);
        fileName = dir.dirName();
        //--
        ui->statusbar->showMessage(fileName);
    }

}


void MainWindow::on_actionSave_triggered()
{
    //---------------------------------------------
    if (!m_fileName.isNull()) {
        //--
        m_levelArea->SaveLevel(m_fileName);
    }
    else {
        on_actionSave_As_triggered();
    }

}


void MainWindow::on_actionSave_As_triggered()
{
    QString		fileName;
    //----------------------------------------------------

    fileName = QFileDialog::getSaveFileName(this, tr("Save Level"),
                                            fileName, tr("Text Files (*.txt)"));

    if (!fileName.isNull()) {
        //--
        m_fileName = fileName;
        //--
        m_levelArea->SaveLevel(fileName);

        //--
        QDir dir(m_fileName);
        fileName =  dir.dirName();
        //--
        ui->statusbar->showMessage(fileName);

    }

}

