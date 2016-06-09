#ifndef ROADTRAFFICSIMULATOR_MAINWINDOW_H
#define ROADTRAFFICSIMULATOR_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <src/model/World.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QTimer *timer;

public:
    MainWindow();
    void startTimer();
};

#endif //ROADTRAFFICSIMULATOR_MAINWINDOW_H
