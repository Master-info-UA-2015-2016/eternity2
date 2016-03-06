#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "View/board_view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(Board *b, QWidget *parent = 0);
    ~MainWindow();

private:
    /**
     * Définit le plateau devant être affiché dans la fenêtre
     * @param _board
     */
    void set_board(Board* _board);

public:
    /**
     * Initialise la configuration à partir d'un fichier d'instance
     * @param filename : nom du fichier d'instance à charger
     * @return true si le fichier est correctement lue
     */
    bool init_configuration(std::string instance_filename);

    /**
     * Dessine et afficher le plateau
     * @deprecated
     */
    void showBoard() const;

    /**
     * Exécute les algorithmes de résolution sur la configuration du plateau
     * TODO : créer des fonctions et mettre celles qui ne sont pas relevantes ici dans "algorithme"
     */
    void launch_resolution();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // MAINWINDOW_H
