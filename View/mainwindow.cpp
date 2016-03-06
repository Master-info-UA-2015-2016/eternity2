#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"
#include "algorithm.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(Board *b, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->board= new BoardWidget(b, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::set_board(Board *_board)
{
    ui->board= new BoardWidget(_board, this);
}

bool MainWindow::init_configuration(std::string instance_filename)
{
    Instance* instance= new Instance;
    if (instance->tryLoadFile(instance_filename)){

        Configuration* config= new Configuration(instance);
        // TODO créer une meilleure configuration initiale ?
        config->randomConfiguration();
#if DEBUG_SHOW_PIECES
        for(auto c : *(config->getPieces())) {
            cout << c << endl;
        }
#endif
#if DEBUG_INIT_CONFIG
        cout << (*config) << endl;
#endif

        Board* board_init= new Board(config);
        set_board(board_init);

//        ui->board->show();  // TODO supprimer lorsque l'affichage de mainwindow sera opérationnel

        return true;
    } else {
        cerr<< "Impossible d'ouvrir le fichier d'instance"<< endl;
        return false;
    }
}

void MainWindow::showBoard() const
{
    ui->board->redraw();
    ui->board->show();
}

void MainWindow::launch_resolution()
{
#if DEBUG_SHOW_SOL_CONFIG
        Configuration * solution = new Configuration(ui->board-> config);

        solution->placePiece(make_pair(1, 1));
        solution->placePiece(make_pair(7, 2));
        solution->placePiece(make_pair(2, 2));
        solution->placePiece(make_pair(5, 1));
        solution->placePiece(make_pair(9, 1));
        solution->placePiece(make_pair(8, 3));
        solution->placePiece(make_pair(3, 0));
        solution->placePiece(make_pair(6, 0));
        solution->placePiece(make_pair(4, 3));

        Board* board_sol= new Board(solution);
        BoardWidget* sol_board= new BoardWidget(board_sol);
        sol_board->show();


        cout << "Nombre d'erreurs :" << solution->checkPieces()  << endl;
        cout << *solution << endl;
        cout << "\t=> " << solution->constraintPieces() << endl;
#endif

#if DEBUG_EVALUATION
        cout << "Adjacences (0,0) " << config->constraintAdjacences(0,0) << endl;
        int nb_errors= config->checkPieces();
        cout << "Nombre d'erreurs :" << nb_errors  << endl;

//        cout << "Evaluation : " << Algorithm::evaluation((*config)) << endl;
#endif
#if DEBUG_LOCAL_SEARCH
        Configuration * local = Algorithm::local_search(instance);
        cout << *local << endl;
        cout << "\t=> " << local->constraintPieces() << endl;

        Board* board_final= new Board(local);
        BoardWidget* res_board= new BoardWidget(board_final);
        res_board->show();
#endif

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    std::cout << "MainWindow_paintEvent : affichage fenêtre"<< std::endl;
    ui->board->show(); // TODO vérifier utilité
}
