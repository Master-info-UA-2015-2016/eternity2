#include "board_view.h"

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
}

// ########################
/***		Affichages	***/
// ########################
void BoardWidget::drawCell(int column, int line)
{
//    buffer = new QImage(100, 100, QImage::Format_ARGB32); // TODO Temporaire, à déplacer

    cout <<"draw cell : "<< column<< " ; " << line<< endl ;
    bufferPainter->begin(buffer); // TODO Temporaire, à déplacer pour performance
    bufferPainter->fillRect(column, line, 3, 3, Qt::white);
//    #if DEBUG_TMATRICE
    cout <<"draw cell : "<< column<< " ; " << line<< endl ;
//    #endif
    bufferPainter->end(); // TODO Temporaire, à déplacer pour performance
    update();
}

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

void BoardWidget::drawPiece(int column, int line, Motif* motif)
{
    //        QVector<QPointF> tri_points(3);
    //        tri_points.push_back(QPointF(0.0, 0.0));
    //        tri_points.push_back(QPointF(-1.5, -1.5));
    //        tri_points.push_back(QPointF(0.0, -3.0));

    //        QPolygonF triangle(tri_points);

    QPainterPath path(QPointF(0.0, 0.0));
    path.lineTo(QPointF(-1.5, -1.5));
    path.lineTo(QPointF(0.0, -3.0));
    //        path.addPolygon(triangle);

//    bufferPainter->fillPath(path, QBrush(*(motif->get_color_ext())));
    bufferPainter->fillPath(path, QBrush(Qt::red));
//    bufferPainter->fillRect(column *3 +1, line *3 +1, 1, 1, *(motif->get_color_int()));
    bufferPainter->fillRect(column *3 +1, line *3 +1, 1, 1,     Qt::blue);
    #if DEBUG_TMATRICE
    cout <<"draw piece ; ";
    #endif
}


//void BoardWidget::drawList(std::map<Cell*, Coordinates> cells){

//    for( map< Cell *, Coordinates>::const_iterator j( cells->begin() ); j != cells->end(); ++j){
//        if (j.first().has_piece())
//            drawPiece(*j);
//        else drawCell(j.second().col, j.second().row);
//    }
//    cells->clear();
//}

void BoardWidget::drawBoard()
{
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
}

//bool PiecesWidget::tryDrawPicture()
//{
//    if (!pictureForest->isNull()){
//        bufferPainter->begin(buffer);
//        bufferPainter->drawImage(0, 0, *pictureForest);
//        bufferPainter->end();

//        return true;
//    }
//    else return false;
//}

//bool PiecesWidget::tryDrawPictureBoard()
//{
//    // essai de dessin de l'image de fond, si présente
//    if (tryDrawPicture()){
//        // si il y a une image de fond, on ne dessine pas les arbres "neutres"

//        bufferPainter->begin(buffer);
//        int current_hauteur= 0;
//        for(int i=0; i<forest->height(); ++i){
//            // On ne passe pas la hauteur de la grille mais le nombre de colonne*taille de colonne pour
//            // éviter la petite zone en bas de grille
//            vector< Cell* >* ligne= (*forest)[i];

//            int current_largeur= 0;
//            for( vector< Cell* >::const_iterator j( ligne->begin() ); j!=ligne->end(); ++j){
//                Cell* cell= *j;
//                if(cell->has_piece()){
//                    // On vérifie ici si l'arbre a recu un retardateur
//                    // i.e son coefficient est inférieur à 1
//                    if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1){
//                        setColor(BlueTrans);
//                        drawCell(current_largeur, current_hauteur);
//                    }
//                }
//                else {
//                    if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1)
//                        setColor(Orange);
//                    else setColor(Red);

//                    drawCell(current_largeur, current_hauteur);
//                }

//                // Incrémentation des positions des Cells
//                current_largeur += 1;
//            }
//            #if DEBUG_TMATRICE
//            cout << endl;
//            #endif
//            current_hauteur += 1;
//        }

//        bufferPainter->end();

//        return true;
//    }
//    else return false;
//}


//void BoardWidget::drawChanged()
//{
//    bufferPainter->begin(buffer);

////    setColor(Red);
//    drawList(board->getPlaced());
//    board->clearPlaced();

////    setColor(Qt::White);
//    drawList(board->getUnplaced());
//    board->clearUnplaced();

//    bufferPainter->end();
//}

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
    buffer = new QImage(board->width() *3, board->height() *3, QImage::Format_ARGB32);

    drawBoard();
//    drawChanged();
    update();	// TODO apparemment non utile, update fait resize
}

// ###################
/*** 		Events 	***/
// ##################

void BoardWidget::mousePressEvent(QMouseEvent *event)
{

}

void BoardWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

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
    paint.scale(cell_size/3, cell_size/3);
    paint.drawImage(0, 0, *buffer);
}
