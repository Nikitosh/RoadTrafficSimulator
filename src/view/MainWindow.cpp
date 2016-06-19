#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QTimer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include "MainWindow.h"
#include "Scene.h"

MainWindow::MainWindow() {
    scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setRange(1, 10);
    scaleSlider->setSliderPosition(3);
    Settings::getInstance().setScale(scaleSlider->value() * MainWindow::MINIMUM_SCALE);
    currentScale = scaleSlider->value() * MainWindow::MINIMUM_SCALE;
    scaleSlider->setTickPosition(QSlider::TicksBelow);
    connect(scaleSlider, &QAbstractSlider::valueChanged, this, &MainWindow::scaleView);

    view = new QGraphicsView;
    World *world = World::generateFullMap(3, 4, 100);
    Scene *scene = new Scene(world);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->scale(Settings::getInstance().getScale(), Settings::getInstance().getScale());
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setRenderHint(QPainter::Antialiasing);

    QLabel *scaleLable = new QLabel("Scale");

    QLabel *speedLable = new QLabel("Speed");
    QSlider *speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(1, 9);
    speedSlider->setSliderPosition(5);
    speedSlider->setTickPosition(QSlider::TicksBelow);
    connect(speedSlider, &QAbstractSlider::valueChanged, scene, &Scene::scaleSpeed);

    QPushButton *nextButton = new QPushButton("Next");
    connect(nextButton, &QPushButton::released, scene, &Scene::updateState);

    timer = new QTimer();
    timer->setInterval(TIMER_INTERVAL);
    connect(timer, &QTimer::timeout, scene, &Scene::updateState);

    QPushButton *playButton = new QPushButton("Play");
    connect(playButton, &QPushButton::released, this, &MainWindow::startTimer);
    QPushButton *pauseButton = new QPushButton("Pause");
    connect(pauseButton, &QPushButton::released, timer, &QTimer::stop);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(scaleLable);
    hLayout->addWidget(scaleSlider);
    hLayout->addStretch(1);
    hLayout->addWidget(speedLable);
    hLayout->addWidget(speedSlider);
    hLayout->addStretch(1);
    hLayout->addWidget(nextButton);
    hLayout->addWidget(playButton);
    hLayout->addWidget(pauseButton);
    hLayout->addStretch(1);
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(view);
    vLayout->addLayout(hLayout);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
    delete timer;
}

void MainWindow::startTimer() {
    timer->start();
}

void MainWindow::scaleView() {
    double scale = scaleSlider->value() * MainWindow::MINIMUM_SCALE / currentScale;
    currentScale = scaleSlider->value() * MainWindow::MINIMUM_SCALE;
    view->scale(scale, scale);
}