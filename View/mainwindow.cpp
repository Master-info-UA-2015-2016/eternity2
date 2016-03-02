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

void MainWindow::set_board(Board *_board)
{
    ui->board= new BoardWidget(_board, this);
}

bool MainWindow::init_configuration(std::string filename)
{
    Instance* instance= new Instance;
    if (instance->tryLoadFile(filename)){

        Configuration* config= new Configuration(instance);
        config->randomConfiguration();
#if DEBUG_SHOW_RANDOM_CONFIG
        cout << (*config) << endl;
        cout << "\t- Lignes : " << config->constraintRowsXtrem() << endl;
        cout << "\t- Colonnes : " << config->constraintColsXtrem() << endl;
        cout << "\t- Angles : " << config->constraintEdges() << endl;
        cout << "Contraintes d'angles sur la première case ? " << config->constraintEdges(0,0) << endl;
        cout << "Contraintes de lignes extrèmes sur la seconde case ? " << config->constraintRowsXtrem(1,0) << endl;
        cout << "Contraintes de colonnes extrèmes sur la quatrième case ? " << config->constraintColsXtrem(0,1) << endl;
        config->constraintPieces();
#endif

#if DEBUG_EVALUATION
//        cout << "Nombre d'erreurs " << endl;
//        cout << "Check ? " << config->checkPieces() << endl;
        cout << "Evaluation : " << Algorithm::evaluation((*config)) << endl;
        Configuration * local = Algorithm::local_search(instance);
        cout << *local << endl;
#endif



        Board* board_model= new Board(config);

        BoardWidget* board_view= new BoardWidget(board_model);
        board_view->show();

        return true;
    } else {
        cerr<< "Impossible d'ouvrir le fichier d'instance"<< endl;
        return false;
    }
}

void MainWindow::showBoard()
{
    ui->board->redraw();
    ui->board->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    std::cout << "MainWindow_paintEvent : affichage fenêtre"<< std::endl;
    ui->board->show(); // TODO vérifier utilité
}
