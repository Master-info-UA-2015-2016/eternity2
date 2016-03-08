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
#if DEBUG_UI
    cout << "Construction de Maindow sans plateau"<< endl;
#endif
//    ui->board= NULL;
}

MainWindow::MainWindow(Board *b, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if DEBUG_UI
    cout << "Construction de Maindow avec un plateau de valeur "<< b<< endl;
#endif
    cout<< "ATTENTION, la valeur du plateau est ignorée"<< endl;
//    ui->board= new BoardWidget(this, b);
}

MainWindow::~MainWindow()
{
    delete ui->board;
    delete ui;
}


void MainWindow::set_board(Board *_board)
{
//    if(ui->board != NULL) delete ui->board; // Utile si on fait new, sinon TODO supprimer

    ui->board->set_board(_board);
}

bool MainWindow::init_configuration(std::string instance_filename)
{
    Instance* instance= new Instance;
    if (instance->tryLoadFile(instance_filename)){

        Configuration* config= new Configuration(instance);
        config->randomConfiguration();
#if DEBUG_SHOW_PIECES
        for(auto c : *(config->getPieces())) {
            cout << c << endl;
        }
#endif
#if DEBUG_INIT_CONFIG
        cout << (*config) << endl;
        cout << "Nombre d'erreurs :" << config->checkPieces()  << endl;
        cout << "\t=> " << config->constraintPieces() << endl;
#endif

        Board* board_init= new Board(config);
        set_board(board_init);

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
        Configuration * solution = new Configuration(ui->board->getConfig());

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
        BoardWidget* sol_board= new BoardWidget(NULL, board_sol);
        sol_board->show();


        cout << "Nombre d'erreurs :" << solution->countNbErrors()  << endl;
        cout << *solution << endl;
        cout << "\t=> " << solution->misplacedPieces() << endl;
#endif
#if DEBUG_EVALUATION
        cout << "Adjacences (0,0) " << ui->board->getConfig().isConstraintAdjacencesRespected(0,0) << endl;
        int nb_errors= ui->board->getConfig().countNbErrors();

        cout << "Nombre d'erreurs :" << nb_errors  << endl;

//        cout << "Evaluation : " << Algorithm::evaluation((*config)) << endl;
#endif
#if DEBUG_LOCAL_SEARCH
        Configuration * local = Algorithm::local_search(&(ui->board->getConfig()));
        cout << *local << endl;
        cout << "\t=> " << local->misplacedPieces() << endl;

        Board* board_final= new Board(local);
        BoardWidget* res_board= new BoardWidget(NULL, board_final);
        res_board->show();
#endif

}

void MainWindow::testShowConfig() const
{   clog << (ui->board->getConfig())<< endl; }

void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    cout << "MainWindow_paintEvent : affichage fenêtre"<< std::endl;
    ui->board->show(); // TODO vérifier utilité
}

void MainWindow::load_instance()
{
    QFileDialog* fileLoadDialog= new QFileDialog(this);
    fileLoadDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileLoadDialog->setNameFilter(tr("Load") +" (*.txt *.inst)");

    string filename;
    if(fileLoadDialog->exec() == QDialog::Accepted){
        filename= fileLoadDialog->selectedFiles().at(0).toStdString();

        init_configuration(filename);
        ui->board->redraw(); // utile ?
    }
    delete fileLoadDialog;

}
