#ifndef KPANELITEM_H
#define KPANELITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class QGraphicsProxyWidget;
class kEmbeddedWidget;

class kPanelItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kPanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget = 0 );
	virtual ~kPanelItem();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
	virtual QRectF boundingRect() const;

	void setPixmap( const QPixmap& pixmap );
	
	void setWidget( kEmbeddedWidget* widget );
	kEmbeddedWidget* widget() const;

	qreal opacity() const;
	void setOpacity( qreal opacity );

protected:
	QBrush mBrush;
	QPixmap mPixmap;
	QTimeLine mTimeLine;
	qreal mLastVal;
	qreal mOpacity;
	kEmbeddedWidget* mEmbeddedWidget;
	QGraphicsProxyWidget* mProxyWidget;
	
	void keyPressEvent( QKeyEvent* event );
	void keyReleaseEvent( QKeyEvent* event );

private slots:
	void updateValue( qreal value );

signals:
	void activated();
};

#endif // KPANELITEM_H
