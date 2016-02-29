#include <QApplication>

#include "mainwindow.h"
#include "Model/configuration.h"
//#include "Controller/controller_config.h"
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/board_model.h"
#include "Model/configuration.h"
#include "View/board_view.h"

using namespace std;

int main(int argc, char *argv[])
{
    /**
     * Utiliser le bloc ci-dessous pour Appli Qt
     * @return
     */
    /*
    QApplication a(argc, argv);

/// TODO A placer dans mainwindow
    Configuration* config= new Configuration("../eternity2/instances_puzzles/pieces_04x04.txt");
    config->randomConfiguration();
//    if (config->tryLoadFile("../eternity2/instances_puzzles/pieces_04x04.txt")){
        cout << "Instance (configuration) statique" << endl;
    //    cout << ((Instance)config)<< endl;

        Board* board_model= new Board(config);
    //    MainWindow w(board_model);
    //    w.show();
    //    w.showBoard();
        BoardWidget* board_view= new BoardWidget(board_model);
        board_view->show();
        board_view->drawCell(1,1);

        return a.exec();
//    }
//    else {
//        cerr<< "Impossible d'ouvrir le fichier d'instance"<< endl;

//    }
//    */

    /**
      * Utiliser le bloc suivant pour debug console
      * @return
      */

    // Test piece et instance

    int tab_tmp[4];

    for(int i = 0; i < 4; ++i ){
        tab_tmp[i] =  (1+i)*5;
    }

    Instance inst;
    inst.tryLoadFile("../eternity2/instances_puzzles/pieces_04x04.txt");

    Configuration c(inst);
    c.randomConfiguration();
    cout << c;

    int tab[4] = {0, 1, 2, 3};
    int * rotate = c.rotate(tab, 1);

    cout << rotate[0] << endl;

    return 0;
}
