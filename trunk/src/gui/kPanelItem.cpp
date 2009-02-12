#include "kPanelItem.h"
#include <kEmbeddedWidget.h>

#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QWidget>

kPanelItem::kPanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget )
	: QObject( 0 ), QGraphicsRectItem( rect ),
	mBrush( brush ),
	mTimeLine( 75, this ),
	mLastVal( 0 ),
	mOpacity( 1 ),
	mEmbeddedWidget( embeddedWidget ),
	mProxyWidget( 0 )
{
	connect( &mTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( updateValue( qreal ) ) );
}

kPanelItem::~kPanelItem()
{
}

void kPanelItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	QTransform x = painter->worldTransform();

	QLineF unit = x.map(QLineF(0, 0, 1, 1));
	if (unit.p1().x() > unit.p2().x() || unit.p1().y() > unit.p2().y()) {
		if (mProxyWidget && mProxyWidget->isVisible()) {
			mProxyWidget->hide();
			mProxyWidget->setGeometry(rect());
		}
		return;
	}

	if (mProxyWidget && !mProxyWidget->isVisible()) {
		mProxyWidget->show();
		mProxyWidget->setFocus();
	}
	if (mProxyWidget && mProxyWidget->pos() != QPoint())
		mProxyWidget->setGeometry(boundingRect().adjusted(25, 25, -25, -25));

	painter->setOpacity(opacity());
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(0, 0, 0, 64));
	painter->drawRoundRect(rect().translated(2, 2));

	if (!mProxyWidget) {
		QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
		const QColor col = mBrush.color();
		gradient.setColorAt(0, col);
		gradient.setColorAt(1, col.dark(int(200 + mLastVal * 50)));
		painter->setBrush(gradient);
	} else {
		painter->setBrush(mBrush);
	}

	painter->setPen(QPen(Qt::black, 1));
	painter->drawRoundRect(rect());
	if (!mPixmap.isNull()) {
		painter->scale(1.95, 1.95);
		painter->drawPixmap(-mPixmap.width() / 2, -mPixmap.height() / 2, mPixmap);
	}
}

QRectF kPanelItem::boundingRect() const
{
	qreal penW = 0.5;
	qreal shadowW = 2.0;
	return rect().adjusted(-penW, -penW, penW + shadowW, penW + shadowW);
}

void kPanelItem::setPixmap(const QPixmap &pixmap)
{
	mPixmap = pixmap;
	if (scene() && isVisible())
		update();
}

void kPanelItem::setWidget( kEmbeddedWidget* widget )
{
	if ( widget != mEmbeddedWidget )
	{
		mEmbeddedWidget = widget;
		
		if ( !mEmbeddedWidget )
		{
			if ( mProxyWidget )
			{
				mProxyWidget->setWidget( 0 );
			}
			
			return;
		}
		
		if ( !mProxyWidget )
		{
			mProxyWidget = new QGraphicsProxyWidget( this );
			mProxyWidget->setFocusPolicy( Qt::StrongFocus );
		}
		
		mBrush = mEmbeddedWidget->palette().window();
		mProxyWidget->setWidget( mEmbeddedWidget );
		mProxyWidget->setGeometry( boundingRect().adjusted( 25, 25, -25, -25 ) );
	}
}

kEmbeddedWidget* kPanelItem::widget() const
{
	return mEmbeddedWidget;
}

qreal kPanelItem::opacity() const
{
	kPanelItem *parent = parentItem() ? (kPanelItem *)parentItem() : 0;
	return mOpacity + (parent ? parent->opacity() : 0);
}

void kPanelItem::setOpacity(qreal opacity)
{
	mOpacity = opacity;
	update();
}

void kPanelItem::keyPressEvent( QKeyEvent* event )
{
	if (event->isAutoRepeat()
		|| (mTimeLine.state() == QTimeLine::Running && mTimeLine.direction() == QTimeLine::Forward)) {
		QGraphicsRectItem::keyPressEvent(event);
		return;
	}
	
	if ( mEmbeddedWidget && mEmbeddedWidget->isVisible() )
	{
		if ( event->key() == Qt::Key_Escape )
		{
			mEmbeddedWidget->reject();
			event->ignore();
			return;
		}
		else if ( event->key() == Qt::Key_Return )
		{
			mEmbeddedWidget->accept();
			event->ignore();
			return;
		}
	}
	else if ( event->key() != Qt::Key_Return )
	{
		QGraphicsRectItem::keyPressEvent(event);
		return;
	}

	mTimeLine.stop();
	mTimeLine.setDirection(QTimeLine::Forward);
	mTimeLine.start();
}

void kPanelItem::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() != Qt::Key_Return && event->key() != Qt::Key_Escape) {
		QGraphicsRectItem::keyReleaseEvent(event);
		return;
	}
	mTimeLine.stop();
	mTimeLine.setDirection(QTimeLine::Backward);
	mTimeLine.start();
	
	emit activated();
	qWarning( "activated" );
}

void kPanelItem::updateValue(qreal value)
{
	mLastVal = value;
	if (!mProxyWidget)
		setTransform(QTransform().scale(1 - value / 10.0, 1 - value / 10.0));
	
	if ( mTimeLine.direction() == QTimeLine::Backward && value == 0 )
	{
//		emit activated();
	}
}
