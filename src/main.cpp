#include <QApplication>
#include <QtWidgets/QLabel>
#include <src/view/MainWindow.h>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.setFixedSize(1080, 760);
    window.show();
    return application.exec();
}
