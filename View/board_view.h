#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <list>

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QPaintEvent>
#include <QVector>
#include <QPointF>
#include <QtGui/qevent.h>

#include "../debug.h"

#include "View/piece_view.h"
#include "View/cell.h"
#include "View/motif_view.h"
#include "Model/board.h" // TODO A remplacer par board_view à priori

/**
 * La classe widget d'affichage d'un plateau et de ses cellules et pièces
 * @author Florian
 */
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

    /*** Getters    ***/
    /**
     * @brief height
     * @return la hauteur du plateau (nombre de pièces verticalement)
     */
    int get_height()    const { return board->get_height(); }
    /**
     * @brief width
     * @return la largeur du plateau (nombre de pièces horizontalement)
     */
    int get_width()     const { return board->get_width(); }
    const Configuration& getConfig() const { return board->getConfig(); }

    /**
     * Dessine un triangle et un rectangle formants un motif, à partir de couleurs
     * @param path Chemin formant le triangle
     * @param colors Motif contenant les couleurs utilisées
     * @param pos_rect La position du carrés
     */
    void drawMotif(const QPainterPath &path, const QPointF& square_pos, const Motif& colors);

    /**
     * Imprime une pièce selon sa position, et ses identifiants de motifs
     * @param column
     * @param row
     * @param motifs tableau d'identifiants de motifs
     * @author Florian
     */
    void drawPiece(int column, int row, const PairColors motifs[4]);

    /**
     * Dessine l'ensemble du plateau dans le buffer
     * @author Ugo et Florian
     */
    void drawBoard();

    /**
     * Vide le buffer et rafraichit l'affichage
     * @author Florian
     */
    void redraw();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent* event);

//signals:

//public slots:

};

#endif // BOARDWIDGET_H
