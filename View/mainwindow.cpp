#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"
#include "algorithm.h"

using namespace std;

//  TODO @flodavid
//      Affichage sans plateau
//      Correction affichage d'une nouvelle instance dans le plateau (bug d'affichage)

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
    ui->board->set_board(_board);
}

bool MainWindow::init_configuration(std::string instance_filename)
{
    instance= new Instance;
    if (instance->tryLoadFile(instance_filename)){

        Configuration* config= new Configuration(instance);
        config->randomConfiguration();

#if DEBUG_SHOW_PIECES
        for(auto c : *(config->getPieces())) {
            cout << c << endl;
        }
#endif
#if DEBUG_INIT_CONFIG
        cout << (*config);
        cout << "Nombre d'erreurs :" << config->countNbErrors()  << endl;
        cout << "\tPièces malplacées=> " << config->misplacedPieces() << endl;
        cout << "\tContraintes d'adjacences->"  << config->nbErrorsAdjacences() << endl;
#endif
        Board* board_init= new Board(config);
        set_board(board_init);

        return true;
    } else {
        cerr<< "Impossible d'ouvrir le fichier d'instance"<< endl;
        return false;
    }
}


void MainWindow::testShowConfig() const
{   clog << (ui->board->getConfig())<< endl; }



void MainWindow::launch_resolution()
{
#if DEBUG_GENETIC
        int nb_config= 10;
        std::vector<Configuration *> genetic= Algorithm::initGenetic(instance, nb_config);
        std::vector<Configuration *> new_generation;

        for(int i= 0; i < nb_config; ++i){
            new_generation= Algorithm::geneticSearch(genetic);
        }

        int ind_best_child= Algorithm::getBestConfig(new_generation);

        Board* board_final2= new Board(new_generation[ind_best_child]);
        BoardWidget* res_board2= new BoardWidget(NULL, board_final2);
        res_board2->show();

#endif

}

void MainWindow::launch_CSP()
{
    Configuration * CSP = Algorithm::resolveWithCSP(instance);
    cout << "##########\tCSP\t##########" << endl;
    cout << (*CSP) << endl;
    cout << "##########\tFIN CSP\t##########" << endl;
    cout << "Nombre d'erreurs : "<< CSP->countNbErrors()<< endl;

    Board* board_final= new Board(CSP);
    BoardWidget* res_board= new BoardWidget(NULL, board_final);
    res_board->show();
}

void MainWindow::launch_local_search() {
    Configuration * local = Algorithm::local_search(&(ui->board->getConfig()));
    cout << *local;
    cout << "Nombre d'erreurs :" << local->countNbErrors()  << endl;

    Board* board_final= new Board(local);
    BoardWidget* res_board= new BoardWidget(NULL, board_final);
    res_board->show();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
#if DEBUG_DRAW_WIDGETS
    cout << "MainWindow_paintEvent : affichage fenêtre"<< std::endl;
#endif
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
//        ui->board->update(); // utile ?
        hide();
        show();
        ui->board->redraw(); // utile ?
    }
    delete fileLoadDialog;

}
