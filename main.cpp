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

    Configuration C("../eternity2/instances_puzzles/pieces_03x03.txt");
    C.placePiece(make_pair(1, 1));
    C.placePiece(make_pair(7, 2));

    vector<pair<int, int> > pairs = C.getAdjacents(1, 0);

    cout << "Test Pair" << endl;
    for(pair<int, int> P : pairs) {
        cout << "id adj :"<< (P.first) << endl;
    }

    MainWindow window;
    if (window.init_configuration("../eternity2/instances_puzzles/pieces_03x03.txt")) {
        window.testShowConfig();
        window.show();
        window.launch_resolution();

        return app.exec();
    } else {
        return EXIT_FAILURE;
    }
}
