#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QTimer>
#include <QtWidgets/QPushButton>
#include "MainWindow.h"
#include "View.h"

MainWindow::MainWindow() {
    View *view = new View;
    QGraphicsScene *scene = new QGraphicsScene;
    view->setScene(scene);

    QPushButton *nextButton = new QPushButton("Next");
    connect(nextButton, &QPushButton::released, view, &View::updateState);

    timer = new QTimer();
    timer->setInterval(40);
    connect(timer, &QTimer::timeout, view, &View::updateState);

    QPushButton *playButton = new QPushButton("Play");
    connect(playButton, &QPushButton::released, this, &MainWindow::startTimer);
    QPushButton *pauseButton = new QPushButton("Pause");
    connect(pauseButton, &QPushButton::released, timer, &QTimer::stop);

    QHBoxLayout *hLayout = new QHBoxLayout;
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
