#ifndef KBOARD_H
#define KBOARD_H

#include <QGraphicsView>
#include <QTimeLine>
#include <QMap>

class kCardItem;

class kBoard : public QGraphicsView
{
	Q_OBJECT
	
public:
	kBoard(const int& gridX = 5, const int& gridY = 5, QWidget* parent = 0);
	virtual ~kBoard();
	
	virtual QSize						sizeHint() const;

//_________________________________________________________________________
//METHOD
private:
	void								createItems();
	void								createScene();
	void								initBoardParameters();
//SELECTION
	QPointF								posForLocation( int x, int y ) const; //return the QPointF position for a X,Y position in the grid
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
	QTimeLine							*_mFlipTimeLine;
	QTimeLine							*_mSelectionTimeLine;

//GRID
	QSize								_mGridSize;

//items
	kCardItem							*_mContainerItem;
	kCardItem							*_mSelectionItem;
	QMap<int, QMap<int, kCardItem*> >	_mItems;

//SCENE
    QGraphicsScene						*_mScene;
	
//SELECTION
	int									_mSelectedX, _mSelectedY;

};

#endif // KBOARD_H
