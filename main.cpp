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

    Piece p(1, tab_tmp);

    cout << p;

    return 0;

}
