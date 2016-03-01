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
    Instance inst;
    inst.tryLoadFile("../eternity2/instances_puzzles/pieces_04x04.txt");

    Configuration C(&inst);
    C.randomConfiguration();
    cout << C << endl;
    if(C.constraintRows())
        cout << "Contraintes de lignes validées !" << endl;
    else
        cout << "Contraintes de lignes non validées." << endl;

    if(C.constraintCols())
        cout << "Contraintes de colonnes validées !" << endl;
    else
        cout << "Contraintes de colonnes non validées." << endl;

//    Algorithm::local_search(&inst);

    QApplication app(argc, argv);

    MainWindow w;
    if (w.init_configuration("../eternity2/instances_puzzles/pieces_04x04.txt")) {

//        w.show(); TODO initialiser correctement et remettre cette ligne
//        w.showBoard();
        return app.exec();
    } else {
        return EXIT_FAILURE;
    }
}
