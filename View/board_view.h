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
     * Imprime une cellule à une position donnée, utilise la couleur courante
     * @author Florian
     * @param int col,row indices de la colonne et de la ligne de la cellules
     */
    void drawCell(int column, int line);
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
     * Dessine l'ensemble des arbres de la liste passée en paramètre
     * @param arbres liste des arbres à dessiner
     * @author Florian et Ugo (commentaires :p )
     */
    void drawList(std::map<Piece *, Coordinates> *cells);
    /**
     * Dessine l'ensemble des arbres de la liste passée en paramètre
     * @param arbres liste des arbres à dessiner
     * @author Florian et Ugo (commentaires :p )
     */
    void drawList(std::list< Coordinates> *cells);
    /**
     * Dessine les arbres et cellules vides dans le buffer
     * @author Ugo et Florian
     */
    void drawBoard();
    /**
     * Redessine les pièces qui ont changés d'état, sur l'ancienne matrice
     * On "réutilise" les cellules non susceptibles d'avoir été modifiées
     * @author Florian et Ugo
     */
    void drawChanged();
    /**
     * Vide le buffer et rafraichit l'affichage
     * @author Florian et Ugo
     */
    void redraw();

    /**
      * A partir d'un id, créé et retourne un motif (unique)
      * @author Antoine
      */
    Motif* get_color(int id);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent* event);

//signals:

//public slots:

};

#endif // PIECESWIDGET_H
