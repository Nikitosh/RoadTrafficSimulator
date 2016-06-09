#ifndef ROADTRAFFICSIMULATOR_SCENE_H
#define ROADTRAFFICSIMULATOR_SCENE_H


#include <QtWidgets/QGraphicsView>
#include <QtGui/QPaintEvent>
#include <src/model/World.h>

class View : public QGraphicsView {
    Q_OBJECT

private:
    const double OFFSET_X[4][3] = {
            {0.6, 0.725, 0.85},
            {0.85, 0.85, 0.85},
            {0.35, 0.225, 0.1},
            {0.1, 0.1, 0.1}
    };
    const double OFFSET_Y[4][3] = {
            {0.85, 0.85, 0.85},
            {0.35, 0.225, 0.1},
            {0.1, 0.1, 0.1},
            {0.6, 0.725, 0.85}
    };
    World *world;

public:
    View();
    void updateState();

protected:
    virtual void paintEvent(QPaintEvent *event);
};


#endif //ROADTRAFFICSIMULATOR_SCENE_H
