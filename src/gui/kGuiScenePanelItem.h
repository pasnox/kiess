#ifndef KGUISCENEPANELITEM_H
#define KGUISCENEPANELITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class kEmbeddedWidget;
class kGuiScenePanel;

class kGuiScenePanelItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kGuiScenePanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget = 0 );
	virtual ~kGuiScenePanelItem();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
	virtual QRectF boundingRect() const;

	void setPixmap( const QPixmap& pixmap );
	
	void setWidget( kEmbeddedWidget* widget );
	kEmbeddedWidget* widget() const;

	qreal opacity() const;
	void setOpacity( qreal opacity );
	
	kGuiScenePanel* panel() const;
	bool isAnimate() const;

protected:
	QBrush mBrush;
	QPixmap mPixmap;
	QTimeLine mAnimationTimeLine;
	qreal mLastVal;
	qreal mOpacity;
	kEmbeddedWidget* mEmbeddedWidget;
	
	void keyPressEvent( QKeyEvent* event );
	void mousePressEvent( QGraphicsSceneMouseEvent* event );

private slots:
	void animationTimeLineChanged( qreal value );

signals:
	void activated();
};

#endif // KGUISCENEPANELITEM_H
