#include "pieceswidget.h"

using namespace std;

PiecesWidget::PiecesWidget(QWidget *parent) : QWidget(parent)
{

}


// ########################
/***		Affichages	***/
// ########################
void PiecesWidget::drawCell(int colonne, int ligne)
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

    bufferPainter->fillPath(path, QBrush(Qt::red));
    bufferPainter->fillRect(colonne *3 +1, ligne *3 +1, 1, 1, Qt::blue);
    #if DEBUG_TMATRICE
    cout <<"draw cell ; ";
    #endif
}

void PiecesWidget::drawPiece(const PieceView* p)
{
// 	drawCell(ab->getPos().col, ab->getPos().row);
    bufferPainter->fillRect(p->getPos().col, p->getPos().row, 1, 1, *(color));
    #if DEBUG_TMATRICE
    cout <<"draw tree ; "<< p->getPos().col << p->getPos().row ;
    #endif
}

void PiecesWidget::drawList( list< PieceView* > * pieces){

    for( list< PieceView * >::const_iterator j( pieces->begin() ); j != pieces->end(); ++j){
        drawPiece(*j);
    }
    pieces->clear();
}

void PiecesWidget::drawBoard()
{
    // essai de dessin de l'image de fond, et de la foret, si présente
//    if (!tryDrawPictureForest()){   // Dessin d'image
        // si il n"y a oas d'image, on dessine toute la foret dont les arbre

        bufferPainter->begin(buffer);

        int current_hauteur= 0;
        for(int i=0; i < board->height(); ++i){
            // On ne passe pas la hauteur de la grille mais le nombre de colonne*taille de colonne pour
            // éviter la petite zone en bas de grille
            vector< Cell* >* ligne= (*board)[i];

            int current_largeur= 0;
            for( vector< Cell* >::const_iterator j( ligne->begin() ); j!=ligne->end(); ++j){
                Cell* cell= *j;

                if(cell->has_piece()){

//                    if (pictureForest->isNull()){

                            // Il faut ici vérifier l'essence de l'arbre pour lui attribuer une variante de vert
//                            const Essence* ess= dynamic_cast < Piece* >(cell)->getEssence();
//                            getColor(...)
//                            setColor(...);

                        drawCell(current_largeur, current_hauteur);
//                    }
                }
                else {
//                    setColor(Qt::white);

                    drawCell(current_largeur, current_hauteur);
                }

                // Incrémentation des positions des Cells
                current_largeur += 1;
            }
            #if DEBUG_TMATRICE
            cout << endl;
            #endif
            current_hauteur += 1;
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


void PiecesWidget::drawChanged()
{
    bufferPainter->begin(buffer);

//    setColor(Red);
    drawList(board->getPlaced());
    board->clearPlaced();

//    setColor(Qt::White);
    drawList(board->getUnplaced());
    board->clearUnplaced();

    bufferPainter->end();
}

// Test perf
#if PERF_REDRAW
int num_redraw= 0;
#endif

void PiecesWidget::redraw()
{
    #if PERF_REDRAW
    ++num_redraw;
    cout << "test redraw PiecesWidget"<< num_redraw<< endl;
    #endif

    if (!buffer->isNull()){
        delete(buffer);
    }
    buffer = new QImage(board->width(), board->height(), QImage::Format_ARGB32);

    drawBoard();
    drawChanged();
    update();	// TODO apparemment non utile, update fait resize
}
