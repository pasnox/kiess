#include "kGuiScenePanelItem.h"
#include "kEmbeddedWidget.h"
#include "kGuiScenePanel.h"

#include <QPainter>
#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>

#include <QDebug>

kGuiScenePanelItem::kGuiScenePanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget )
	: QObject( 0 ), QGraphicsRectItem( rect ),
	mBrush( brush ),
	mAnimationTimeLine( 500, this ),
	mLastVal( 0 ),
	mEmbeddedWidget( embeddedWidget ),
	mProxyWidget( 0 )
{
	connect( &mAnimationTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( animationTimeLineChanged( qreal ) ) );
	connect( &mAnimationTimeLine, SIGNAL( finished() ), this, SIGNAL( activated() ) );
}

kGuiScenePanelItem::~kGuiScenePanelItem()
{
}

void kGuiScenePanelItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	Q_UNUSED( options );
	Q_UNUSED( widget );
	
	QTransform x = painter->worldTransform();
	x.rotate( -( 360 *mLastVal ) );
	QLineF unit = x.map( QLineF( 0, 0, 1, 1 ) );
	
	if ( unit.p1().x() > unit.p2().x() || unit.p1().y() > unit.p2().y() )
	{
		if ( mProxyWidget && mProxyWidget->isVisible() )
		{
			mProxyWidget->hide();
			mProxyWidget->setGeometry( rect() );
		}
		
		return;
	}
	
	if ( mProxyWidget && !mProxyWidget->isVisible() )
	{
		mProxyWidget->show();
		mProxyWidget->setFocus();
	}
	
	if ( mProxyWidget && mProxyWidget->pos() != QPoint() )
	{
		mProxyWidget->setGeometry( boundingRect().adjusted( 75, 75, -75, -75 ) );
	}
	
	painter->setOpacity( 1 );
	painter->setPen( Qt::NoPen );
	painter->setBrush( QColor( 0, 0, 0, 64 ) );
	painter->drawRoundRect( rect().translated( 2, 2 ) );

	if ( !mProxyWidget || !mProxyWidget->widget() )
	{
		QLinearGradient gradient( rect().topLeft(), rect().bottomRight() );
		const QColor col = mBrush.color();
		gradient.setColorAt( 0, col );
		gradient.setColorAt( 1, col.dark( int( 200 +mLastVal *50 ) ) );
		painter->setBrush( gradient );
	}
	else
	{
		painter->setBrush( mBrush );
	}

	painter->setPen( QPen( Qt::black, 1 ) );
	painter->drawRoundRect( rect() );
	
	if ( !mPixmap.isNull() )
	{
		painter->scale( 1.95, 1.95 );
		painter->drawPixmap( -mPixmap.width() /2, -mPixmap.height() /2, mPixmap );
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

kGuiScenePanel* kGuiScenePanelItem::panel() const
{
	return parentItem() ? static_cast<kGuiScenePanel*>( parentItem() ) : 0;
}

bool kGuiScenePanelItem::isAnimate() const
{
	return mAnimationTimeLine.state() == QTimeLine::Running;
}

void kGuiScenePanelItem::loadWidget( kEmbeddedWidget* widget )
{
	Q_ASSERT( widget );
	
	if ( !mProxyWidget )
	{
		mProxyWidget = new QGraphicsProxyWidget( this );
		mProxyWidget->setFocusPolicy( Qt::StrongFocus );
	}
	
	mProxyWidget->setWidget( widget );
	mBrush = widget->palette().window();
	widget->loadDatas();
	
	connect( widget, SIGNAL( rejected() ), panel(), SLOT( item_rejected() ) );
	connect( widget, SIGNAL( accepted() ), panel(), SLOT( item_accepted() ) );
}

void kGuiScenePanelItem::unloadWidget()
{
	Q_ASSERT( mProxyWidget );
	Q_ASSERT( mProxyWidget->widget() );
	
	disconnect( mProxyWidget->widget(), SIGNAL( rejected() ), panel(), SLOT( item_rejected() ) );
	disconnect( mProxyWidget->widget(), SIGNAL( accepted() ), panel(), SLOT( item_accepted() ) );
	
	mProxyWidget->setWidget( 0 );
	
	emit activated();
}

void kGuiScenePanelItem::activate()
{
	if ( !isAnimate() )
	{
		mAnimationTimeLine.start();
	}
}

void kGuiScenePanelItem::animationTimeLineChanged( qreal value )
{
	mLastVal = value;
	QTransform transform;
	
	// rotation
	transform.rotate( 360 *value, Qt::ZAxis );
	
	// scale
	if ( value <= 0.5 )
	{
		transform.scale( 1- ( 1 *value ), 1 -( 1 *value ) );
	}
	else
	{
		transform.scale( 1 *value, 1 *value );
	}
	
	setTransform( transform );
}
