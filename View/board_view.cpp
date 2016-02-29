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

void BoardWidget::drawPiece(int column, int line, int motif[4])
{
    bufferPainter->begin(buffer); // TODO Temporaire, à déplacer pour performance

//        QVector<QPointF> tri_points(3);
//        tri_points.push_back(QPointF(column, line));
//        tri_points.push_back(QPointF(column, line + 12.0));
//        tri_points.push_back(QPointF(column + 6.0, line + 6.0));

//        QPolygonF triangle(tri_points);
//    QPainterPath path;
//    path.addPolygon(triangle);


    bufferPainter->setBrushOrigin(QPointF(column* DRAW_SCALE,      line* DRAW_SCALE));

//    QPainterPath path(QPointF(column, line));
        QPainterPath path1(QPointF(column* DRAW_SCALE,      line* DRAW_SCALE));           // Coin en haut à gauche
        path1.lineTo(QPointF(column * DRAW_SCALE,           (line + 3.0) * DRAW_SCALE )); // Coin milieu droit
        path1.lineTo(QPointF((column + 1.5) * DRAW_SCALE,   (line + 1.5) * DRAW_SCALE));  // Coin en bas à gauche
        path1.lineTo(QPointF(column * DRAW_SCALE,           line * DRAW_SCALE));          // Coin en haut à gauche
    for (int i= 0; i < 4; ++i) {
        bufferPainter->fillPath(path1, QBrush(Qt::red));
        bufferPainter->fillRect(column* DRAW_SCALE , (line +1)* DRAW_SCALE, DRAW_SCALE, DRAW_SCALE,     Qt::blue);
        bufferPainter->rotate(10.0);
    }

//    QPainterPath path2(QPointF( (column +1.5)* DRAW_SCALE, line* DRAW_SCALE));          // Coin en haut à droite
//    path2.lineTo(QPointF( column * DRAW_SCALE,          (line + 3.0) * DRAW_SCALE ));   // Coin milieu gauche
//    path2.lineTo(QPointF((column + 3.0) * DRAW_SCALE,   (line + 1.5) * DRAW_SCALE));    // Coin en bas à droite
//    path2.lineTo(QPointF((column + 3.0) * DRAW_SCALE,    line * DRAW_SCALE));            // Coin en haut à droite
//    bufferPainter->fillPath(path2, QBrush(Qt::yellow));

    #if DEBUG_TMATRICE
    cout <<"draw piece ; ";
    #endif
//    bufferPainter->rotate();

    bufferPainter->end(); // TODO Temporaire, à déplacer pour performance
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
    buffer = new QImage(board->width() *3 * DRAW_SCALE, board->height() *3 * DRAW_SCALE, QImage::Format_ARGB32);

    drawBoard();
//    drawChanged();
    update();	// TODO apparemment non utile, update fait resize
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
    paint.scale(cell_size/(3 * DRAW_SCALE), cell_size/(3 * DRAW_SCALE));
    paint.drawImage(0, 0, *buffer);
}
