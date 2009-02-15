#include "kGuiScenePanelItem.h"
#include "kEmbeddedWidget.h"
#include "kGuiScenePanel.h"

#include <QPainter>
#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

kGuiScenePanelItem::kGuiScenePanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget )
	: QObject( 0 ), QGraphicsRectItem( rect ),
	mBrush( brush ),
	mAnimationTimeLine( 500, this ),
	mLastVal( 0 ),
	mOpacity( 1 ),
	mEmbeddedWidget( embeddedWidget )
{
	connect( &mAnimationTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( animationTimeLineChanged( qreal ) ) );
}

kGuiScenePanelItem::~kGuiScenePanelItem()
{
}

void kGuiScenePanelItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	QTransform x = painter->worldTransform();

	QLineF unit = x.map(QLineF(0, 0, 1, 1));
	/*
	if (unit.p1().x() > unit.p2().x() || unit.p1().y() > unit.p2().y()) {
		if (mProxyWidget && mProxyWidget->isVisible()) {
			mProxyWidget->hide();
			mProxyWidget->setGeometry(rect());
		}
		return;
	}

	if (mProxyWidget && mProxyWidget->widget() && !mProxyWidget->isVisible()) {
		mProxyWidget->show();
		mProxyWidget->setFocus();
	}
	if (mProxyWidget && mProxyWidget->widget() && mProxyWidget->pos() != QPoint())
		mProxyWidget->setGeometry(boundingRect().adjusted(25, 25, -25, -25));
	*/

	painter->setOpacity(opacity());
	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(0, 0, 0, 64));
	painter->drawRoundRect(rect().translated(2, 2));

	/*
	if (!mProxyWidget || !mProxyWidget->widget() ) {
		QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
		const QColor col = mBrush.color();
		gradient.setColorAt(0, col);
		gradient.setColorAt(1, col.dark(int(200 + mLastVal * 50)));
		painter->setBrush(gradient);
	} else */{
		painter->setBrush(mBrush);
	}

	painter->setPen(QPen(Qt::black, 1));
	painter->drawRoundRect(rect());
	if (!mPixmap.isNull()) {
		painter->scale(1.95, 1.95);
		painter->drawPixmap(-mPixmap.width() / 2, -mPixmap.height() / 2, mPixmap);
	}
}

QRectF kGuiScenePanelItem::boundingRect() const
{
	qreal penW = 0.5;
	qreal shadowW = 2.0;
	return rect().adjusted( -penW, -penW, penW +shadowW, penW +shadowW );
}

void kGuiScenePanelItem::setPixmap( const QPixmap& pixmap )
{
	mPixmap = pixmap;
	
	if ( scene() && isVisible() )
	{
		update();
	}
}

void kGuiScenePanelItem::setWidget( kEmbeddedWidget* widget )
{
	mEmbeddedWidget = widget;
}

kEmbeddedWidget* kGuiScenePanelItem::widget() const
{
	return mEmbeddedWidget;
}

qreal kGuiScenePanelItem::opacity() const
{
	kGuiScenePanelItem* parent = parentItem() ? static_cast<kGuiScenePanelItem*>( parentItem() ) : 0;
	return mOpacity +( parent ? parent->opacity() : 0 );
}

void kGuiScenePanelItem::setOpacity( qreal opacity )
{
	mOpacity = opacity;
	update();
}

kGuiScenePanel* kGuiScenePanelItem::panel() const
{
	return parentItem() ? static_cast<kGuiScenePanel*>( parentItem() ) : 0;
}

bool kGuiScenePanelItem::isAnimationRunning() const
{
	return mAnimationTimeLine.state() == QTimeLine::Running;
}

void kGuiScenePanelItem::keyPressEvent( QKeyEvent* event )
{
	if ( !isAnimationRunning() && mEmbeddedWidget )
	{
		if ( event->key() == Qt::Key_Escape )
		{
			mEmbeddedWidget->reject();
			emit activated();
			return;
		}
		else if ( event->key() == Qt::Key_Return )
		{
			mEmbeddedWidget->accept();
			emit activated();
			return;
		}
	}
	
	if ( event->key() != Qt::Key_Return )
	{
		QGraphicsRectItem::keyPressEvent( event );
		return;
	}
	
	mAnimationTimeLine.stop();
	mAnimationTimeLine.setDirection( QTimeLine::Forward );
	mAnimationTimeLine.start();
}
/*
void kGuiScenePanelItem::keyReleaseEvent( QKeyEvent* event )
{
	//if ( isFlipped() || event->isAutoRepeat() || event->key() != Qt::Key_Return )
	{
		QGraphicsRectItem::keyReleaseEvent( event );
		return;
	}
	
	if ( mAnimateTimeLine.direction() != QTimeLine::Backward )
	{
		mAnimateTimeLine.stop();
		mAnimateTimeLine.setDirection( QTimeLine::Backward );
		mAnimateTimeLine.start();
	}
}
*/
/*
void kGuiScenePanelItem::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
	if ( isFlipped() && canMove() )
	{
		if ( event->button() == Qt::RightButton )
		{
			mEmbeddedWidget->reject();
			emit activated();
			return;
		}
		else if ( event->button() == Qt::LeftButton )
		{
			mEmbeddedWidget->accept();
			emit activated();
			return;
		}
	}
	else if ( !canMove() || event->button() != Qt::LeftButton )
	{
		QGraphicsRectItem::mousePressEvent( event );
		return;
	}
	
	mFlipTimeLine.setDirection( QTimeLine::Forward );
	mFlipTimeLine.start();
}

void kGuiScenePanelItem::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
	if ( isFlipped() || event->button() != Qt::LeftButton )
	{
		QGraphicsRectItem::mouseReleaseEvent( event );
		return;
	}
	
	if ( mFlipTimeLine.direction() != QTimeLine::Backward )
	{
		mFlipTimeLine.stop();
		mFlipTimeLine.setDirection( QTimeLine::Backward );
		mFlipTimeLine.start();
	}
}
*/
void kGuiScenePanelItem::animationTimeLineChanged( qreal value )
{
	mLastVal = value;
	
	QTransform transform;
	transform.scale( 1 -value /10.0, 1 -value /10.0 );
	transform.translate( rect().center().x(), rect().center().y() );
	transform.rotate( 360 *value, Qt::ZAxis );
	transform.translate( rect().left(), rect().top() );
	setTransform( transform );
	
	/*
	if ( mFlipTimeLine.direction() == QTimeLine::Backward && value == 0 && mEmbeddedWidget && !isFlipped() )
	{
		emit activated();
	}
	*/
}
