#ifndef KPANEL_H
#define KPANEL_H

#include <QGraphicsView>
#include <QTimeLine>
#include <QMap>

class kPanelItem;

class kPanel : public QGraphicsView
{
	Q_OBJECT
	
public:
	kPanel( QWidget* parent = 0 );
	virtual ~kPanel();
	
	virtual QSize sizeHint() const;
	bool canFlip() const;
	bool canMove() const;
	bool isKeyPad( QKeyEvent* event ) const;

protected:
	QGraphicsScene* mScene;
	kPanelItem* mContainerItem;
	kPanelItem* mBackItem;
	kPanelItem* mSelectionItem;
	QSize mGridSize;
	QMap<int, QMap<int, kPanelItem*> > mItems;
	int mSelectedX, mSelectedY;
	QTimeLine* mSelectionTimeLine;
	QTimeLine* mFlipTimeLine;
	QPointF mSelectionStart;
	QPointF mSelectionEnd;
	qreal mContainerRotationX, mContainerRotationY;
	bool mFlipped;
	bool mFlipLeft;
	
	void keyPressEvent( QKeyEvent* event );
	void resizeEvent( QResizeEvent* event );
	
	QPointF posForLocation( int x, int y ) const;
	void setCurrentItem( int x, int y, bool animate );

protected slots:
	void updateSelectionStep( qreal val );
	void updateFlipStep( qreal val );
	void flip();

private:
	QGraphicsWidget *splash;
};

#endif // KPANEL_H
