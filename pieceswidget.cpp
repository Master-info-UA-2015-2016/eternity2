#include "pieceswidget.h"

PiecesWidget::PiecesWidget(QWidget *parent) : QWidget(parent)
{

}


// ########################
/***		Affichages	***/
// ########################
void FireWidget::drawCell(int colonne, int ligne)
{
    //        QVector<QPointF> tri_points(3);
    //        tri_points.push_back(QPointF(0.0, 0.0));
    //        tri_points.push_back(QPointF(-1.5, -1.5));
    //        tri_points.push_back(QPointF(0.0, -3.0));

    //        QPolygonF triangle(tri_points);

            QPainterPath path(QPointF(0.0, 0.0));
            QPainterPath.lineTo(QPointF(-1.5, -1.5));
            QPainterPath.lineTo(QPointF(0.0, -3.0));
    //        path.addPolygon(triangle);

    bufferPainter->fillPath(path);
    bufferPainter->fillRect(colonne, ligne, 1, 1, *(color));
    #if DEBUG_TMATRICE
    cout <<"draw cell ; ";
    #endif
}

void FireWidget::drawTree(const Arbre* ab)
{
// 	drawCell(ab->getPos().col, ab->getPos().row);
    bufferPainter->fillRect(ab->getPos().col, ab->getPos().row, 1, 1, *(color));
    #if DEBUG_TMATRICE
    cout <<"draw tree ; "<< ab->getPos().col << ab->getPos().row ;
    #endif
}

void FireWidget::drawList( list< Arbre* > * arbres){

    for( list< Arbre * >::const_iterator j( arbres->begin() ); j != arbres->end(); ++j){
        drawTree(*j);
    }
    arbres->clear();
}

void FireWidget::drawForest()
{
    // essai de dessin de l'image de fond, et de la foret, si présente
    if (!tryDrawPictureForest()){
        // si il n"y a oas d'image, on dessine toute la foret dont les arbre

        bufferPainter->begin(buffer);

        int current_hauteur= 0;
        for(int i=0; i<forest->height(); ++i){
            // On ne passe pas la hauteur de la grille mais le nombre de colonne*taille de colonne pour
            // éviter la petite zone en bas de grille
            vector< Cellule* >* ligne= (*forest)[i];

            int current_largeur= 0;
            for( vector< Cellule* >::const_iterator j( ligne->begin() ); j!=ligne->end(); ++j){
                Cellule* cell= *j;

                if( cell->getState() == 0){
                    setColor(Brownie);
                    drawCell(current_largeur, current_hauteur);
                }
                else if(cell->getState() == 1){

                    if (pictureForest->isNull()){
                        // On vérifie ici si l'arbre a recu un retardateur
                        // i.e son coefficient est inférieur à 1
                        if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1)
                            setColor(BlueTrans);
                        else{
                            // Il faut ici vérifier l'essence de l'arbre pour lui attribuer une variante de vert
                            const Essence* ess= dynamic_cast < Arbre* >(cell)->getEssence();
                            setColor(ess);
                        }

                        drawCell(current_largeur, current_hauteur);
                    }

                }
                else if (cell->getState() == 2){
                    if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1)
                        setColor(Orange);
                    else setColor(Red);

                    drawCell(current_largeur, current_hauteur);
                }
                else if (cell->getState() == -1){
                    setColor(Gray);
                    drawCell(current_largeur, current_hauteur);
                }
                else if(cell->getState() == -2){
                    setColor(BrownCut);
                    drawCell(current_largeur,current_hauteur);
                }

                // Incrémentation des positions des cellules
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
    }
}

bool FireWidget::tryDrawPicture()
{
    if (!pictureForest->isNull()){
        bufferPainter->begin(buffer);
        bufferPainter->drawImage(0, 0, *pictureForest);
        bufferPainter->end();

        return true;
    }
    else return false;
}

bool FireWidget::tryDrawPictureForest()
{
    // essai de dessin de l'image de fond, si présente
    if (tryDrawPicture()){
        // si il y a une image de fond, on ne dessine pas les arbres "neutres"

        bufferPainter->begin(buffer);
        int current_hauteur= 0;
        for(int i=0; i<forest->height(); ++i){
            // On ne passe pas la hauteur de la grille mais le nombre de colonne*taille de colonne pour
            // éviter la petite zone en bas de grille
            vector< Cellule* >* ligne= (*forest)[i];

            int current_largeur= 0;
            for( vector< Cellule* >::const_iterator j( ligne->begin() ); j!=ligne->end(); ++j){
                Cellule* cell= *j;
                if(cell->getState() == 1){
                    // On vérifie ici si l'arbre a recu un retardateur
                    // i.e son coefficient est inférieur à 1
                    if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1){
                        setColor(BlueTrans);
                        drawCell(current_largeur, current_hauteur);
                    }
                }
                else if (cell->getState() == 2){
                    if(dynamic_cast < Arbre* >(cell)->getCoeff() < 1)
                        setColor(Orange);
                    else setColor(Red);

                    drawCell(current_largeur, current_hauteur);
                }
                else if (cell->getState() == -1){
                    setColor(Gray);
                    drawCell(current_largeur, current_hauteur);
                }
                else if(cell->getState() == -2){
                    setColor(BrownCut);
                    drawCell(current_largeur,current_hauteur);
                }

                // Incrémentation des positions des cellules
                current_largeur += 1;
            }
            #if DEBUG_TMATRICE
            cout << endl;
            #endif
            current_hauteur += 1;
        }

        bufferPainter->end();

        return true;
    }
    else return false;
}


void FireWidget::drawChanged()
{
    bufferPainter->begin(buffer);

    setColor(Red);
    drawList(forest->getBurned());
    forest->clearBurned();

    setColor(Gray);
    drawList(forest->getCarbonized());
    forest->clearCarbonized();

    setColor(BlueTrans);
    drawList(forest->getDelayed());
    forest->clearDelayed();

    setColor(Orange);
    drawList(forest->getDelayBurned());
    forest->clearDelayBurned();

    setColor(BrownCut);
    drawList(forest->getUprooted());
    forest->clearUprooted();

    bufferPainter->end();
}

// Test perf
#if PERF_REDRAW
int num_redraw= 0;
#endif

void FireWidget::redraw()
{
    #if PERF_REDRAW
    ++num_redraw;
    cout << "test redraw firewidget"<< num_redraw<< endl;
    #endif

    if (!buffer->isNull()){
        delete(buffer);
    }
    buffer = new QImage(forest->width(), forest->height(), QImage::Format_ARGB32);

    drawForest();
    drawChanged();
    update();	// TODO apparemment non utile, update fait resize
}
