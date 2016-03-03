#include <QApplication>

#include "View/mainwindow.h"
#include "Model/configuration.h"
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/board_model.h"
#include "Model/configuration.h"
#include "View/board_view.h"
#include "algorithm.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    MainWindow w;
    if (w.init_configuration("../eternity2/instances_puzzles/pieces_03x03.txt")) {

//        w.show(); // TODO initialiser correctement et remettre cette ligne
//        w.showBoard();
        return app.exec();
    } else {
        return EXIT_FAILURE;
    }
}
