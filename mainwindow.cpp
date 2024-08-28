#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // main window
    ui->setupUi(this);
    setWindowTitle("Hangman");

    // game window
    gw = new GameWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_button_clicked()
{
    this->close();
    gw->show();
}


void MainWindow::on_quit_button_clicked()
{
    this->close();
}

