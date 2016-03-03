#include "board_view.h"

#define DRAW_SCALE  32.0
#define SQUARE_COEF_INVERSE   4.0

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
void BoardWidget::drawMotif(const QPainterPath& path, const QPointF& square_pos, const Motif &colors)
{
#if DEBUG_DRAW_COLORS
    cout<< colors<< endl;
#endif
    bufferPainter->fillPath(path, *(colors.get_color_ext()));
    bufferPainter->fillRect(square_pos.x() * DRAW_SCALE , square_pos.y() * DRAW_SCALE,
                            DRAW_SCALE / SQUARE_COEF_INVERSE, DRAW_SCALE / SQUARE_COEF_INVERSE,
                            *(colors.get_color_int()) );
}

void BoardWidget::drawPiece(int column, int row, const PairColors motifs[])
{
    QPointF top_left(column * DRAW_SCALE,            row * DRAW_SCALE);
    QPointF middle((column +0.5) * DRAW_SCALE,      (row +0.5) * DRAW_SCALE);
    QPointF bottom_left(column * DRAW_SCALE,        (row +1.0) * DRAW_SCALE);
    QPointF top_right((column +1.0) * DRAW_SCALE,    row * DRAW_SCALE);
    QPointF bottom_right((column + 1.0) * DRAW_SCALE,(row +1.0) * DRAW_SCALE);

    // Triangle en bas
    QPainterPath path0(bottom_right);   // En haut à gauche
        path0.lineTo(bottom_left);      // En haut à droite
        path0.lineTo(middle);           // Milieu
        path0.lineTo(bottom_right);     // En haut à gauche
    // Triangle de gauche
    QPainterPath path1(top_left);   // En haut à gauche
        path1.lineTo(middle);       // Milieu
        path1.lineTo(bottom_left);  // En bas à gauche
        path1.lineTo(top_left);     // En haut à gauche
    // Triangle en haut
    QPainterPath path2(top_left);   // En haut à gauche
        path2.lineTo(top_right);    // En haut à droite
        path2.lineTo(middle);       // Milieu
        path2.lineTo(top_left);     // En haut à gauche
    // Triangle à droite
    QPainterPath path3(top_right);  // En haut à gauche
        path3.lineTo(bottom_right); // En haut à droite
        path3.lineTo(middle);       // Milieu
        path3.lineTo(top_right);    // En haut à gauche

    drawMotif(path0,
            *(new QPointF(column + (0.5)*(1 -1/SQUARE_COEF_INVERSE),    row + 1 -1/SQUARE_COEF_INVERSE)),
            Motif(motifs[0]));
    drawMotif(path1,
            *(new QPointF(column + 0.0, row + (1/2.0)*(1 -1/SQUARE_COEF_INVERSE))),
            Motif(motifs[1]));
    drawMotif(path2,
            *(new QPointF(column + (0.5)*(1 -1/SQUARE_COEF_INVERSE),    row + 0.0)),
            Motif(motifs[2]));
    drawMotif(path3,
            *(new QPointF(column + 1 -1/SQUARE_COEF_INVERSE,    row + (0.5)*(1 -1/SQUARE_COEF_INVERSE))),
            Motif(motifs[3]));
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

        PairColors* colors= board->getConfig().getRotatedMotif(current_width, current_height);
        // On affiche la pièce à la position courante, avec son motif
#if DEBUG_DRAW_COLORS
        cout<< "Piece en position "<< current_width<< ";"<< current_height<< " : "<< endl;
#endif
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

#if DEBUG_PAINT
    cout << "redraw BoardWidget"<< endl;
#endif

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
#if DEBUG_PAINT
    cout << "BoardWidget_paintEvent : affichage plateau"<< std::endl;
#endif
    QPainter paint(this);
    paint.scale(cell_size/(DRAW_SCALE), cell_size/(DRAW_SCALE));
    paint.drawImage(0, 0, *buffer);
}
