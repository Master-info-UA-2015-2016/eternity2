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

    void set_board(Board* _board);

    void showBoard();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // MAINWINDOW_H
