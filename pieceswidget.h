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
#include <QVector>
#include <QPointF>

#include "Model/piece_model.h"
#include "Model/cell.h"
#include "Model/board_model.h"

class PiecesWidget : public QWidget
{
    Q_OBJECT
private :
    QImage* buffer;
    QColor* color;
    QPainter* bufferPainter;
    Board*  board;

public:
    explicit PiecesWidget(QWidget *parent = 0);

    /**
     * Imprime une cellule à une position donnée, utilise la couleur courante
     * @author Florian
     * @param int col,row indices de la colonne et de la ligne de la cellules
     */
    void drawCell(int colonne, int ligne);
    /**
     * Imprime une pièce selon sa position, utilise la couleur courante.
     * @author Florian
     * @param ab arbre à dessiner
     * @deprecated
     */
    void drawPiece(const Piece* p);
    /**
     * Dessine l'ensemble des arbres de la liste passée en paramètre
     * @param arbres liste des arbres à dessiner
     * @author Florian et Ugo (commentaires :p )
     */
    void drawList(std::list< Piece* >* pieces);
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


signals:

public slots:
};

#endif // PIECESWIDGET_H
