#include <c++/ctime>
#include <QApplication>
#include <src/view/MainWindow.h>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.setFixedSize(1080, 760);
    window.show();
    return application.exec();

    /*
    World *world = new World;
    world->read("resources/map.txt");
    for (int i = 0; i < 6666; i++)
        world->onTick(0.3);
    printf("%f\n", clock() * 1.);
    */
}
