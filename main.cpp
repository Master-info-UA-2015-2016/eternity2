#include <QApplication>

//#include "pieceswidget.h"
//#include "mainwindow.h"

#include "Model/piece_model.h"
#include "Model/instance_model.h"

using namespace std;

int main(int argc, char *argv[])
{
    /**
     * @brief Utiliser le bloc ci-dessous pour Appli Qt
     * @return
     */
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */

    /**
      * @brief Utiliser le bloc suivant pour debug console
      * @return
      */

    // Test piece et instance

    int tab_tmp[4];

    for(int i = 0; i < 4; ++i ){
        tab_tmp[i] =  (1+i)*5;
    }

    Piece *p = new Piece(1, tab_tmp);
    cout << *p;

    cout << "Fin test piece, statique et pointeur ok" << endl;

    Instance inst;
    inst.tryLoadFile("../eternity2/instances_puzzles/pieces_05x05.txt");
    cout << "Instance statique" << endl;
    cout << inst ;

    Instance *inst2 = new Instance();
    inst2->tryLoadFile("../eternity2/instances_puzzles/pieces_03x03.txt");
    cout << "Pointeur sur instance" << endl;
    cout << *inst2 ;
    cout << "Fin test instance, statique et pointeur ok" << endl;

    return 0;

}
