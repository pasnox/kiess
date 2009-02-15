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
	virtual QRectF						boundingRect() const;
	virtual void						paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
    
//_________________________________________________________________________
//METHOD
public:
	qreal opacity() const;
	void setOpacity( qreal opacity );
    void setPixmap( const QPixmap& pixmap );

private slots:
	void								updateValue( qreal value );
	void								finishedRotation();

//_________________________________________________________________________
//MEMBERS
private:
	QBrush								_mBrush;
	bool								_mChangePicture; //Flag, change picture when card rotate by 90�
	QTimeLine							_mFlipTimeLine; //Rotation time line
    qreal								_mLastVal;
    qreal								_mOpacity;
    QPixmap								_mPixmap; //current pixmap
	QPixmap								_mSourcePixmap; //first pixmap assignment

//EVENT
protected:
	void								keyPressEvent( QKeyEvent* event );
    void								keyReleaseEvent( QKeyEvent* event );
	void								mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
	void								returnCardItem(kCardItem*); //return cardItem to the view
};

#endif // KCARDITEM_H
