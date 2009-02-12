#ifndef KCARDITEM_H
#define KCARDITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class QGraphicsProxyWidget;

class kCardItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kCardItem( const QRectF& rect, const QBrush& brush);
	virtual ~kCardItem();
	virtual QRectF boundingRect() const;
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
    
//_________________________________________________________________________
//METHOD
public:
	qreal opacity() const;
	void setOpacity( qreal opacity );
    void setPixmap( const QPixmap& pixmap );

//_________________________________________________________________________
//MEMBERS
private:
	QBrush								_mBrush;
    qreal								_mLastVal;
    qreal								_mOpacity;
    QPixmap								_mPixmap;
	QPixmap								_mSourcePixmap; //first pixmap assignment
	
protected:
	void keyPressEvent( QKeyEvent* event );
    void keyReleaseEvent( QKeyEvent* event );
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
	void returnCardItem(kCardItem*);
};

#endif // KCARDITEM_H
