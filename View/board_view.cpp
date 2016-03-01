#include "board_view.h"

#define DRAW_SCALE 32.0

using namespace std;

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent)
{
    buffer= new QImage;
    bufferPainter= new QPainter;
    board= new Board( new Configuration() );
}

BoardWidget::BoardWidget(Board *b, QWidget *parent) :
    QWidget(parent), board(b)
{
    buffer= new QImage;
    bufferPainter= new QPainter;
}

// ########################
/***		Affichages	***/
// ########################

// INUTILISE POUR L'INSTANT : dessine un triangle à partir d'un QVector
//    //        QVector<QPointF> tri_points(3);
//    //        tri_points.push_back(QPointF(0.0, 0.0));
//    //        tri_points.push_back(QPointF(-1.5, -1.5));
//    //        tri_points.push_back(QPointF(0.0, -3.0));
//    //        QPolygonF triangle(tri_points);

void BoardWidget::drawMotif(const QPainterPath& path, const Motif &colors, const QPointF& pos_rect)
{
#if DEBUG_DRAW_COLORS
    cout << "Couleurs du motif : "<< colors<< endl;
#endif
    bufferPainter->fillPath(path, *(colors.get_color_ext()));
    bufferPainter->fillRect(pos_rect.x() * DRAW_SCALE , pos_rect.y() * DRAW_SCALE,
                            DRAW_SCALE /3.0, DRAW_SCALE /3.0,
                            *(colors.get_color_int()) );
}

void BoardWidget::drawPiece(int column, int row, const int motifs[4])
{
    QPointF top_left(column * DRAW_SCALE,            row * DRAW_SCALE);
    QPointF middle((column +0.5) * DRAW_SCALE,      (row +0.5) * DRAW_SCALE);
    QPointF bottom_left(column * DRAW_SCALE,        (row +1.0) * DRAW_SCALE);
    QPointF top_right((column +1.0) * DRAW_SCALE,    row * DRAW_SCALE);
    QPointF bottom_right((column + 1.0) * DRAW_SCALE,(row +1.0) * DRAW_SCALE);

    QPainterPath path0(top_left);   // En haut à gauche
        path0.lineTo(middle);       // Milieu
        path0.lineTo(bottom_left);  // En bas à gauche
        path0.lineTo(top_left);     // En haut à gauche

    QPainterPath path1(top_left);   // En haut à gauche
        path1.lineTo(top_right);    // En haut à droite
        path1.lineTo(middle);       // Milieu
        path1.lineTo(top_left);     // En haut à gauche

    QPainterPath path2(top_right);  // En haut à gauche
        path2.lineTo(bottom_right); // En haut à droite
        path2.lineTo(middle);       // Milieu
        path2.lineTo(top_right);    // En haut à gauche

    QPainterPath path3(bottom_right);   // En haut à gauche
        path3.lineTo(bottom_left);      // En haut à droite
        path3.lineTo(middle);           // Milieu
        path3.lineTo(bottom_right);     // En haut à gauche

    drawMotif(path0, Motif(motifs[0]), *(new QPointF(column + 0.0,      row + 0.33)) );
    drawMotif(path1, Motif(motifs[1]), *(new QPointF(column + 0.33,    row + 0.0)) );
    drawMotif(path2, Motif(motifs[2]), *(new QPointF(column + 0.70,    row + 0.33)) );
    drawMotif(path3, Motif(motifs[3]), *(new QPointF(column + 0.33,    row + 0.70)) );
}

void BoardWidget::drawBoard()
{
    bufferPainter->begin(buffer);

    int current_height, current_width;
    for(int i= 0; i < board->height() * board->width(); ++i){
        current_width= i % board->width();
        current_height= i / board->height();

#if DEBUG_POS_PIECE
        clog << "Affichage de la pièce num "<< i;
        clog<< " de coordonnées : "<< current_width<< " ; "<< current_height<< endl;
#endif

        int* colors= board->getConfig().getRotatedMotif(current_width, current_height);
        // On affiche la pièce à la position courante, avec son motif
        drawPiece(current_width, current_height, colors);
//       }
//      else {
//               drawCell(current_width, current_height);
//       }
    }

    bufferPainter->end();
}

// Test perf
#if PERF_REDRAW
int num_redraw= 0;
#endif

void BoardWidget::redraw()
{
    #if PERF_REDRAW
    ++num_redraw;
    cout << "test redraw BoardWidget"<< num_redraw<< endl;
    #endif

    cout << "redraw BoardWidget"<< endl;

    if (!buffer->isNull()){
        delete(buffer);
    }
    buffer = new QImage(board->width() * DRAW_SCALE, board->height() * DRAW_SCALE, QImage::Format_ARGB32);

    drawBoard();
    update();	// TODO apparemment non utile, update fait resize
}

// ###################
/*** 		Events 	***/
// ##################
void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void BoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void BoardWidget::resizeEvent(QResizeEvent *event)
{
    int max_width=  event->size().width() / board->width();
    int max_height= event->size().height() / board->height();
    cell_size= min(max_height, max_width);
    redraw();
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    std::cout << "BoardWidget_paintEvent : affichage plateau"<< std::endl;
    QPainter paint(this);
    paint.scale(cell_size/(DRAW_SCALE), cell_size/(DRAW_SCALE));
    paint.drawImage(0, 0, *buffer);
}
