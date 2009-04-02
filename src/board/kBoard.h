#ifndef KBOARD_H
#define KBOARD_H

#include "kBoardDef.h"

#include <QGraphicsView>
#include <QMap>

class kCardItem;
class QDir;
class QTimeLine;

class kBoard : public QGraphicsView
{
    Q_OBJECT

public:
    kBoard(const int& gridX = 6, const int& gridY = 4, QWidget* parent = 0);
    virtual								~kBoard();

    virtual QSize                                                       sizeHint() const;

    //_________________________________________________________________________
    //METHOD
private:
    void								createItems();
    //ONLY FOR DEBUG
    //STORE CARD PICTURE IN ITEMS
    QStringList                                                         createListPixmap(const QDir& directory);

    void								createScene();
    void								initBoardParameters();
    //Scene/Grid coordinate computation
    QPointF								locationForPos( int x, int y ) const; //return the QPointF position in the grid referential with a X,Y scene position
    QPointF								posForLocation( int x, int y ) const; //return the QPointF position in scene referential with X,Y position in the grid
    //SELECTION
    void 								setCurrentItem( int x, int y, bool animate ); //Set the currentItem and move the _mSelectionItem

private slots:
    //SELECTION
    void								selectedCardItem(kCardItem*);//connect to the cardItem mousePressEvent
    //ANIMATION
    void								updateSelectionStep(qreal val);//Animation, move the _mSelectionItem to the next selected item

protected:
    //Events
    void								resizeEvent( QResizeEvent* event );

    //_________________________________________________________________________
    //MEMBERS
private:
    //ANIMATION
    QPointF								_mEndPos;
    QPointF								_mStartPos;

    QTimeLine                                                           *_mSelectionTimeLine;

    //GRID
    QSize								_mGridSize;

    //items
    kCardItem                                                           *_mContainerItem;
    QStringList                                                         _mListOfPixmap;
    kCardItem                                                           *_mSelectionItem;
    kCardItem                                                           *_previousItem; //previous selected item
    QMap<int, QMap<int, kCardItem*> >	_mItems;

    //SCENE
    QGraphicsScene                                                      *_mScene;

    //SELECTION
    int									_mSelectedX, _mSelectedY;

    //MODE
    ViewMode::BoardViewMode				_mboardViewMode;
};

#endif // KBOARD_H
