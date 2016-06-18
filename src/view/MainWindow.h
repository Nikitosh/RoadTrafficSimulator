#ifndef ROADTRAFFICSIMULATOR_MAINWINDOW_H
#define ROADTRAFFICSIMULATOR_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <src/model/World.h>

class QGraphicsView;
class QSlider;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    static constexpr double MINIMUM_SCALE = 0.04;
    static constexpr int TIMER_INTERVAL = 1000 / 25; //FPS = 25
    QTimer *timer;
    QGraphicsView *view;
    QSlider *scaleSlider;
    double currentScale = Settings::getInstance().getScale();

public:
    static const int SPEED_SLIDER_MAXIMUM = 9;
    static const int SPEED_SLIDER_INITIAL_POSITION = (1 + SPEED_SLIDER_MAXIMUM) / 2;
    MainWindow();
    ~MainWindow();

private:
    void startTimer();
    void scaleView();
};

#endif //ROADTRAFFICSIMULATOR_MAINWINDOW_H
