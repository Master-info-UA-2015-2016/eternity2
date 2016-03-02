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
        cout << "Nombre d'erreurs " << endl;
        cout << "\t- Lignes : " << config->constraintRows() << endl;
        cout << "\t- Colonnes : " << config->constraintCols() << endl;
        cout << "\t- Angles : " << config->constraintEdges() << endl;
        cout << "Evaluation : " << Algorithm::evaluation((*config)) << endl;

        cout << "Check ? " << config->checkPieces() << endl;
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
