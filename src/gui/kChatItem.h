#ifndef KCHATITEM_H
#define KCHATITEM_H

#include <QGraphicsRectItem>

class QGraphicsProxyWidget;
class kChatWidget;

class kChatItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kChatItem( const QRectF& rect, kChatWidget* widget );
	virtual ~kChatItem();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
	virtual QRectF boundingRect() const;

protected:
	QGraphicsProxyWidget* mProxyWidget;
	kChatWidget* mWidget;
};

#endif // KCHATITEM_H
