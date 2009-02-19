#ifndef KGUISCENEPANEL_H
#define KGUISCENEPANEL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimeLine>
#include <QBrush>

class kGuiScenePanelItem;

class kGuiScenePanel : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	friend class kGuiScene;
	
public:
	kGuiScenePanel( const QRectF& rect, const QSize& gridSize, QObject* parent = 0 );
	virtual ~kGuiScenePanel();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
	virtual QRectF boundingRect() const;
	
	kGuiScenePanelItem* item( const QPoint& pos ) const;
	bool isAnimate() const;
	bool isFlipped() const;
	
	kGuiScenePanelItem* currentItem() const;
	void setCurrentItem( const QPoint& pos, bool animate );

public slots:
	void flip();

protected:
	QBrush mBrush;
	QSize mGridSize;
	QMap<int, QMap<int, kGuiScenePanelItem*> > mItems;
	QTimeLine* mSelectionTimeLine;
	QPoint mSelectedPos;
	QPointF mSelectionStart;
	QPointF mSelectionEnd;
	kGuiScenePanelItem* mSelectionItem;
	bool mFlipped;
	bool mFlipLeft;
	qreal mRotationX, mRotationY;
	QTimeLine* mFlipTimeLine;
	
	void initialize();
	QPointF gridPosition( const QPoint& pos ) const;
	bool isKeyPad( QKeyEvent* event ) const;
	void keyPressEvent( QKeyEvent* event );
	void mousePressEvent( QGraphicsSceneMouseEvent* event );

protected slots:
	void selectionTimeLineChanged( qreal value );
	void selectionMoved( const QPointF& pos );
	
	void flipTimeLineChanged( qreal value );
};

#endif // KGUISCENEPANEL_H
