#ifndef KPANELITEM_H
#define KPANELITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class QGraphicsProxyWidget;

class kPanelItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kPanelItem( const QRectF& rect, const QBrush& brush, QWidget* embeddedWidget = 0 );
	virtual ~kPanelItem();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
    virtual QRectF boundingRect() const;

    void setPixmap( const QPixmap& pixmap );

    qreal opacity() const;
    void setOpacity( qreal opacity );

protected:
	QBrush mBrush;
    QPixmap mPixmap;
    QTimeLine mTimeLine;
    qreal mLastVal;
    qreal mOpacity;
	QGraphicsProxyWidget* mProxyWidget;
	
	void keyPressEvent( QKeyEvent* event );
    void keyReleaseEvent( QKeyEvent* event );

private slots:
    void updateValue( qreal value );

signals:
	void activated();
};

#endif // KPANELITEM_H
