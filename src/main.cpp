#include <QApplication>
#include <src/view/MainWindow.h>
#include <src/algo/MonteCarlo.h>
#include <src/algo/SimulatedAnnealing.h>

int main(int argc, char *argv[]) {


    QApplication application(argc, argv);
    MainWindow window;
    window.setFixedSize(1080, 760);
    window.show();
    return application.exec();


    //srand(239);
    //MonteCarlo monteCarlo;
    //printf("%f\n", monteCarlo.run());
    //SimulatedAnnealing simulatedAnnealing;
    //printf("%f\n", simulatedAnnealing.run());
}
