#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "View/board_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Instance* instance;

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(Board *b, QWidget *parent = 0);
    ~MainWindow();

private:
    /**
     * Définit le plateau devant être affiché dans la fenêtre
     * @param _board
     * @author Florian
     */
    void set_board(Board* _board);

public:
    /**
     * Initialise la configuration à partir d'un fichier d'instance
     * @param filename : nom du fichier d'instance à charger
     * @return true si le fichier est correctement lue
     * @author Florian
     */
    bool init_configuration(std::string instance_filename);

    /**
     * Permet d'afficher la configuration dans le terminal
     * @test fonction utilisée afin de vérfiée que le plateau, la config et l'instance
     *  sont bien initialisés
     * @author Florian
     */
    void testShowConfig() const;

public slots:
    /**
     * Exécute les algorithmes de résolution sur la configuration du plateau
     * créer des fonctions et mettre celles qui ne sont pas relevantes ici dans "algorithme"
     * @author Florian
     */
    void launch_resolution();

    /**
     * Exécute l'algorithme de CSP sur l'instance de la classe
     * @author DAVID Florian
     */
    void launch_CSP();

protected:
    void paintEvent(QPaintEvent* event);

    /*** Loads and saves  ***/
public slots:
    /**
     * Exécute l'algorithme de recherche local sur la configuration du plateau
     * @author FOURMOND Jérôme
     */
    void launch_local_search();
    /**
     * Ouvre un explorateur et charge une instance à partir du fichier sélectionné
     */
    void load_instance();
};

#endif // MAINWINDOW_H
