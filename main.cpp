#include <QApplication>

#include "View/mainwindow.h"
#include "Model/configuration.h"
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/board_model.h"
#include "Model/configuration.h"
#include "View/board_view.h"

using namespace std;

int main(int argc, char *argv[])
{
    Instance inst;
    inst.tryLoadFile("../eternity2/instances_puzzles/pieces_04x04.txt");

    Configuration c(&inst);
    c.randomConfiguration();
    cout << c;

    QApplication app(argc, argv);

    MainWindow w;
    if (w.init_configuration("../eternity2/instances_puzzles/pieces_04x04.txt")) {

//        w.show();
//        w.showBoard();
        return app.exec();
    } else {
        return EXIT_FAILURE;
    }
/// FIN A placer
}
