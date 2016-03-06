#include <QApplication>

#include "View/mainwindow.h"
#include "Model/configuration.h"
#include "Model/piece.h"
#include "Model/instance.h"
#include "Model/board.h"
#include "Model/configuration.h"
#include "View/board_view.h"
#include "algorithm.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    MainWindow window;
    if (window.init_configuration("../eternity2/instances_puzzles/pieces_03x03.txt")) {

        window.show(); // TODO initialiser correctement et remettre cette ligne
//        window.launch_resolution();
//        w.showBoard();
        return app.exec();
    } else {
        return EXIT_FAILURE;
    }
}
