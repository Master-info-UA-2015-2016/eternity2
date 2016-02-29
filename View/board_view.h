#ifndef PIECESWIDGET_H
#define PIECESWIDGET_H

#include <list>

#include <QWidget>
#include <QColor>
#include <QBrush>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QPaintEvent>
#include <QVector>
#include <QPointF>
#include <QtGui/qevent.h>	// IMPROVEIT pas d'equivalent sans .h ?

#include "View/piece_view.h"
#include "View/cell.h"
#include "View/motif.h"
#include "Model/board_model.h" // TODO A remplacer par board_view à priori

class BoardWidget : public QWidget
{
    Q_OBJECT
private :
    QImage* buffer;
    QPainter* bufferPainter;
    Board*  board;
    int cell_size;

public:
    explicit BoardWidget(Board* b, QWidget *parent = 0);
    explicit BoardWidget(QWidget *parent = 0);

    void init_board(Board* b);
    /**
     * Imprime une pièce selon sa position, utilise la couleur courante.
     * @author Florian
     * @param ab arbre à dessiner
     * @deprecated
     */
    void drawPiece(int column, int line, int motif[4]);
    /**
     * Imprime une pièce selon sa position, utilise la couleur courante.
     * @author Florian
     * @param ab arbre à dessiner
     * @deprecated
     */
    void drawPiece(const PieceView *p);

    /**
     * Commentaires ???
     * @author Ugo et Florian
     */
    void drawBoard();

    /**
     * Vide le buffer et rafraichit l'affichage
     * @author Florian et Ugo
     */
    void redraw();

    /**
      * A partir d'un id, créé et retourne un motif (unique)
      * @author Antoine
      */
    Motif get_color(int id);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent* event);

//signals:

//public slots:

};

#endif // PIECESWIDGET_H
