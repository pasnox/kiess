#include "kGuiScenePanel.h"
#include "kGuiScenePanelItem.h"
#include "kEmbeddedWidget.h"
#include "kHelper.h"

#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <math.h>

kGuiScenePanel::kGuiScenePanel( const QRectF& rect, const QSize& gridSize, QObject* parent )
	: QObject( parent ), QGraphicsRectItem( rect ),
	mBrush( QColor( 226, 255, 92, 64 ) ),
	mGridSize( gridSize ),
	mSelectionTimeLine( 250, this ),
	mFlipped( false ),
	mFlipLeft( true ),
	mRotationX( 0 ),
	mRotationY( 0 ),
	mFlipTimeLine( 500, this )
{	
	qreal width = ( rect.width() /(qreal)mGridSize.width() );
	qreal height = ( rect.height() /(qreal)mGridSize.height() );
	
	mSelectionItem = new kGuiScenePanelItem( kHelper::translatedRect( QRectF( 0, 0, width *0.8, height *0.8 ) ), Qt::gray );
	mSelectionItem->setParentItem( this );
	mSelectionItem->setPos( gridPosition( QPoint( 0, 0 ) ) );
	mSelectionItem->setZValue( -1 );
	
	mFlippedItem = new kGuiScenePanelItem( kHelper::translatedRect( rect ), Qt::gray );
	mFlippedItem->setParentItem( this );
	mFlippedItem->setTransform( QTransform().rotate( 180, Qt::YAxis ) );
	
	for ( int x = 0; x < mGridSize.width(); x++ )
	{
		for ( int y = 0; y < mGridSize.height(); y++ )
		{
			kGuiScenePanelItem* item = new kGuiScenePanelItem( kHelper::translatedRect( QRectF( 0, 0, width *0.7, height *0.7 ) ), QColor( 214, 240, 110, 128 ) );
			item->setParentItem( this );
			item->setFlag( QGraphicsItem::ItemIsFocusable );
			item->setPos( gridPosition( QPoint( x, y ) ) );
			
			mItems[ x ][ y ] = item;
			connect( item, SIGNAL( activated() ), this, SLOT( flip() ) );
		}
	}
	
	connect( mFlippedItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	connect( &mSelectionTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( selectionTimeLineChanged( qreal ) ) );
	connect( &mFlipTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( flipTimeLineChanged( qreal ) ) );
}

kGuiScenePanel::~kGuiScenePanel()
{
}

void kGuiScenePanel::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	Q_UNUSED( options );
	Q_UNUSED( widget );

	painter->setOpacity( 1 );
	
	painter->setPen( Qt::NoPen );
	painter->setBrush( QColor( 0, 0, 0, 64 ) );
	painter->drawRoundRect( rect().translated( 2, 2 ) );
	
	painter->setPen( QPen( Qt::black, 1 ) );
	painter->setBrush( mBrush );
	painter->drawRoundRect( rect() );
}

QRectF kGuiScenePanel::boundingRect() const
{
	qreal penW = 0.5;
	qreal shadowW = 2.0;
	return rect().adjusted( -penW, -penW, penW +shadowW, penW +shadowW );
}

kGuiScenePanelItem* kGuiScenePanel::item( const QPoint& pos ) const
{
	return mItems.value( pos.x() ).value( pos.y() );
}

bool kGuiScenePanel::isAnimate() const
{
	return mSelectionTimeLine.state() == QTimeLine::Running;
}

bool kGuiScenePanel::isFlipped() const
{
	return mFlipped;
}

kGuiScenePanelItem* kGuiScenePanel::currentItem() const
{
	return item( mSelectedPos );
}

void kGuiScenePanel::setCurrentItem( const QPoint& pos, bool animate )
{	
	item( pos )->setFocus();
	mSelectedPos = pos;
	
	if ( animate )
	{
		mSelectionTimeLine.stop();
		mSelectionStart = mSelectionItem->pos();
		mSelectionEnd = gridPosition( pos );
		mSelectionTimeLine.start();
	}
	else
	{
		mSelectionTimeLine.stop();
		mSelectionItem->setPos( gridPosition( pos ) );
		mSelectionStart = mSelectionItem->pos();
		selectionMoved( mSelectionStart );
	}
}

void kGuiScenePanel::flip()
{
	kGuiScenePanelItem* item = currentItem();
	
	if ( isAnimate() || ( item && item->isAnimate() ) )
	{
		return;
	}

	if ( mFlipTimeLine.currentValue() == 0 )
	{
		kEmbeddedWidget* widget = item->widget();
		
		if ( widget )
		{
			mFlippedItem->loadWidget( widget );
			
			mFlipped = true;
			mFlipLeft = mSelectionItem->pos().x() < 0;
			mFlipTimeLine.setDirection( QTimeLine::Forward );
			mFlipTimeLine.start();
		}
	}
	else
	{
		mFlipped = false;
		mFlipTimeLine.setDirection( QTimeLine::Backward );
		mFlipTimeLine.start();
	}
}

QPointF kGuiScenePanel::gridPosition( const QPoint& pos ) const
{
	QPointF p = rect().topLeft() /2;
	QSizeF s = rect().size() /2;
	
	return QPointF( p.x() +( s.width() *pos.x() ), p.y() +( s.height() *pos.y() ) );
}

void kGuiScenePanel::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
	kGuiScenePanelItem* it = currentItem();
	
	if ( ( !it || ( it && !it->isAnimate() ) ) && !isAnimate() && event->modifiers() == Qt::NoModifier )
	{
		if ( isFlipped() )
		{
		}
		else
		{
			if (  event->button() == Qt::LeftButton )
			{
				QPoint newPos = mSelectedPos;
				bool found = false;
				
				foreach ( const int& x, mItems.keys() )
				{
					foreach ( const int& y, mItems[ x ].keys() )
					{
						kGuiScenePanelItem* item = mItems[ x ][ y ];
						
						QPointF mappedPos = item->mapFromScene( event->scenePos() );
						
						if ( item->contains( mappedPos ) )
						{
							newPos = QPoint( x, y );
							found = true;
							break;
						}
					}
				}
				
				if ( found && newPos != mSelectedPos )
				{
					setCurrentItem( newPos, true );
					return;
				}
				else if ( found )
				{
					it->activate();
					return;
				}
			}
		}
	}
	
	QGraphicsRectItem::mousePressEvent( event );
}

void kGuiScenePanel::selectionTimeLineChanged( qreal value )
{
	QPointF newPos( mSelectionStart.x() +( mSelectionEnd -mSelectionStart ).x() *value, mSelectionStart.y() +( mSelectionEnd -mSelectionStart ).y() *value );
	mSelectionItem->setPos( newPos );
	selectionMoved( newPos );
}

void kGuiScenePanel::selectionMoved( const QPointF& newPos )
{
	QTransform transform;
	mRotationY = newPos.x() /8.0;
	mRotationX = newPos.y() /8.0;
	transform.rotate( newPos.x() /8.0, Qt::YAxis );
	transform.rotate( newPos.y() /8.0, Qt::XAxis );
	setTransform( transform );
}

void kGuiScenePanel::flipTimeLineChanged( qreal value )
{
	qreal finalxrot = mRotationX -mRotationX *value;
	qreal finalyrot;
	
	if ( mFlipLeft )
	{
		finalyrot = mRotationY -mRotationY *value -180 *value;
	}
	else
	{
		finalyrot = mRotationY -mRotationY *value +180 *value;
	}
	
	QTransform transform;
	transform.rotate( finalyrot, Qt::YAxis );
	transform.rotate( finalxrot, Qt::XAxis );
	qreal scale = 1 -sin( M_PI *value ) *0.3;
	transform.scale( scale, scale );
	setTransform( transform );
	
	if ( value == 0 )
	{
		currentItem()->setFocus();
	}
}

void kGuiScenePanel::item_rejected()
{
	mFlippedItem->unloadWidget();
}

void kGuiScenePanel::item_accepted()
{
	mFlippedItem->unloadWidget();
}
