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
    QPointF top= column* DRAW_SCALE,      line* DRAW_SCALE;
    QPointF middle= column * DRAW_SCALE,           (line + 3.0) * DRAW_SCALE;
    QPointF bottom= (column* DRAW_SCALE,      line* DRAW_SCALE);

    /*
    bufferPainter->begin(buffer); // TODO Temporaire, à déplacer pour performance

//        QVector<QPointF> tri_points(3);
//        tri_points.push_back(top);
//        tri_points.push_back(middle);
//        tri_points.push_back(bottom);

//        QPolygonF triangle(tri_points);
//    QPainterPath path;
//    path.addPolygon(triangle);

    QPainterPath path1(top);           // Coin en haut à gauche
        path1.lineTo(middle); // Coin milieu droit
        path1.lineTo(bottom);  // Coin en bas à gauche
        path1.lineTo(top);          // Coin en haut à gauche
    for (int i= 0; i < 4; ++i) {
        bufferPainter->fillPath(path1, QBrush(Qt::red));
        bufferPainter->fillRect(column* DRAW_SCALE , (line +1)* DRAW_SCALE, DRAW_SCALE, DRAW_SCALE,     Qt::blue);
        bufferPainter->rotate(10.0);
    }

    #if DEBUG_TMATRICE
    cout <<"draw piece ; ";
    #endif
//    bufferPainter->rotate();

    bufferPainter->end(); // TODO Temporaire, à déplacer pour performance
    */
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
  * A partir d'un id, créé et retourne un motif (unique)
  * @author Antoine
  */
/*
Motif* BoardWidget::get_color(int id)
{
    switch(id){
        case 0:
            case Black:
                this->color->setRgb(0,0,0);
                break;
            case Gray:
                this->color->setRgb(128,128,128);
                break;
            case Brown:
                this->color->setRgb(100,50,0);
                break;
            case Orange:
                this->color->setRgb(250,128,0);
                break;
            case Pink:
                this->color->setRgb(250,100,250);
                break;
            case Red:
                this->color->setRgb(255,0,0);
                break;
            case Yellow:
                this->color->setRgb(250,250,0);
                break;
            case LightGreen:
                this->color->setRgb(100,250,100);
                break;
            case DarkGreen:
                this->color->setRgb(0,150,0);
                break;
            case LightBlue:
                this->color->setRgb(100,250,250);
                break;
            case DarkBlue:
                this->color->setRgb(0,0,250);
                break;
            case Purple:
                this->color->setRgb(150,50,250);
                break;
            default :
                this->color->setRgb(255, 255, 255);
            }
        }
}

*/

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
