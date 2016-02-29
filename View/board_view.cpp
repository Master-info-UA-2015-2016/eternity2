#include "board_view.h"

#define DRAW_SCALE 16.0

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

void BoardWidget::init_board(Board *b)
{
    board= b;
    int w_tmp = width() / b->getConfig().width();
    int h_tmp = height() / b->getConfig().height();

    if(w_tmp < h_tmp)
        cell_size = w_tmp;
    else
        cell_size = h_tmp;

}

// ########################
/***		Affichages	***/
// ########################

//void BoardWidget::drawPiece(const PieceView* p)
//{
//    //        QVector<QPointF> tri_points(3);
//    //        tri_points.push_back(QPointF(0.0, 0.0));
//    //        tri_points.push_back(QPointF(-1.5, -1.5));
//    //        tri_points.push_back(QPointF(0.0, -3.0));

//    //        QPolygonF triangle(tri_points);

//    QPainterPath path(QPointF(0.0, 0.0));
//    path.lineTo(QPointF(-1.5, -1.5));
//    path.lineTo(QPointF(0.0, -3.0));
//    //        path.addPolygon(triangle);

//    bufferPainter->fillPath(path, QBrush(motif->get_color_ext()));
//    bufferPainter->fillRect(colonne *3 +1, ligne *3 +1, 1, 1, motif->get_color_int());
//    #if DEBUG_TMATRICE
//    cout <<"draw piece ; ";
//    #endif
//}

void BoardWidget::drawPiece(int column, int line, int motif[4])
{
    QPointF top(column* DRAW_SCALE,      line* DRAW_SCALE);
    QPointF middle(column * DRAW_SCALE,           (line + 3.0) * DRAW_SCALE);
    QPointF bottom(column + 6.0, line + 6.0);

    bufferPainter->begin(buffer); // TODO Temporaire, à déplacer pour performance

//        QVector<QPointF> tri_points(3);
//        tri_points.push_back(top);
//        tri_points.push_back(middle);
//        tri_points.push_back(bottom);

//        QPolygonF triangle(tri_points);
//    QPainterPath path;
//    path.addPolygon(triangle);

//    QPainterPath path(QPointF(column, line));
    QPainterPath path1(top);           // Coin en haut à gauche
        path1.lineTo(middle); // Coin milieu droit
        path1.lineTo(bottom);  // Coin en bas à gauche
        path1.lineTo(top);          // Coin en haut à gauche
    for (int i= 0; i < 4; ++i) {
        Motif colors= get_color(motif[i]);
        bufferPainter->fillPath(path1, QBrush(*colors.get_color_int()));
        bufferPainter->fillRect(column* DRAW_SCALE , (line +1)* DRAW_SCALE, DRAW_SCALE, DRAW_SCALE,
                                *colors.get_color_ext());
//        bufferPainter->rotate(10.0);
    }

    #if DEBUG_TMATRICE
    cout <<"draw piece ; ";
    #endif
//    bufferPainter->rotate();

    bufferPainter->end(); // TODO Temporaire, à déplacer pour performance

}

void BoardWidget::drawBoard()
{
    /*
    bufferPainter->begin(buffer);

    int current_height, current_width;
    for(int i= 0; i < board->height() * board->width(); ++i){
        current_width= 1 + i % board->width();
        current_height= 1 + i / board->height();
        pair<int, int> piece= board->getConfig().getPiece(current_width, current_height);

//        for( vector< Piece* >::const_iterator j( ligne->begin() ); j!=ligne->end(); ++j){
//            if ((*j) != NULL){
                // TODO Decommenter
//                Piece* piece= *j;
//
//                // On récupère le motif de la pièce
//                int ind_motif= piece->get_motif();
//                Motif* motif= setColor(ind_motif);
//
//                drawPiece(current_width, current_height, motif);
//            }
//            else {
//                drawCell(current_width, current_height);
//            }

            // Incrémentation des positions des Cells
//        }
        #if DEBUG_TMATRICE
        cout << endl;
        #endif
    }

    bufferPainter->end();

    #if DEBUG_TMATRICE
    cout <<"fin draw forest ; "<< endl;
    #endif
//    } // FIN_Dessin d'image
*/

}

// Test perf
#if PERF_REDRAW
int num_redraw= 0;
#endif

void BoardWidget::redraw()
{
    /*
    #if PERF_REDRAW
    ++num_redraw;
    cout << "test redraw BoardWidget"<< num_redraw<< endl;
    #endif

    cout << "redraw BoardWidget"<< endl;

    if (!buffer->isNull()){
        delete(buffer);
    }
    buffer = new QImage(board->width() *3 * DRAW_SCALE, board->height() *3 * DRAW_SCALE, QImage::Format_ARGB32);

    drawBoard();
//    drawChanged();
    update();	// TODO apparemment non utile, update fait resize
    */
}

/**
  * A partir d'un id correspondant aux couleurs d'un motif, créé et retourne le motif (unique) associé
  * @author Antoine
  */
Motif BoardWidget::get_color(int id)
{
    Motif motif_res(Black, Black);
    switch(id){
        case Black_Black:
            motif_res.set_colors(Black, Black);
            break;
        case Gray_Brown:
            motif_res.set_colors(Gray, Brown);
            break;
        case Pink_Brown:
            motif_res.set_colors(Pink, Brown);
            break;
        case Red_Brown:
            motif_res.set_colors(Red, Brown);
            break;
        case Yellow_Brown:
            motif_res.set_colors(Yellow, Brown);
            break;
        case LightGreen_Brown:
            motif_res.set_colors(LightGreen, Brown);
            break;
        case LightBlue_Brown:
            motif_res.set_colors(LightBlue, Brown);
            break;
        case Purple_Brown:
            motif_res.set_colors(Purple, Brown);
            break;
            //fin full brown - 8 couleurs

        case Gray_Orange:
            motif_res.set_colors(Gray, Orange);
            break;
        case Pink_Orange:
            motif_res.set_colors(Pink, Orange);
            break;
        case Red_Orange:
            motif_res.set_colors(Red, Orange);
            break;
        case Yellow_Orange:
            motif_res.set_colors(Yellow, Orange);
            break;
        case LightGreen_Orange:
            motif_res.set_colors(LightGreen, Orange);
            break;
        case DarkGreen_Orange:
            motif_res.set_colors(DarkGreen, Orange);
            break;
        case LightBlue_Orange:
            motif_res.set_colors(LightBlue, Orange);
            break;
        case DarkBlue_Orange:
            motif_res.set_colors(DarkBlue, Orange);
            break;
        case Purple_Orange:
            motif_res.set_colors(Purple, Orange);
            break;
        //fin full Orange - 17 couleurs au total

        case Gray_DarkGreen:
            motif_res.set_colors(Gray, DarkGreen);
            break;
        case Pink_DarkGreen:
            motif_res.set_colors(Pink, DarkGreen);
            break;
        case Red_DarkGreen:
            motif_res.set_colors(Red, DarkGreen);
            break;
        case Yellow_DarkGreen:
            motif_res.set_colors(Yellow, DarkGreen);
            break;
        case LightBlue_DarkGreen:
            motif_res.set_colors(LightBlue, DarkGreen);
            break;
        case DarkBlue_DarkGreen:
            motif_res.set_colors(DarkBlue, DarkGreen);
            break;
        case Purple_DarkGreen:
            motif_res.set_colors(Purple, DarkGreen);
            break;
        //fin full DarkGreen - 24 couleurs au total

        //si pair de couleurs non reconnue, motif blanc
        default:
            motif_res.set_colors(White, White);
            break;
    }//fin switch

    return motif_res;
}

// ###################
/*** 		Events 	***/
// ##################

void BoardWidget::resizeEvent(QResizeEvent *event)
{
    cell_size= event->size().height() / board->height();
    redraw();
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    std::cout << "BoardWidget_paintEvent : affichage plateau"<< std::endl;
    QPainter paint(this);
//    paint.scale(cell_size/(3 * DRAW_SCALE), cell_size/(3 * DRAW_SCALE));
    paint.drawImage(0, 0, *buffer);
}
