#include "kChatItem.h"
#include "kChatWidget.h"

#include <QPainter>
#include <QGraphicsProxyWidget>

kChatItem::kChatItem( const QRectF& rect, kChatWidget* widget )
	: QObject( 0 ), QGraphicsRectItem( rect ),
	mProxyWidget( new QGraphicsProxyWidget( this ) ),
	mWidget( widget )
{
	Q_ASSERT( mWidget );
	
	mProxyWidget->setWidget( widget );
	mProxyWidget->setFocusPolicy( Qt::StrongFocus );
	mProxyWidget->setGeometry( boundingRect().adjusted( 30, 30, -30, -30 ) );
	mProxyWidget->show();
	mProxyWidget->setFocus();
}

kChatItem::~kChatItem()
{
}

void kChatItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	Q_UNUSED( options );
	Q_UNUSED( widget );
	
	painter->setOpacity( 0.8 );
	painter->setPen( Qt::NoPen );
	painter->setBrush( QColor( 0, 0, 0, 64 ) );
	painter->drawRoundRect( rect().translated( 2, 2 ) );

	painter->setPen( QPen( Qt::black, 1 ) );
	painter->drawRoundRect( rect() );
}

QRectF kChatItem::boundingRect() const
{
	qreal penW = 0.5;
	qreal shadowW = 2.0;
	return rect().adjusted( -penW, -penW, penW +shadowW, penW +shadowW );
}
